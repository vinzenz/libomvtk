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
#include "caps_event.h"
#include <boost/pool/detail/singleton.hpp>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/preprocessor/stringize.hpp>

namespace omvtk
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
            typedef boost::bimaps::tagged<CapsEvent,by_id>     tag_cap;
            typedef boost::bimaps::tagged<String,by_name>       tag_name;
            typedef boost::bimaps::unordered_set_of<tag_cap>     impl_cap;
            typedef boost::bimaps::unordered_set_of<tag_name>     impl_name;
            typedef boost::bimaps::bimap<impl_cap,impl_name>     container;
            typedef container::map_by<by_id>                     mapped_by_id;
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
#define OMVTK_CAPS_ADD(EVT) add(EVT,(BOOST_STRINGIZE(EVT)))
            OMVTK_CAPS_ADD(EventQueueGet);
#undef     OMVTK_CAPS_ADD
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

