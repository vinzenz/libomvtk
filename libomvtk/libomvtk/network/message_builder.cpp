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
#include "message_builder.h"
#include "network.h"
#include "simulator.h"
#include "../packets/packets.h"

namespace
{
	struct MessageBuilder
	{
		MessageBuilder(omvtk::Network & net, omvtk::Simulator & sim, omvtk::ByteBuffer & buf)
			: m_net(&net)
			, m_sim(&sim)
			, m_buf(&buf)			
		{
		}

		template<typename T>
		void apply()
		{
			std::size_t pos;
			T msg(*m_buf, pos);

			if(pos == m_buf->size())
			{
				m_net->messages_manager()(msg, *m_sim);
			}			
		}	

	protected:
		omvtk::Network * m_net;
		omvtk::Simulator * m_sim;
		omvtk::ByteBuffer * m_buf;	
	};
}	
namespace omvtk
{
	void build_message(Network & net, Simulator & sim, ByteBuffer & buf, UInt32 id)
	{
		MessageBuilder builder(net, sim, buf);
		packets::Lookup(id, builder);
	}
}

