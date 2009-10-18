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
#ifndef GUARD_LIBOMVTK_HTTP_LOGIN_XMLRPC_H_INCLUDED
#define GUARD_LIBOMVTK_HTTP_LOGIN_XMLRPC_H_INCLUDED

#include <sstream>
#include "../libomvtk/llsd/value.h"
#if 0
    return "<?xml version=\"1.0\"?><methodCall><methodName>login_to_simulator</methodName><params><param><value><struct>"
        "<member><name>first</name><value><string>" + firstname + "</string></value></member>"
        "<member><name>last</name><value><string>" + lastname + "</string></value></member>"
        "<member><name>passwd</name><value><string>" + "$1$" + MD5::hash(password).to_string() + "</string></value></member>"
        "<member><name>start</name><value><string>last</string></value></member>"
        "<member><name>major</name><value><string>1</string></value></member>"
        "<member><name>minor</name><value><string>23</string></value></member>"
        "<member><name>patch</name><value><string>4</string></value></member>"
        "<member><name>build</name><value><string>123908</string></value></member>"
        "<member><name>platform</name><value><string>Win</string></value></member>"
        "<member><name>mac</name><value><string>" + "00:13:8F:63:2B:B5" + "</string></value></member>"
        "<member><name>viewer_digest</name><value><string>68920a26-9f41-b742-a5e6-db6a713dcd96</string></value></member>"
        "<member><name>user-agent</name><value><string>" + "0.0.1" + "</string></value></member>"
     "<member><name>author</name><value><string>" + "contact@virtuosic-bytes.com" + "</string></value></member>"
        "</struct></value></param></params></methodCall>\r\n\r\n";
    map["first"]             = firstname;
    map["last"]             = lastname;
    map["passwd"]             = "$1$" + MD5::hash(password).to_string();
    map["start"]             = "last";
    map["channel"]             = "contact@virtuosic-bytes.com";
    map["version"]             = "1.23.4.123908";
    map["major"]             = "1";
    map["minor"]             = "23";
    map["patch"]             = "4";
    map["build"]             = "123908";
    map["platform"]         = "Win";
    map["mac"]                 = "00:13:8F:63:2B:B5";
    map["agree_to_tos"]     = true;
    map["read_critical"]     = true;
    map["viewer_digest"]     = "68920a26-9f41-b742-a5e6-db6a713dcd96";
    map["id0"]                 = map["mac"];
#endif
namespace omvtk {
    struct LoginRequestXMLRPC {
        String operator()( LLSDValue::Map const & m ){
            std::ostringstream os;
            os << "<?xml version=\"1.0\"?>";
            methodCall(os, m);
            return os.str();
        }

        void methodCall( std::ostream & os, LLSDValue::Map const & m ) {
            os << "<methodCall><methodName>login_to_simulator</methodName><params><param><value><struct>";
            params(os, m);
            os << "</struct></value></param></params></methodCall>";
        }

        void params( std::ostream & os, LLSDValue::Map const & m ) {
            BOOST_FOREACH( LLSDValue::Map::value_type const & v, m ){
                value(os, v.first, v.second);
            }
        }

        void value( std::ostream & os, String const & name, LLSDValue const & value ){
            String mapped_name = map_name(name);
            if ( !mapped_name.empty() ) {
                os << "<member><name>" << mapped_name 
                   << "</name><value>" 
                   << value.to_string() 
                   << "</value></member>";
            }
        }

        String map_name( String const & name ) {
            if ( name == "version" ) {
                return "user-agent";
            }
            else if ( name == "channel" ) {
                return "author";
            }
            else if ( name == "options" ) {
                return "";
            }
            return name;
        }
    };
}

#endif //GUARD_LIBOMVTK_HTTP_LOGIN_XMLRPC_H_INCLUDED
