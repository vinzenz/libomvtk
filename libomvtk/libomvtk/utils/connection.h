#ifndef GUARD_LIBOMVTK_UTILS_CONNECTION_H_INCLUDED
#define GUARD_LIBOMVTK_UTILS_CONNECTION_H_INCLUDED

#include <boost/noncopyable.hpp>

namespace omvtk
{
	namespace detail
	{
		template<typename SlotT, typename IdT>
		struct Connection : boost::noncopyable
		{
			Connection(IdT id)
				: m_slot(0)
				, m_id(id)
			{}

			~Connection()
			{
				disconnect();
			}

			IdT const & id() const
			{
				return m_id;
			}

			bool is_connected() const
			{
				return m_slot != 0;
			}

			void disconnect()
			{
				if(m_slot)
				{
					m_slot->disconnect(*this);
					m_slot = 0;
				}
			}

			void connect(SlotT & slot)
			{
				disconnect();
				m_slot = &slot;
			}			
		protected:
			SlotT * m_slot;
			IdT m_id;
		};
	}
}

#endif //GUARD_LIBOMVTK_UTILS_CONNECTION_H_INCLUDED

