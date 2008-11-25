#include "get_mac.h"
#include <sstream>
#include <Poco/Random.h>

namespace 
{
	omvtk::String generate_random_mac()
	{
		Poco::Random rnd;
		std::ostringstream ostr;
		for(omvtk::UInt8 i = 0; i < 6; ++i)
		{
			switch(i)
			{
			default:
				ostr << ":"; 			
			case 0:
				ostr.width(2);
				ostr.fill('0');
				ostr << std::hex << unsigned(rnd.nextChar());					
				break;
			}
		}			
		return ostr.str();
	}


	void fmt_bytes(omvtk::UInt8 * bytes, omvtk::UInt32 size, omvtk::String & out)
	{
		std::ostringstream ostr;
		for(omvtk::UInt8 i = 0; i < size; ++i)
		{
			switch(i)
			{
			default:
				ostr << ":"; 			
			case 0:
				ostr.width(2);
				ostr.fill('0');
				ostr << std::hex << unsigned(bytes[i]);					
				break;
			}
		}	
		out = ostr.str();			
	}
}

#ifdef LIBOMVTK_LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netpacket/packet.h>
#include <ifaddrs.h>

namespace
{

	template<typename Container>
	void get_all_mac_addresses(Container & macs)
	{
		ifaddrs * ifap = 0;
		if(getifaddrs(&ifap) == 0)
		{		
			ifaddrs * iter = ifap;
			while(iter)
			{
				sockaddr_ll * sal = reinterpret_cast<sockaddr_ll*>(iter->ifa_addr);
				if(sal->sll_family == AF_PACKET)
				{
					omvtk::String mac;
					fmt_bytes(&sal->sll_addr[0], sal->sll_halen, mac);
					if(mac.size() == 17)
					{
						macs.push_back(mac);
					}
				}
				iter = iter->ifa_next;
			}
			freeifaddrs(ifap);
		}
	}
}

#elif defined(LIBOMVTK_WINDOWS)

#	include <winsock2.h>
#	include <iphlpapi.h>

namespace 
{
	template<typename Container>
	void get_all_mac_addresses(Container & macs)
	{
		omvtk::ByteBuffer buf;
		DWORD bufLen = 0;
		GetAdaptersAddresses(0, 0, 0, 0, &bufLen);
		if(!bufLen)
		{
			return;
		}
		buf.resize(bufLen, 0);
		IP_ADAPTER_ADDRESSES * ptr = reinterpret_cast<IP_ADAPTER_ADDRESSES*>(&buf[0]);
		DWORD err = GetAdaptersAddresses(0, 0, 0, ptr, &bufLen);
		if(err == NO_ERROR)
		{
			while(ptr)
			{
				if(ptr->PhysicalAddressLength)
				{
					omvtk::String mac;
					fmt_bytes(&ptr->PhysicalAddress[0], ptr->PhysicalAddressLength, mac);
					if(mac.size() == 17)
					{
						macs.push_back(mac);
					}
				}
				ptr = ptr->Next;
			}
		}
	}
}
#else
namespace
{	
	template<typename Container>
	void get_all_mac_addresses(Container & macs)
	{
		macs.push_back(generate_random_mac());
	}
}
#endif

#include <vector>

namespace omvtk
{
	String get_mac()
	{
		std::vector<String> macs;
		get_all_mac_addresses(macs);
		if(macs.empty())
		{
			return generate_random_mac();
		}	
		return macs.back();
	}	
}
