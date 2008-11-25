#include "logger.h"
#include <boost/logging/format/named_write.hpp>

namespace vw
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
			g_logger()->writer().write("[%idx%] %time%($yyyy-$MM-$dd $hh:$mm.$ss) %thread_id% |\n", "file(libvw.log) debug");
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
