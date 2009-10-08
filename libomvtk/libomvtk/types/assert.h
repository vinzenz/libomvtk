#ifndef GUARD_LIBOMVTK_TYPES_ASSERT_H_INCLUDED
#define GUARD_LIBOMVTK_TYPES_ASSERT_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include <cassert>

#define libomvtk_ensure(x)				assert(x)
#define libomvtk_assert(x)				poco_assert_dbg(x)
#define libomvtk_bugcheck_msg(x)		poco_bugcheck_msg(x)
#define libomvtk_bugcheck()			poco_bugcheck()
#define libomvtk_check_ptr(x)			poco_check_ptr(x)
#define libomvtk_debugger()			poco_debugger()
#define libomvtk_debugger_msg(x)		poco_debugger_msg(x)


#endif //GUARD_LIBOMVTK_TYPES_ASSERT_H_INCLUDED

