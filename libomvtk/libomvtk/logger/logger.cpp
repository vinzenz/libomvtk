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
#include "logger.h"
#include <boost/logging/format/named_write.hpp>

namespace omvtk
{
	namespace logger
	{
		  
		BOOST_DEFINE_LOG_FILTER( g_log_level, boost::logging::level::holder )
		BOOST_DEFINE_LOG(g_logger, logger_type)
		  
		void set_log_level(log_level l)
		{
			using namespace boost::logging;
			switch(l)
			{
			case debug:
			  g_log_level()->set_enabled(level::debug);
			  break;
			case info:
			  g_log_level()->set_enabled(level::info);
			  break;
			case error:
			  g_log_level()->set_enabled(level::error);
			  break;
			}
		}
		  
		void init(log_level level)
		{
			g_logger()->writer().write("[%idx%] %time%($yyyy-$MM-$dd $hh:$mm.$ss) %thread_id% |\n", "file(libomvtk.log) debug");
			g_logger()->mark_as_initialized();    
			LOG_APP << "Logger Subsystem initialized";
			set_log_level(level);
		}

		void suspend()
		{
			g_log_level()->set_enabled(false);
		}

		void resume()
		{
			g_log_level()->set_enabled(true);
		}

		void shutdown()
		{
			set_log_level(info);
			LOG_APP << "Logger Subsystem shutdown";    
		}
	}
}
