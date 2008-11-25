#include "network.h"
#include "../packets/packets.h"
#include "../gridclient.h"

namespace vw
{

	Network::Network(GridClient & client)
		: m_client(client)
		, m_handler_manager()
		, m_id()
		, m_session_id()
		, m_circuit_code(~UInt32(0))
	{
	}

	Network::~Network()
	{
	}

	LLUUID Network::id() const
	{
		return m_id;
	}
	
	void Network::id(LLUUID const & id_)
	{
		m_id = id_;
	}

	LLUUID Network::session_id() const
	{
		return m_session_id;
	}
	
	void Network::session_id(LLUUID const & sess_id)
	{
		m_session_id = sess_id;
	}

	UInt32 Network::circuit_code() const
	{
		return m_circuit_code;
	}

	void Network::circuit_code(UInt32 code)
	{
		m_circuit_code = code;
	}

	boost::asio::io_service & Network::service()
	{
		return m_client.library().service();
	}

	boost::asio::io_service const & Network::service() const
	{
		return m_client.library().service();
	}

	boost::asio::ssl::context & Network::context()
	{
		return m_client.library().context();
	}

	boost::asio::ssl::context const & Network::context() const
	{
		return m_client.library().context();
	}

	Network::HandlerManager const & Network::handler() const
	{
		return m_handler_manager;
	}
	
	Network::HandlerManager & Network::handler()
	{
		return m_handler_manager;
	}
	
	void Network::get_circuit_code(packets::UseCircuitCodeMessage& msg)
	{
		msg.CircuitCode.Code = m_circuit_code;
		msg.CircuitCode.SessionID = m_session_id;
		msg.CircuitCode.ID = m_id;
	}		
}
