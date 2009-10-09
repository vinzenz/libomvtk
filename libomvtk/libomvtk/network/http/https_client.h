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

