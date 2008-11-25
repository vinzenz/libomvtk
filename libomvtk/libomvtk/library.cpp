#include "library.h"
#include "logger/logger.h"
#include <boost/pool/detail/singleton.hpp>

namespace omvtk
{
	namespace detail
	{
		struct LibraryImpl
		{
			LibraryImpl()
			: service()
			, ssl_context(service, boost::asio::ssl::context::sslv23)
			{
				logger::init(); 
			}

			~LibraryImpl()
			{ 
				logger::shutdown(); 
			}
			
			boost::asio::io_service 	service;
			boost::asio::ssl::context 	ssl_context;		
		};

		typedef boost::details::pool::singleton_default<LibraryImpl> Library;
	}
		
	boost::asio::io_service & Library::service()
	{
		return detail::Library::instance().service;
	}

	boost::asio::ssl::context & Library::context()
	{
		return detail::Library::instance().ssl_context;
	}
		
}

