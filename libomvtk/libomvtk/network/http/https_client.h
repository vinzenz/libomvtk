#ifndef GUARD_LIBOMVTK_NETWORK_HTTPS_CLIENT_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_HTTPS_CLIENT_H_INCLUDED

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "http_request.h"
#include "http_response.h"
#include "../../types/base_types.h"

namespace omvtk
{
	struct HTTPSClient
		: boost::enable_shared_from_this<HTTPSClient>
	{
		enum { BUFFER_SIZE = 8192 };
		typedef boost::asio::ssl::context 					Context;		
		typedef boost::asio::io_service   					Service;		
		typedef boost::asio::ip::tcp						Impl;
		typedef boost::asio::ssl::stream<Impl::socket>		Socket;
		typedef Impl::resolver								Resolver;
		typedef Impl::resolver::iterator					EPIterator;
		typedef Impl::endpoint								Endpoint;		
		typedef boost::system::error_code					ErrorCode;
		typedef boost::function<void(HTTPResponse const&)>  Handler;
		typedef boost::shared_ptr<HTTPSClient>				Pointer;
		typedef boost::shared_ptr<HTTPRequest>				RequestPtr;		

		static Pointer create(Context & ctx, Service & ios);

		bool async_request(HTTPRequest const & req, Handler handler);		

		Endpoint endpoint() const;
		void cancel();
		
		~HTTPSClient();
	protected:
		HTTPSClient(Context & ctx, Service & ios);

	protected:
		static void on_resolve(Pointer, ErrorCode, EPIterator);
		static void setup_connect(Pointer, ErrorCode, EPIterator);
		static void on_connect(Pointer, ErrorCode, EPIterator);
		static void on_handshake(Pointer, ErrorCode);
		static void on_write(Pointer, ErrorCode, size_t);
		static void on_read(Pointer, ErrorCode, size_t);
		static void do_read(Pointer);
		static void process_data(Pointer);
		void do_close();				
	protected:
		Service &   m_ios;
		Context &   m_ctx;
		Resolver    m_resolver;
		Socket 		m_socket;
		RequestPtr  m_req;
		ByteBuffer  m_writeBuf;
		ByteBuffer  m_readBuf;		
		Handler     m_handler;
	};	
}

#endif //GUARD_LIBOMVTK_NETWORK_HTTPS_CLIENT_H_INCLUDED

