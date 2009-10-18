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
#ifndef GUARD_LIBOMVTK_NETWORK_ASYNC_TIMER_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_ASYNC_TIMER_H_INCLUDED

#if _MSC_VER > 1200
#    pragma once
#endif

#include <boost/asio.hpp>
#include <boost/asio/placeholders.hpp>

namespace omvtk
{
    
    struct AsyncTimer
        : boost::noncopyable
    {
        AsyncTimer(boost::asio::io_service & ios)
            : m_timer(ios)
            , m_interval(0)
        {}

        ~AsyncTimer()
        {
            stop();
        }        

        void start(UInt32 interval, boost::function<void()> const & func)
        {
            m_interval     = interval;
            m_func = func;
            on_timer(boost::system::error_code());
        }

        void stop()
        {
            m_timer.cancel();
            m_interval = 0;
            m_func.clear();
        }

    protected:
        void on_timer(boost::system::error_code const & error)
        {
            if(error && m_func && m_interval > 0)
            {
                m_timer.expires_from_now
                (
                    boost::posix_time::millisecons(m_interval),
                    boost::bind
                    ( 
                        &AsyncTimer::on_timer, 
                        this,
                        boost::asio::placeholders::error                        
                    );
                );
                m_func();        
            }
        }

    protected:
        boost::asio::deadline_timer m_timer;
        UInt32 m_interval; 
        boost::function<void()> m_func;
    };
}

#endif // GUARD_LIBOMVTK_NETWORK_ASYNC_TIMER_H_INCLUDED
