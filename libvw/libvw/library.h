#ifndef GUARD_LIBVW_LIBRARY_H_INCLUDED
#define GUARD_LIBVW_LIBRARY_H_INCLUDED

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace vw
{
	struct Library
	{
		boost::asio::io_service   & service();		
		boost::asio::ssl::context & context();
	};
}

#endif //GUARD_LIBVW_LIBRARY_H_INCLUDED

