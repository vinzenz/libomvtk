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
#ifndef GUARD_LIBOMVTK_LOGGER_LOGGER_H_INCLUDED
#define GUARD_LIBOMVTK_LOGGER_LOGGER_H_INCLUDED

#include <boost/logging/format_fwd.hpp>
#include <boost/logging/format/named_write_fwd.hpp>

#ifdef LOG_LEVEL
  #define DEFAULT_LOG_LEVEL LOG_LEVEL
#else
  #define DEFAULT_LOG_LEVEL info
#endif

namespace omvtk
{
    namespace logger
    {
          enum log_level
          {
            trace,
            debug,
            verbose,
            info,
            warning,
            error,
            fatal
          };
  
          typedef boost::logging::named_logger<>::type logger_type;
        #define LOG_(lvl) BOOST_LOG_USE_LOG_IF_LEVEL( omvtk::logger::g_logger() , omvtk::logger::g_log_level(), lvl ) << __FILE__ << ":" << __LINE__

        #define LOG_DBG     LOG_(debug)     <<  " [ DEBUG ] MSG: "
        #define LOG_APP     LOG_(verbose)   <<  " [  APP  ] MSG: "
        #define LOG_INFO    LOG_(info)      <<  " [ INFO  ] MSG: "
        #define LOG_ERR     LOG_(error)     <<  " [ ERROR ] MSG: "        
        #define LOG_FATAL   LOG_(fatal)     <<  " [ FATAL ] MSG: "
        #define LOG_WARN    LOG_(warning)   <<  " [ WARN  ] MSG: "
        #define LOG_TRACE   LOG_(enable_all)<<  " [ TRACE ] MSG: "

        BOOST_DECLARE_LOG_FILTER( g_log_level, boost::logging::level::holder )
        BOOST_DECLARE_LOG(g_logger, logger_type)
  
        void set_log_level(log_level l);  
        void init(log_level level = DEFAULT_LOG_LEVEL);
        void suspend();
        void resume();
        void shutdown();
    }
}

#endif //GUARD_LIBOMVTK_LOGGER_LOGGER_H_INCLUDED


