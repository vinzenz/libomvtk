//
// Thread_WIN32.h
//
// $Id: //poco/1.3/Foundation/src/Thread_WIN32.cpp#2 $
//
// Library: Foundation
// Package: Threading
// Module:  Thread
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/Thread_WIN32.h"
#include "Poco/Exception.h"
#include "Poco/ErrorHandler.h"
#include <process.h>


namespace Poco {


DWORD ThreadImpl::_currentKey = TLS_OUT_OF_INDEXES;


ThreadImpl::ThreadImpl(): _pTarget(0), _thread(0), _prio(PRIO_NORMAL_IMPL)
{
	if (_currentKey == TLS_OUT_OF_INDEXES)
	{
		_currentKey = TlsAlloc();
		if (_currentKey == TLS_OUT_OF_INDEXES)
			throw SystemException("cannot allocate thread context key");
	}
}

			
ThreadImpl::~ThreadImpl()
{
	if (_thread) CloseHandle(_thread);
}


void ThreadImpl::setPriorityImpl(int prio)
{
	if (prio != _prio)
	{
		_prio = prio;
		if (_thread)
		{
			if (SetThreadPriority(_thread, _prio) == 0)
				throw SystemException("cannot set thread priority");
		}
	}
}


void ThreadImpl::startImpl(Runnable& target)
{
	if (_thread) throw SystemException("thread already running");

	_pTarget = &target;
#if defined(_DLL)
	DWORD threadId;
	_thread = CreateThread(NULL, 0, entry, this, 0, &threadId);
#else
	unsigned threadId;
	_thread = (HANDLE) _beginthreadex(NULL, 0, entry, this, 0, &threadId);
#endif
	if (!_thread)
		throw SystemException("cannot create thread");
	if (_prio != PRIO_NORMAL_IMPL && !SetThreadPriority(_thread, _prio))
		throw SystemException("cannot set thread priority");
}


void ThreadImpl::joinImpl()
{
	if (!_thread) return;

	switch (WaitForSingleObject(_thread, INFINITE))
	{
	case WAIT_OBJECT_0:
		return;
	default:
		throw SystemException("cannot join thread");
	}
}


bool ThreadImpl::joinImpl(long milliseconds)
{
	if (!_thread) return true;

	switch (WaitForSingleObject(_thread, milliseconds + 1))
	{
	case WAIT_TIMEOUT:
		return false;
	case WAIT_OBJECT_0:
		return true;
	default:
		throw SystemException("cannot join thread");
	}
}


bool ThreadImpl::isRunningImpl() const
{
	if (_thread)
	{
		DWORD ec = 0;
		return GetExitCodeThread(_thread, &ec) && ec == STILL_ACTIVE;
	}
	return false;
}


ThreadImpl* ThreadImpl::currentImpl()
{
	if (_currentKey == TLS_OUT_OF_INDEXES)
		return 0;
	else
		return (ThreadImpl*) TlsGetValue(_currentKey);
}


#if defined(_DLL)
DWORD WINAPI ThreadImpl::entry(LPVOID pThread)
#else
unsigned __stdcall ThreadImpl::entry(void* pThread)
#endif
{
	TlsSetValue(_currentKey, pThread);
	try
	{
		reinterpret_cast<ThreadImpl*>(pThread)->_pTarget->run();
	}
	catch (Exception& exc)
	{
		ErrorHandler::handle(exc);
	}
	catch (std::exception& exc)
	{
		ErrorHandler::handle(exc);
	}
	catch (...)
	{
		ErrorHandler::handle();
	}
	return 0;
}


} // namespace Poco
