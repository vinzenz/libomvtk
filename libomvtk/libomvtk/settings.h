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
#ifndef GUARD_LIBOMVTK_SETTINGS_H_INCLUDED
#define GUARD_LIBOMVTK_SETTINGS_H_INCLUDED

#include "utils/locked_property.h"
#include "types/base_types.h"

namespace omvtk
{
    struct GridClient;
    struct Settings
        : boost::noncopyable
    {        
        typedef boost::mutex Mutex;
        typedef LockedProperty<String> StringProp;
        typedef LockedProperty<UInt32> UInt32Prop;
        typedef LockedProperty<Int32>  Int32Prop;
        typedef LockedProperty<bool>   BoolProp;

    protected:

        GridClient & m_client;
        Mutex m_mutex;
    
    public:
        
        Settings(GridClient & gc);

    // Settings from here to the end 
        StringProp const login_uri;
        StringProp const agni_uri;
        StringProp const aditi_uri;
        StringProp const resource_directory;
        StringProp const cache_directory;
    
    // Network Settings
        StringProp user_agent;
        UInt32Prop http_connect_timeout;
        UInt32Prop http_timeout;
    };
}

#endif //GUARD_LIBOMVTK_SETTINGS_H_INCLUDED

