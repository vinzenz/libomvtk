#include "settings.h"
#include "gridclient.h"

namespace omvtk
{
	Settings::Settings(GridClient & gc)
	: boost::noncopyable()
	, m_client(gc)
	, m_mutex()
	, login_uri(m_mutex, "https://login.agni.lindenlab.com/cgi-bin/login.cgi")
	, agni_uri(m_mutex, "https://login.agni.lindenlab.com/cgi-bin/login.cgi")
	, aditi_uri(m_mutex, "https://login.aditi.lindenlab.com/cgi-bin/login.cgi")
	, resource_directory(m_mutex, "../../data/")
	, cache_directory(m_mutex, "../../data/cache/")
	{}			
}

