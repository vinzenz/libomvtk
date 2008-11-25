#include "gridclient.h"
#include "settings.h"
#include "library.h"

namespace omvtk
{
	GridClient::GridClient()
	: m_library()
	, m_settings(*this)
	, m_network(*this)
	{}
	
	Network & GridClient::network()
	{
		return m_network;
	}

	Network const & GridClient::network() const
	{
		return m_network;
	}

	Settings & GridClient::settings()
	{
		return m_settings;
	}

	Settings const & GridClient::settings() const
	{
		return m_settings;
	}

	Library & GridClient::library()
	{
		return m_library;
	}
	
	Library const & GridClient::library() const
	{
		return m_library;
	}
}

