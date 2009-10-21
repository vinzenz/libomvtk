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
#ifndef GUARD_OMVTK_NETWORK_HTTP_REQUEST_RESULT_H_INCLUDED
#define GUARD_OMVTK_NETWORK_HTTP_REQUEST_RESULT_H_INCLUDED

#include "response.h"

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>
#include "traits/locking_traits.h"
#include "traits/request_id_traits.h"
#include "detail/exceptions.h"

#include <list>

namespace omvtk {
    namespace http {

        namespace state {
            enum states {
                queued,
                connecting,
                connected,
                transfering_request,
                waiting_for_response,
                transfering_headers,
                headers_received,
                transfering_body,
                finished,
                failure
            };
        }
        template < typename Tag >
        struct basic_http_session;

        template< typename Tag >
        struct basic_request_result 
        : locking_traits< Tag >::type {
            typedef typename locking_traits< Tag >::type            locking_type;
            typedef typename locking_type::read_lock                read_lock;
            typedef typename locking_type::write_lock               write_lock;
            typedef basic_response< Tag >                           response_type;
            typedef boost::shared_ptr< response_type >              response_type_ptr;
            typedef state::states                                   state_type;
            typedef typename request_id_traits< Tag >::type         request_id_type;
            typedef boost::system::error_code                       error_type;
            typedef boost::function< void( basic_request_result ) > callback_type;

            basic_request_result( request_id_type const & id, state::states initial_state = state::queued )
            : locking_type()
            , state_( initial_state )
            , id_( id )
            , error_()
            , response_()
            , callback_()
            , ready_( false )
            {}

            state_type state() const {
                read_lock lock(this->mutex_);
                return state_;
            }
            
            request_id_type id() const {
                read_lock lock(this->mutex_);
                return id_;
            }

            bool ready() const {
                read_lock lock(this->mutex_);
                return ready_ > 0l;
            }

            response_type const & response() const {
                // We're locking only for ready_ to check that 
                // no one else might use this
                read_lock lock(this->mutex_);
                if ( !ready_ ) {
                    boost::throw_exception(request_not_finished_error());
                }
                return *response_;
            }

            response_type & response() {
                // We're locking only for ready_ to check that 
                // no one else might use this
                read_lock lock(this->mutex_);
                if ( !ready_ ) {
                    boost::throw_exception(request_not_finished_error());
                }
                return *response_;
            }

            error_type error() const {
                read_lock lock(this->mutex_);
                return error_;
            }

            void set_callback( callback_type const & callback, bool replace = false ) {
                if( !replace && has_callback() ) {
                    boost::throw_exception( handler_already_specified_error() );
                }
                write_lock lock(this->mutex_);
                callback_ = callback;
            }

            void unset_callback() {
                write_lock lock(this->mutex_);
                callback_ = callback_type();
            }

            bool has_callback() const {
                read_lock lock(this->mutex_);
                return bool( callback_ );
            }

        protected:
            friend struct basic_http_session< Tag >;
            
            template< typename Service >
            void state_updated( Service & s ) {
                read_lock lock(this->mutex_);
                if( state_ == state::finished ||  state_ == state::failure ) {
                    // First we mark ourselves as ready()
                    ready_ = true;
                    s.post( boost::bind( callback_, *this ) );
                }
            }

        protected:
            state_type                  state_;
            request_id_type             id_;
            error_type                  error_;
            response_type_ptr           response_;
            callback_type               callback_;
            bool                        ready_;
        };
    }
}

#endif //GUARD_OMVTK_NETWORK_HTTP_REQUEST_RESULT_H_INCLUDED
