#ifndef GUARD_LIBVW_NETWORK_ASYNC_TIMER_H_INCLUDED
#define GUARD_LIBVW_NETWORK_ASYNC_TIMER_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include <boost/asio.hpp>
#include <boost/asio/placeholders.hpp>

namespace vw
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
			m_interval 	= interval;
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

#endif // GUARD_LIBVW_NETWORK_ASYNC_TIMER_H_INCLUDED
