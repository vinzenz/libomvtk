#include "https_client.h"
#include "http_response_parser.h"
#include "../../logger/logger.h"

namespace omvtk
{
	HTTPSClient::Pointer HTTPSClient::create(Context & ctx, Service & ios)
	{
		return Pointer(new HTTPSClient(ctx, ios));
	}

	bool HTTPSClient::async_request(HTTPRequest const & req, Handler handler)
	{
		if(handler && !m_socket.lowest_layer().is_open())
		{									
			size_t pos = req.header().host().find_first_of(':');
			Resolver::query q(req.header().host().substr(0, pos),"https");
			m_handler = handler;
			m_req = RequestPtr(new HTTPRequest(req));			
			m_resolver.async_resolve
			(
				q, 
				boost::bind
				(
					&HTTPSClient::on_resolve, 
					shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::iterator
				)
			);
			return true;
		}
		return false;
	}
		
	HTTPSClient::HTTPSClient(Context & ctx, Service & ios)
	: m_ios(ios)
	, m_ctx(ctx)
	, m_resolver(ios)
	, m_socket(ios, ctx)
	, m_req()
	, m_writeBuf()
	, m_readBuf()
	, m_handler()
	{

	}

	HTTPSClient::~HTTPSClient()
	{

	}

	HTTPSClient::Endpoint HTTPSClient::endpoint() const
	{
		return const_cast<HTTPSClient*>(this)->m_socket.lowest_layer().remote_endpoint();
	}

	void HTTPSClient::cancel()
	{
		m_ios.post(boost::bind(&HTTPSClient::do_close, this));
	}

	void HTTPSClient::do_close()
	{
		if(m_socket.lowest_layer().is_open())
		{
			m_socket.lowest_layer().close();
		}
	}

	void HTTPSClient::on_resolve(Pointer self, ErrorCode ec, EPIterator iter)
	{
		if(!ec)
		{
			setup_connect(self, ec, iter);
		}
		else
		{
			LOG_ERR << "HTTPSClient: Resolving host failed:  " << ec.message() 
					<< " Request was: " << self->m_req->header().request();

		}
	}
	
	void HTTPSClient::setup_connect(Pointer self, ErrorCode ec, EPIterator iter)
	{
		if(!ec)
		{
			Endpoint endpoint = *iter;
    	  	self->m_socket.lowest_layer().async_connect
			(
				endpoint,
				boost::bind
				(
					&HTTPSClient::on_connect, 
					self,
					boost::asio::placeholders::error, 
					++iter
				)
			);			
		}
	}

	void HTTPSClient::on_connect(Pointer self, ErrorCode ec, EPIterator iter)
	{
		if(!ec)
		{
			self->m_socket.async_handshake
			(
				boost::asio::ssl::stream_base::client,
				boost::bind
				(
					&HTTPSClient::on_handshake, 
					self,
					boost::asio::placeholders::error
				)
			);
		}
		else if(iter != EPIterator())
		{
			self->m_socket.lowest_layer().close();
			setup_connect(self, ec, iter);
		}
		else
		{
			self->m_socket.lowest_layer().close();
			LOG_ERR << "HTTPSClient: Connecting to server failed: " << ec.message() 
					<< " Request was: " << self->m_req->header().request();
		}
	}

	void HTTPSClient::on_handshake(Pointer self, ErrorCode ec)
	{
		if(!ec)
		{
			self->m_req->build(self->m_writeBuf);
			boost::asio::async_write
			(
				self->m_socket,
				boost::asio::buffer(self->m_writeBuf),
				boost::bind
				(
					&HTTPSClient::on_write,
					self,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred
				)
			);
		}
		else
		{
			LOG_ERR << "HTTPSClient: Connecting to server failed: " << ec.message() 
					<< " Request was: " << self->m_req->header().request();
		}
	}

	void HTTPSClient::on_write(Pointer self, ErrorCode ec, size_t)
	{
		self->m_writeBuf.clear();
		if(!ec)
		{
			self->m_writeBuf.resize(BUFFER_SIZE,0);		
			do_read(self);
		}
		else
		{
			LOG_ERR << "HTTPSClient: Writing to server failed: " << ec.message() 
					<< " Request was: " << self->m_req->header().request();
		}
	}

	void HTTPSClient::on_read(Pointer self, ErrorCode ec, size_t bytes)
	{
		if(bytes)
		{	
			LOG_DBG << "HTTPSClient: Received " << bytes << "Bytes Data:\n" 
					<< String(self->m_writeBuf.begin(),self->m_writeBuf.begin()+bytes) << std::endl;	
			self->m_readBuf.insert(	self->m_readBuf.end(), 
									self->m_writeBuf.begin(), 
									self->m_writeBuf.begin() + bytes);
		}

		if(!ec)
		{
			do_read(self);
		}
		else if(ec == boost::asio::error::eof)
		{
			process_data(self);
		}
		else if(!self->m_readBuf.empty())
		{
//			LOG_WARN << "HTTPSClient: an error occurred while reading from socket: " << ec.message() 
//					 << " Request was: " << self->m_req->header().request()
//					 << " But data have been received. Trying to process them.";
			process_data(self);
		}
		else
		{
			LOG_ERR << "HTTPSClient: Reading data from server failed: " << ec.message() 
					<< " Request was: " << self->m_req->header().request();
		}
	}
	
	void HTTPSClient::do_read(Pointer self)
	{		
		boost::asio::async_read
		(
			self->m_socket,
			boost::asio::buffer(&self->m_writeBuf[0],self->m_writeBuf.size()),
			boost::bind
			(
				&HTTPSClient::on_read,
				self,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)
		);
	}

	void HTTPSClient::process_data(Pointer self)
	{
		self->m_socket.lowest_layer().close();
		if(!self->m_readBuf.empty())
		{
			try
			{
				LOG_DBG << "Received data:\n" <<  String(self->m_readBuf.begin(),self->m_readBuf.end()) << std::endl;

				HTTPResponseParser parser(self->m_readBuf);
				self->m_handler(parser.get());			
			}	
			catch(std::exception const & e)
			{				
				LOG_ERR << "HTTPSClient: Excecption caught while processing data. What: " << e.what();
			}
			catch(...)
			{
				LOG_ERR << "HTTPSClient: Unknown excecption caught while processing data.";
			}
		}
		else
		{
			LOG_ERR << "HTTPSClient: No data received. Request (data stripped) was: " << self->m_req->header().request(); 
		}
	}

}

