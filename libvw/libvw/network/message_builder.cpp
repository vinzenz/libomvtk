#include "message_builder.h"
#include "network.h"
#include "simulator.h"
#include "../packets/packets.h"

namespace
{
	struct MessageBuilder
	{
		MessageBuilder(vw::Network & net, vw::Simulator & sim, vw::ByteBuffer & buf)
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
		vw::Network * m_net;
		vw::Simulator * m_sim;
		vw::ByteBuffer * m_buf;	
	};
}	
namespace vw
{
	void build_message(Network & net, Simulator & sim, ByteBuffer & buf, UInt32 id)
	{
		MessageBuilder builder(net, sim, buf);
		packets::Lookup(id, builder);
	}
}

