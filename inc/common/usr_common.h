#pragma once

#include <windows.h>
#include <winbase.h>
#include <assert.h>
#include <stdint.h>

#include <memory>
#include <algorithm>
#include <functional>
#include <string>
#include <atomic>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

#include <thread>
//#include <boost/thread.hpp>

#ifndef VS
#define sprintf_s snprintf
#endif

#ifndef _THREAD_
#ifndef CYGWIN
#ifndef UNIX
#include <common/mingw/mingw.thread.h>
#endif
#endif
#endif


#define POWER2(exp) ((size_t)1 << (exp))
#define MEMBER(cast, ptr, member) reinterpret_cast<cast*>(reinterpret_cast<size_t>(ptr) + static_cast<size_t>(member))
#define BOOLIFY(x) !!(x)

#ifndef CONTAINING_RECORD
#define CONTAINING_RECORD(address, type, field) ((type *)( \
	(PCHAR)(address)-\
	(ULONG_PTR)(&((type *)0)->field)))
#endif

#ifndef __in
#define UNUSED(x) x __attribute__((unused))
#define UNREFERENCED_PARAM(x)
#define FORCE_INLINE __attribute__((always_inline)) 
#else
#define UNUSED(x) x
#define UNREFERENCED_PARAM(x) (x)
#define FORCE_INLINE __forceinline
#endif

static const size_t UNDEF = -1;

#define __inX
#define __outX

#ifndef __in

#include "sal.h"

#endif

/* _countof helper */
#if !defined (_countof)
#if defined (__cplusplus)
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#else  /* !defined (__cplusplus) */
extern "C++"
{
	template <typename _CountofType, size_t _SizeOfArray>
	char(*__countof_helper(_UNALIGNED _CountofType(&_Array)[_SizeOfArray]))[_SizeOfArray];
#define _countof(_Array) (sizeof(*__countof_helper(_Array)) + 0)
}
#endif  /* !defined (__cplusplus) */
#endif  /* !defined (_countof) */

//hmm rethink where this should belongs
namespace common
{
	static const size_t g_sInvalid = static_cast<size_t>(-1);
	static const size_t g_sPageSize = 0x1000;
};
