#include "message_handler_manager.h"
#include <list>

namespace omvtk
{
	MessageHandlerManager::MessageHandlerManager()
	{

	}

	MessageHandlerManager::~MessageHandlerManager()
	{
		std::vector<Data::Ptr> ptrs(m_handler_map.size(),0);
		for(HandlerMap::iterator it = m_handler_map.begin(); it != m_handler_map.end(); ++it)
		{
			ptrs.push_back(it->second.ptr);
		}

		BOOST_FOREACH(Data::Ptr p, ptrs)
		{
			if(p)
			{
				p->disconnect();
			}
		}			
	}

	void MessageHandlerManager::notify(UInt32 id, packets::Message const & msg, Simulator & sender)
	{
		std::pair<HandlerMap::iterator,HandlerMap::iterator> iter;
		iter = m_handler_map.equal_range(id);
		for(;iter.first != iter.second;++iter.first)
		{
			if(iter.first->second.ptr)
			{
				iter.first->second.caller(iter.first->second.ptr,msg,sender);					
			}
		}
	}

	void MessageHandlerManager::disconnect(ConnectionT & msg)
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

	std::size_t MessageHandlerManager::count(UInt32 id) const
	{
		return m_handler_map.count(id);
	}

	std::size_t MessageHandlerManager::size() const
	{
		return m_handler_map.size();
	}

	bool MessageHandlerManager::empty() const
	{
		return m_handler_map.empty();
	}
}

