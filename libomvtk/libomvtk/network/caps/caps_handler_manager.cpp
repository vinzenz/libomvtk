#include "caps_handler_manager.h"

namespace omvtk
{
	CapsHandlerManager::CapsHandlerManager()
	: m_handler_map()
	{}
		
	CapsHandlerManager::~CapsHandlerManager()
	{
		std::vector<ConnectionT*> ptrs(m_handler_map.size(),0);
		for(HandlerMap::iterator it = m_handler_map.begin(); it != m_handler_map.end(); ++it)
		{
			ptrs.push_back(it->second.ptr);
		}

		BOOST_FOREACH(ConnectionT * p, ptrs)
		{
			if(p)
			{
				p->disconnect();
			}
		}			
	}

	std::size_t CapsHandlerManager::count(CapsEvent event_id) const
	{
		return m_handler_map.count(event_id);
	}

	std::size_t CapsHandlerManager::size() const
	{
		return m_handler_map.size();
	}
	bool CapsHandlerManager::empty() const
	{
		return m_handler_map.empty();
	}
	
	void CapsHandlerManager::operator()(CapsEvent event_id, boost::shared_ptr<LLSDValue> value, Simulator & sender)
	{
		if(count(event_id))
		{
			typedef HandlerMap::iterator iter;
			std::pair<iter, iter> iterp = m_handler_map.equal_range(event_id);
			for(;iterp.first != iterp.second; ++iterp.first)
			{
				if(iterp.first->second.ptr)
				{
					iterp.first->second.caller_fun(iterp.first->second.ptr,value,sender);					
				}
			}
		}	
	}

	void CapsHandlerManager::disconnect(ConnectionT & msg)	
	{
		std::pair<HandlerMap::iterator,HandlerMap::iterator> iter;
		iter = m_handler_map.equal_range(msg.id());
		for(;iter.first != iter.second;++iter.first)
		{
			if(iter.first->second.ptr == &msg)
			{
				m_handler_map.erase(iter.first);
				return;
			}
		}
	}
}

