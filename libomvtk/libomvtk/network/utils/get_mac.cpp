// vim:et:st=4:ts=4:sts=4:
// Copyright (c) 2008,2009 by the OpenMetaverse Toolkit Library Team
// All rights reserved.
//
// - Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions are met:
//
// - Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// - Neither the name of the OpenMetaverse Toolkit Library Team nor the names
//   of its contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE
#include "get_mac.h"
#include <sstream>
#include <boost/random.hpp>

namespace 
{
    omvtk::String generate_random_mac()
    {
        boost::mt19937 rng;
        boost::uniform_int<> chars(0,255);
        boost::variate_generator<boost::mt19937&, boost::uniform_int<> > gen(rng, chars);
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
                ostr << std::hex << unsigned(gen());
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

#    include <winsock2.h>
#    include <iphlpapi.h>

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
