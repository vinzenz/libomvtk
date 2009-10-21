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

#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>

namespace omvtk {
    namespace http {
        namespace detail {
            struct write_lock {
                write_lock(boost::shared_mutex & m)
                : lock_(m)
                , unique_(lock_)
                {}
                    
                boost::upgrade_lock<boost::shared_mutex> lock_;
                boost::upgrade_to_unique_lock<boost::shared_mutex> unique_;
            };

            struct read_lock {
                read_lock(boost::shared_mutex & m)
                : lock_(m)
                {}
                
                boost::shared_lock<boost::shared_mutex> lock_;
            };
        }
        
        template< typename Tag >
        struct locking_traits {
            struct type {
                typedef detail::read_lock    read_lock; 
                typedef detail::write_lock   write_lock;
                
                type()
                : mutex_()
                {}
                
            protected:
                mutable boost::shared_mutex  mutex_;
            };
        };
    }
}
