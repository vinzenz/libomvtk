#ifndef GUARD_LIBOMVTK_LIBRARY_H_INCLUDED
#define GUARD_LIBOMVTK_LIBRARY_H_INCLUDED

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace omvtk
{
	struct Library
	{
		boost::asio::io_service   & service();		
		boost::asio::ssl::context & context();
	};
}

#endif //GUARD_LIBOMVTK_LIBRARY_H_INCLUDED

