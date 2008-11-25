#include "http_response_parser.h"
#include "byte_buffer_stream_source.h"
#include "../../logger/logger.h"
#include <boost/lexical_cast.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/foreach.hpp>
#include <sstream>
#include <iomanip>
#include <list>
#include <vector>

namespace vw
{
	HTTPResponseParser::HTTPResponseParser(ByteBuffer const & buf)
	: m_buffer(buf)
	, m_response()
	{
		parse();
	}

	HTTPResponseParser::HTTPResponseParser(HTTPResponseParser const & hrp)
	: m_response(hrp.m_response)
	{
	}
	
	HTTPResponseParser::~HTTPResponseParser()
	{
	}

	HTTPResponseParser & HTTPResponseParser::operator=(HTTPResponseParser hrp)
	{
		swap(hrp);
		return *this;
	}

	HTTPResponse const & HTTPResponseParser::get() const
	{
		return m_response;
	}

	HTTPResponse & HTTPResponseParser::get()
	{
		return m_response;
	}

	void HTTPResponseParser::swap(HTTPResponseParser & hrp)
	{
		hrp.m_response.swap(m_response);
	}

	void HTTPResponseParser::parse_header(std::istream & is)
	{
		parse_version(is);
		
		LOG_DBG << "Parse header stream state: " << std::boolalpha << bool(is);

		String line;
		while(std::getline(is, line))
		{
			boost::algorithm::trim_right(line);
			if(line.empty())
			{
				break;
			}		
			//TODO: add multiline header item support
			//TODO: add multiple equal field support

			std::istringstream istr(line);
			String name;
			String value;		
			if((istr >> name) && std::getline(istr,value))
			{
				if(name.empty() || *name.rbegin() != ':')
				{
					LOG_ERR << "Received illformed HTTP response. Header illformed. Illformed data: " << line;
					throw MalformedPacketException();			
				}
				name.erase(name.end()-1);
				m_response.header().field(name) = boost::algorithm::trim_copy(value);
			}
			else
			{
				LOG_ERR << "Received illformed HTTP response. Header illformed. Illformed data: " << line;
				throw MalformedPacketException();
			}
		}
	}

	void HTTPResponseParser::parse_version(std::istream & input)
	{
		LOG_DBG << "Parse version stream state: " << std::boolalpha << bool(input);
		String line;
		if(std::getline(input,line))
		{
			std::istringstream status(line);
			String version;
			if(!(status >> version) || (version != HTTP::VERSION11 && version != HTTP::VERSION10))
			{
				LOG_ERR << "Received illformed HTTP response. Version incorrect. " << version;
				throw MalformedPacketException();
			}			
			
			String code;
			if(!(status >> code) || code.size() != 3)
			{
				LOG_ERR << "Received illformed HTTP response";
				throw MalformedPacketException();
			}			

			String message;
			if(!std::getline(status,message))
			{
				LOG_ERR << "Received illformed HTTP response";
				throw MalformedPacketException();
			}

			try	
			{
				UInt16 numcode = boost::lexical_cast<UInt16>(code);
				if(numcode > 999 || numcode < 100)
				{
					throw MalformedPacketException();
				}
				m_response.header().status_code() 	 = numcode;
				m_response.header().status_message() = boost::algorithm::trim_right_copy(message);
			}
			catch(boost::bad_lexical_cast const &)
			{
				LOG_ERR << "Received illformed HTTP response";
				throw MalformedPacketException();
			}			
		}
	}

	void HTTPResponseParser::parse_chunked(std::istream & is)
	{
		LOG_DBG << "Parse chunked stream state: " << std::boolalpha << bool(is);
		if(!is)
		{
			LOG_ERR << "Received illformed HTTP response";
			throw MalformedPacketException();
		}

		try
		{
			for(;;)
			{
				// consume all whitespaces
				int ch = is.get();		
				while(std::isspace(ch))
				{
					ch = is.get();
				}	
				// Read the hex size
				String len;
				while(std::isxdigit(ch))
				{
					len.push_back(ch);
					ch = is.get();
				}

				// Consume whitespaces
				while (std::isspace(ch) && ch != -1)
				{
					ch = is.get();
				}
				// Put back last read character (Otherwise stream would not contain all data)
				if(ch != -1) 
				{
					is.putback(ch);
				}	

				// Convert hex number to streamsize value
				std::istringstream his(len);
				std::streamsize chunk_len = 0;
				his >> std::hex >> chunk_len;

				// If the chunk_len is 0 we're done in any case
				if(chunk_len == 0)
				{
					return; // we're done
				}

				// Read chunk
				ByteBuffer tmp(chunk_len, 0);
				if(!is.read(reinterpret_cast<char*>(&tmp[0]), chunk_len))
				{
					LOG_ERR << "Received illformed HTTP response. Unexpected end of input reached.";
					throw MalformedPacketException();
				}
				
				// Store chunk
				m_response.content().insert(m_response.content().end(),tmp.begin(),tmp.end());

				// Search for next \n
				while (ch != -1 && ch != '\n')
				{
					ch = is.get();
				}
			}
		}
		catch(boost::bad_lexical_cast const &)
		{
			LOG_ERR << "Received illformed HTTP response.";
			throw MalformedPacketException();
		}	
	}

	void HTTPResponseParser::parse_identity(std::istream & is)
	{
		is >> std::noskipws;
		m_response.content().assign(
			std::istream_iterator<char>(is),
			std::istream_iterator<char>());		
	}
	
	void HTTPResponseParser::parse()
	{
		LOG_DBG << "Parse...";
		std::istream input_stream(&m_buffer);
		LOG_DBG << "Parsing header";
		parse_header(input_stream);
		using boost::algorithm::iequals;
		if(iequals(m_response.header().transfer_encoding(), HTTP::TRANSFER_ENCODING_IDENTITY))
		{
			LOG_DBG << "Parsing identity";
			parse_identity(input_stream);
		}
		else
		{
			LOG_DBG << "Parsing chunked";
			parse_chunked(input_stream);
		}
		LOG_DBG << "End of parse";
	}		
}

