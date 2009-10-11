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
#include "settings.h"
#include "gridclient.h"
#include "version.h"

namespace omvtk
{
	Settings::Settings(GridClient & gc)
	: boost::noncopyable()
	, m_client(gc)
	, m_mutex()
	, login_uri(m_mutex, "https://login.agni.lindenlab.com/cgi-bin/login.cgi")
	, agni_uri(m_mutex, "https://login.agni.lindenlab.com/cgi-bin/login.cgi")
	, aditi_uri(m_mutex, "https://login.aditi.lindenlab.com/cgi-bin/login.cgi")
	, resource_directory(m_mutex, "../../data/")
	, cache_directory(m_mutex, "../../data/cache/")
    // Network Settings
	, user_agent(m_mutex, LIBOMVTK_VERSION_STRING)
	, http_connect_timeout(m_mutex, 30)
	, http_timeout(m_mutex, 30)
	{}			
}

