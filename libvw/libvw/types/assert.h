#ifndef GUARD_LIBVW_TYPES_ASSERT_H_INCLUDED
#define GUARD_LIBVW_TYPES_ASSERT_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include <Poco/Bugcheck.h>

#define libvw_ensure(x)				poco_assert(x)
#define libvw_assert(x)				poco_assert_dbg(x)
#define libvw_bugcheck_msg(x)		poco_bugcheck_msg(x)
#define libvw_bugcheck()			poco_bugcheck()
#define libvw_check_ptr(x)			poco_check_ptr(x)
#define libvw_debugger()			poco_debugger()
#define libvw_debugger_msg(x)		poco_debugger_msg(x)


#endif //GUARD_LIBVW_TYPES_ASSERT_H_INCLUDED

