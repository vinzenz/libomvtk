//
// SimpleFileChannelTest.cpp
//
// $Id: //poco/1.3/Foundation/testsuite/src/SimpleFileChannelTest.cpp#1 $
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
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


#include "Poco/SimpleFileChannel.h"
#include "Poco/Message.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/AutoPtr.h"
#include "SimpleFileChannelTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"


using Poco::SimpleFileChannel;
using Poco::Message;
using Poco::Path;
using Poco::File;
using Poco::DirectoryIterator;
using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::AutoPtr;


SimpleFileChannelTest::SimpleFileChannelTest(const std::string& name): CppUnit::TestCase(name)
{
}


SimpleFileChannelTest::~SimpleFileChannelTest()
{
}


void SimpleFileChannelTest::testRotate()
{
	std::string name = filename();
	try
	{
		AutoPtr<SimpleFileChannel> pChannel = new SimpleFileChannel(name);
		pChannel->setProperty(SimpleFileChannel::PROP_ROTATION, "2 K");
		pChannel->open();
		Message msg("source", "This is a log file entry", Message::PRIO_INFORMATION);
		for (int i = 0; i < 200; ++i)
		{
			pChannel->log(msg);
		}
		File f(name);
		assert (f.exists());
		f = name + ".0";
		assert (f.exists());
		assert (f.getSize() >= 2048);
	}
	catch (...)
	{
		remove(name);
		throw;
	}
	remove(name);
}


void SimpleFileChannelTest::setUp()
{
}


void SimpleFileChannelTest::tearDown()
{
}


void SimpleFileChannelTest::remove(const std::string& baseName)
{
	DirectoryIterator it(Path::current());
	DirectoryIterator end;
	std::vector<std::string> files;
	while (it != end)
	{
		if (it.name().find(baseName) == 0)
		{
			files.push_back(it.name());
		}
		++it;
	}
	for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it)
	{
		try
		{
			File f(*it);
			f.remove();
		}
		catch (...)
		{
		}
	}
}


std::string SimpleFileChannelTest::filename() const
{
	std::string name = "log_";
	name.append(DateTimeFormatter::format(Timestamp(), "%Y%m%d%H%M%S"));
	name.append(".log");
	return name;
}


CppUnit::Test* SimpleFileChannelTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SimpleFileChannelTest");

	CppUnit_addTest(pSuite, SimpleFileChannelTest, testRotate);

	return pSuite;
}
