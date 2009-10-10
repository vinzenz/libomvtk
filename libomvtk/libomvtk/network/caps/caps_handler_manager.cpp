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

