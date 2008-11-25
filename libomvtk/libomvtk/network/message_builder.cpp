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

