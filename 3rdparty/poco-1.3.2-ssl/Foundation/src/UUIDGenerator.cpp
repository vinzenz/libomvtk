//
// UUIDGenerator.cpp
//
// $Id: //poco/1.3/Foundation/src/UUIDGenerator.cpp#3 $
//
// Library: Foundation
// Package: UUID
// Module:  UUID
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


#include "Poco/UUIDGenerator.h"
#include "Poco/Thread.h"
#include "Poco/RandomStream.h"
#include "Poco/DigestEngine.h"
#include "Poco/MD5Engine.h"
#include "Poco/SingletonHolder.h"
#include <cstring>


namespace Poco {


UUIDGenerator::UUIDGenerator(): _ticks(0), _haveNode(false)
{
}


UUIDGenerator::~UUIDGenerator()
{
}


UUID UUIDGenerator::create()
{
	FastMutex::ScopedLock lock(_mutex);

	if (!_haveNode)
	{
		getNode();
		_haveNode = true;
	}
	Timestamp::UtcTimeVal tv = timeStamp();
	UInt32 timeLow = UInt32(tv & 0xFFFFFFFF);
	UInt16 timeMid = UInt16((tv >> 32) & 0xFFFF);
	UInt16 timeHiAndVersion = UInt16((tv >> 48) & 0x0FFF) + (UUID::UUID_TIME_BASED << 12);
	UInt16 clockSeq = (UInt16(_random.next() >> 4) & 0x3FFF) | 0x8000;
	return UUID(timeLow, timeMid, timeHiAndVersion, clockSeq, _node);
}


UUID UUIDGenerator::createFromName(const UUID& nsid, const std::string& name)
{
	MD5Engine md5;
	return createFromName(nsid, name, md5);
}


UUID UUIDGenerator::createFromName(const UUID& nsid, const std::string& name, DigestEngine& de)
{
	poco_assert_dbg (de.digestLength() >= 16);

	UUID netNsid = nsid;
	netNsid.toNetwork();
	de.reset();
	de.update(&netNsid, sizeof(netNsid));
	de.update(name);
	char buffer[16];
	const DigestEngine::Digest& d = de.digest();
	for (int i = 0; i < 16; ++i)
	{
		buffer[i] = d[i];
	}
	return UUID(buffer, UUID::UUID_NAME_BASED);
}

	
UUID UUIDGenerator::createRandom()
{
	char buffer[16];
	RandomInputStream ris;
	ris.read(buffer, sizeof(buffer));
	return UUID(buffer, UUID::UUID_RANDOM);
}


Timestamp::UtcTimeVal UUIDGenerator::timeStamp()
{
	Timestamp now;
	for (;;)
	{
		if (now != _lastTime)
		{
			_lastTime = now;
			_ticks = 0;
			break;
		}
		if (_ticks < 100)
		{
			++_ticks;
			break;
		}
		now.update();
	}
	Timestamp::UtcTimeVal tv = now.utcTime();
	return tv + _ticks;
}


UUID UUIDGenerator::createOne()
{
	try
	{
		return create();
	}
	catch (Exception&)
	{
		return createRandom();
	}
}


UUIDGenerator& UUIDGenerator::defaultGenerator()
{
	static SingletonHolder<UUIDGenerator> sh;
	return *sh.get();
}


} // namespace Poco


//
// platform-specific code below
//


#if defined(POCO_OS_FAMILY_WINDOWS)
//
// Windows
//
#include "Poco/UnWindows.h"
#include <iphlpapi.h>


namespace Poco {


void UUIDGenerator::getNode()
{
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = 0;
	ULONG len    = sizeof(IP_ADAPTER_INFO);
	pAdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(new char[len]);
	// Make an initial call to GetAdaptersInfo to get
	// the necessary size into len
	DWORD rc = GetAdaptersInfo(pAdapterInfo, &len);
	if (rc == ERROR_BUFFER_OVERFLOW) 
	{
		delete [] reinterpret_cast<char*>(pAdapterInfo);
		pAdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(new char[len]);
	}
	else if (rc != ERROR_SUCCESS)
	{
		throw SystemException("cannot get network adapter list");
	}
	try
	{
		bool found = false;
		if (GetAdaptersInfo(pAdapterInfo, &len) == NO_ERROR) 
		{
			pAdapter = pAdapterInfo;
			while (pAdapter && !found) 
			{
				if (pAdapter->Type == MIB_IF_TYPE_ETHERNET && pAdapter->AddressLength == sizeof(_node))
				{
					std::memcpy(_node, pAdapter->Address, pAdapter->AddressLength);
					found = true;
				}
				pAdapter = pAdapter->Next;
			}
		}
		else throw SystemException("cannot get network adapter list");
		if (!found) throw SystemException("no Ethernet adapter found");
	}
	catch (Exception&)
	{
		delete [] reinterpret_cast<char*>(pAdapterInfo);
		throw;
	}
	delete [] reinterpret_cast<char*>(pAdapterInfo);
}


} // namespace Poco


#elif defined(POCO_OS_FAMILY_BSD) || POCO_OS == POCO_OS_QNX
//
// BSD variants
//
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <net/if_dl.h>


namespace Poco {


void UUIDGenerator::getNode()
{
	struct ifaddrs* ifaphead;
	int rc = getifaddrs(&ifaphead);
	if (rc) throw SystemException("cannot get network adapter list");

	bool foundAdapter = false;
	for (struct ifaddrs* ifap = ifaphead; ifap; ifap = ifap->ifa_next) 
	{
		if (ifap->ifa_addr && ifap->ifa_addr->sa_family == AF_LINK) 
		{
			struct sockaddr_dl* sdl = reinterpret_cast<struct sockaddr_dl*>(ifap->ifa_addr);
			caddr_t ap = (caddr_t) (sdl->sdl_data + sdl->sdl_nlen);
			int alen = sdl->sdl_alen;
			if (ap && alen > 0) 
			{
				std::memcpy(_node, ap, sizeof(_node));
				foundAdapter = true;
				break;
			}
		}
	}
	freeifaddrs(ifaphead);
	if (!foundAdapter) throw SystemException("cannot determine MAC address (no suitable network adapter found)");
}


} // namespace Poco


#elif defined(__CYGWIN__) || POCO_OS == POCO_OS_LINUX
//
// Linux
//
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <unistd.h>


namespace Poco {


void UUIDGenerator::getNode()
{
	struct ifreq ifr;

	int s = socket(PF_INET, SOCK_DGRAM, 0);
	if (s == -1) throw SystemException("cannot open socket");

	strcpy(ifr.ifr_name, "eth0");
	int rc = ioctl(s, SIOCGIFHWADDR, &ifr);
	close(s);
	if (rc < 0) throw SystemException("cannot get MAC address");
	struct sockaddr* sa = reinterpret_cast<struct sockaddr*>(&ifr.ifr_addr);
	std::memcpy(_node, sa->sa_data, sizeof(_node));
}


} // namespace Poco


#elif defined(POCO_OS_FAMILY_UNIX) || defined(POCO_OS_FAMILY_VMS)
//
// Unix/VMS
//
#if defined(__VMS)
#include <ioctl.h>
#else
#include <sys/ioctl.h>
#endif
#if defined(sun) || defined(__sun)
#include <sys/sockio.h>
#endif
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <net/if.h>
#if defined(__VMS)
#include <inet.h>
#else
#include <arpa/inet.h>
#endif
#include <netdb.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <unistd.h>


#if defined(__VMS)
#define MAXHOSTNAMELEN 64
#endif


namespace Poco {


void UUIDGenerator::getNode()
{
	char name[MAXHOSTNAMELEN];
	if (gethostname(name, sizeof(name)))
		throw SystemException("cannot get host name");

	struct hostent* pHost = gethostbyname(name);
	if (!pHost) throw SystemException("cannot get host IP address");

	int s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == -1) throw SystemException("cannot open socket");

	struct arpreq ar;
	std::memset(&ar, 0, sizeof(ar));
	struct sockaddr_in* pAddr = reinterpret_cast<struct sockaddr_in*>(&ar.arp_pa);
	pAddr->sin_family = AF_INET;
	std::memcpy(&pAddr->sin_addr, *pHost->h_addr_list, sizeof(struct in_addr));
	int rc = ioctl(s, SIOCGARP, &ar);
	close(s);
	if (rc < 0) throw SystemException("cannot get MAC address");
	std::memcpy(_node, ar.arp_ha.sa_data, sizeof(_node));
}


} // namespace Poco


#endif
