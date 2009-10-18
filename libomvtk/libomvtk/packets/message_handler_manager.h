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
#ifndef GUARD_LIBOMVTK_PACKETS_MESSAGE_MANAGER_H_INCLUDED
#define GUARD_LIBOMVTK_PACKETS_MESSAGE_MANAGER_H_INCLUDED

#include <map>

#include "../utils/connection.h"
#include "../types/base_types.h"
#include "header.h"

namespace omvtk
{
    struct Simulator;
    
    template<typename> 
    struct MessageHandler;

    struct MessageHandlerManager 
    {    
        typedef detail::Connection<MessageHandlerManager,UInt32> ConnectionT;

        struct Data
        {
            typedef ConnectionT * Ptr;
            typedef void (*CallerFunT)(Ptr p, packets::Message const &, Simulator &);
            Ptr ptr;
            CallerFunT caller;            
            template<typename T>
            static void caller_fun(Ptr p, packets::Message const & msg, Simulator & sender)
            {
                static_cast<MessageHandler<T>*>(p)->call(msg,sender);
            }
        };
        typedef std::multimap<UInt32, Data> HandlerMap;            

        MessageHandlerManager();
        ~MessageHandlerManager();

        template <typename MessageT>
        std::size_t count() const
        {
            return count(MessageT::id);
        }

        std::size_t count(UInt32 id) const;
        std::size_t size() const;
        bool empty() const;

        template<typename MessageT>
        void connect(MessageHandler<MessageT> & handler)
        {
            Data data;
            data.ptr = &handler;
            data.caller = &Data::caller_fun<MessageT>;
            m_handler_map.insert(HandlerMap::value_type(MessageT::id,data));
            handler.connect(*this);
        }

        template<typename MessageT>
        void operator()(MessageT const & msg, Simulator & sender)
        {
            notify(MessageT::id, msg, sender);
        }

        void disconnect(ConnectionT & msg);
    protected:
        void notify(UInt32 id, packets::Message const & msg, Simulator & sender);
        HandlerMap m_handler_map;
    };

}

#ifndef GUARD_LIBOMVTK_PACKETS_MESSAGE_HANDLER_H_INCLUDED
#    include "message_handler.h"
#endif

#endif //GUARD_LIBOMVTK_PACKETS_MESSAGE_MANAGER_H_INCLUDED
