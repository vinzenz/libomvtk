// Copyright (c) 2008 by the OpenMetaverse Toolkit Library Team
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
// POSSIBILITY OF SUCH DAMAGE.
#ifndef GUARD_LIBVW_NETTESTENV_HTTP_TEST_SERVER_H_INCLUDED
#define GUARD_LIBVW_NETTESTENV_HTTP_TEST_SERVER_H_INCLUDED

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>


namespace vw
{
    namespace testenv
    {
        struct ServerTraits
        {
            typedef boost::asio::io_service                                 io_service_type;
            typedef boost::asio::ip::tcp::endpoint                          endpoint_type;
            typedef boost::asio::ip::tcp::socket                            socket_type;
            typedef boost::asio::ip::tcp::acceptor                          acceptor_type;
            
            static endpoint_type create_ep(boost::uint16_t port)
            {
                return boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port);
            }
        };

        struct HTTPTestSession
        {
            typedef ServerTraits traits;
            HTTPTestSession(traits::io_service_type & service)
            : m_service(service)
            , m_socket(service)
            {}
            
            traits::socket_type & socket()
            { 
                return m_socket; 
            }
            
            void start()
            {
                m_socket.async_read_some
                (
                    boost::asio::buffer(m_inputBuffer, MAX_BUFFER_LENGTH),
                    boost::bind(&HTTPTestSession::handle_read, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred)
                );
            }
        
        protected:
            
            void handle_read(boost::system::error_code const & error, size_t bytes_transferred)
            {
                if(error)
                {
                    std::cout << "ERROR: " << __FILE__ << ":" << __LINE__ << " " << __func__ << ": reading from socket failed. " << error << std::endl;
                    delete this;
                }
                else
                {
                    std::cout << "Retrieved Data:\n";
                    std::cout.write(m_inputBuffer, bytes_transferred);
                    std::cout << std::endl;
                    
                    std::string content = "<h1>Hello World</h1>";
                    std::ostringstream ostr;
                    ostr << "HTTP/1.1 200 OK\r\n";
                    ostr << "Connection: close\r\n";
                    ostr << "Content-Type: text/html\r\n";
                    ostr << "Content-Length: " << content.size() << "\r\n";
                    ostr << "\r\n\r\n" << content;
                    boost::asio::async_write
                    (
                        m_socket,
                        boost::asio::buffer(ostr.str()),
                        boost::bind(&HTTPTestSession::handle_write, this, boost::asio::placeholders::error)
                    );
                    
                }
            }                    
            
            void handle_write(boost::system::error_code const & error)
            {
                if(error)
                {
                    std::cout << "ERROR: " << __FILE__ << ":" << __LINE__ << " " << __func__ << ": reading from socket failed. " << error << std::endl;
                    delete this;
                }
                else
                {
                    memset(m_inputBuffer, 0, MAX_BUFFER_LENGTH);
                    m_socket.close();
                }
            }
            
        protected:
            traits::io_service_type & m_service;
            traits::socket_type       m_socket;
            enum { MAX_BUFFER_LENGTH = 8192 };
            
            char m_inputBuffer[MAX_BUFFER_LENGTH];
        };


        struct HTTPTestServer
        {
            typedef ServerTraits traits;
            
            HTTPTestServer(traits::io_service_type & service, boost::uint16_t port)
            : m_service(service)
            , m_acceptor(service, traits::create_ep(port))
            {
                acceptNextSession();
            }
            
            void handle_accept(HTTPTestSession * pSession, boost::system::error_code const & error)
            {
                if(error)
                {
                    delete pSession;
                    std::cout << "ERROR: " << __FILE__ << ":" << __LINE__ << " " << __func__ << ": Accepting new connection failed. " << error << std::endl;                    
                }
                else
                {
                    pSession->start();
                    acceptNextSession();
                }
            }

            void acceptNextSession()
            {
                HTTPTestSession * pSess = new HTTPTestSession( m_service );
                m_acceptor.async_accept
                (
                    pSess->socket(),
                    boost::bind( &HTTPTestServer::handle_accept, this, pSess, boost::asio::placeholders::error)
                );
            }

        protected:
            traits::io_service_type & m_service;
            traits::acceptor_type     m_acceptor;
        };
    }
}

#endif //GUARD_LIBVW_NETTESTENV_HTTP_TEST_SERVER_H_INCLUDED
