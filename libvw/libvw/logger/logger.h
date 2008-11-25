#ifndef GUARD_LIBVW_LOGGER_LOGGER_H_INCLUDED
#define GUARD_LIBVW_LOGGER_LOGGER_H_INCLUDED

#include <boost/logging/format_fwd.hpp>
#include <boost/logging/format/named_write_fwd.hpp>

#ifdef LOG_LEVEL
  #define DEFAULT_LOG_LEVEL LOG_LEVEL
#else
  #define DEFAULT_LOG_LEVEL info
#endif

namespace vw
{
	namespace logger
	{
  		enum log_level
  		{
    		debug,
    		info,
    		error
  		};
  
  		typedef boost::logging::named_logger<>::type logger_type;
  		#define LOG_(lvl) BOOST_LOG_USE_LOG_IF_LEVEL( logger::g_logger() , logger::g_log_level(), lvl ) << __FILE__ << ":" << __LINE__

		#define LOG_DBG LOG_(debug)  <<  " [ DEBUG ] MSG: "
		#define LOG_APP LOG_(info)   <<  " [ INFO  ] MSG: "
		#define LOG_ERR LOG_(error)  <<  " [ ERROR ] MSG: "		
		#define LOG_FATAL LOG_(error) << " [ FATAL ] MSG: "
		#define LOG_WARN LOG_(error) <<  " [ WARN  ] MSG: "
		#define LOG_TRACE LOG_(debug)<<  " [ TRACE ] MSG: "

		BOOST_DECLARE_LOG_FILTER( g_log_level, boost::logging::level::holder )
		BOOST_DECLARE_LOG(g_logger, logger_type)
  
		void set_log_level(log_level l);  
		void init(log_level level = DEFAULT_LOG_LEVEL);
		void suspend();
		void resume();
		void shutdown();
	}
}

#endif //GUARD_LIBVW_LOGGER_LOGGER_H_INCLUDED


