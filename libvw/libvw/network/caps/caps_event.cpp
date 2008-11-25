#include "caps_event.h"
#include <boost/pool/detail/singleton.hpp>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/preprocessor/stringize.hpp>

namespace vw
{
	namespace detail
	{
		using boost::bimaps::tagged;
		using boost::bimaps::bimap;
		using boost::bimaps::unordered_set_of;

		class CapsEventLookupImpl
		{		
			struct by_id  {};
			struct by_name {};
			typedef boost::bimaps::tagged<CapsEvent,by_id> 	tag_cap;
			typedef boost::bimaps::tagged<String,by_name>   	tag_name;
			typedef boost::bimaps::unordered_set_of<tag_cap> 	impl_cap;
			typedef boost::bimaps::unordered_set_of<tag_name> 	impl_name;
			typedef boost::bimaps::bimap<impl_cap,impl_name> 	container;
			typedef container::map_by<by_id> 					mapped_by_id;
		public:

			CapsEventLookupImpl()
			: m_map()
			{
				init();
			}

			CapsEvent lookup(String const & name) const
			{
				return m_map.by<by_name>().find(name)->second;
			}
			
			String const & lookup(CapsEvent event_id) const
			{
				return m_map.by<by_id>().find(event_id)->second;
			}

		protected:
			void init();

			void add(CapsEvent evt,String const & name)
			{
				m_map.by<by_id>().insert
				(
					mapped_by_id::value_type(evt,name)
				);	
			}

			container m_map;
		};

		void CapsEventLookupImpl::init()
		{
#define VW_CAPS_ADD(EVT) add(EVT,(BOOST_STRINGIZE(EVT)))
			VW_CAPS_ADD(EventQueueGet);
#undef 	VW_CAPS_ADD
		}

		typedef boost::details::pool::singleton_default<CapsEventLookupImpl> CapsEventLookup;
	}

	CapsEvent CapsEventLookup::lookup(String const & name)
	{
		return detail::CapsEventLookup::instance().lookup(name);
	}	
	
	String const & CapsEventLookup::lookup(CapsEvent event_id)
	{
		return detail::CapsEventLookup::instance().lookup(event_id);
	}	
}

