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
#ifndef GUARD_LIBOMVTK_TYPES_ERROR_H_INCLUDED
#define GUARD_LIBOMVTK_TYPES_ERROR_H_INCLUDED

#include <boost/system/error_code.hpp>

namespace omvtk {
    typedef boost::system::error_code ErrorCode;

    namespace error {
        // Specification of the error codes
        // Note, if you add an error add also the message to error.cpp :-)
        enum omvtk_error_codes {
            NoError = 0,
            InvalidOrCorruptedProtocol
        };        
    }
}

namespace boost { 
    namespace system {
        template<> 
        struct is_error_code_enum < 
            omvtk::error::omvtk_error_codes
        >
        { 
            static const bool value = true; 
        };
    }
}

namespace omvtk {
    namespace error {
        // Implementation of necessary things for this purpose
        boost::system::error_category const & get_omvtk_error_category();
        static boost::system::error_category const & category = get_omvtk_error_category();

        inline boost::system::error_code make_error_code( omvtk_error_codes e ) {
            return boost::system::error_code( e, category );
        }
    }
}



#endif //GUARD_LIBOMVTK_TYPES_ERROR_H_INCLUDED
