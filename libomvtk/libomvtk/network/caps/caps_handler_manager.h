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
#ifndef GUARD_LIBOMVTK_NETWORK_CAPS_HANDLER_MANAGER_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_CAPS_HANDLER_MANAGER_H_INCLUDED

#include "caps_event.h"
#include "../../utils/connection.h"
#include "../../llsd/value.h"
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

namespace omvtk
{
    struct Simulator;

    template<CapsEvent EventID>
    struct CapsHandler;

    struct CapsHandlerManager 
    {
        typedef detail::Connection<CapsHandlerManager,CapsEvent> ConnectionT;
        typedef boost::shared_ptr<LLSDValue> LLSDPtr;

        struct Data
        {
            typedef void (*caller_fun_t)(ConnectionT *, LLSDPtr, Simulator &);
            Data()
            : ptr(0)
            , caller_fun(0)
            {}

            template<CapsEvent event_id>
            Data(CapsHandler<event_id> & p)
            : ptr(&p)
            , caller_fun(caller_fun_t(&Data::template caller<event_id>))
            {
            }

            ConnectionT * ptr;                        
            caller_fun_t caller_fun;

            template<CapsEvent event_id>
            static void caller(ConnectionT * ptr, LLSDPtr value, Simulator & sender)
            {
                if(ptr)
                (*static_cast<CapsHandler<event_id>*>(ptr))(value,sender);
            }
        };
    
        typedef boost::unordered_map<CapsEvent, Data> HandlerMap;            

        CapsHandlerManager();
        ~CapsHandlerManager();

        // Check how many handlers are registered for the given event id
        std::size_t count(CapsEvent event_id) const;
        // Check how many handlers are registered 
        std::size_t size() const;
        // returns true if no handlers are registered
        bool empty() const;

        // Connects a caps event handler
        template<CapsEvent event_id>
        void connect(CapsHandler<event_id> & connection)
        {
            m_handler_map.insert(HandlerMap::value_type(event_id, Data(connection)));    
            connection.connect(*this);
        }

        // Disconnects a handler
        void disconnect(ConnectionT & msg);

        void operator()(CapsEvent event_id, LLSDPtr value, Simulator & sender);
    protected:
        HandlerMap m_handler_map;
    };
}



#endif //GUARD_LIBOMVTK_NETWORK_CAPS_HANDLER_MANAGER_H_INCLUDED

