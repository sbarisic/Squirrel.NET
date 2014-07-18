#include "stdafx.h"

#include <squirrel.h>
#include <sqstdaux.h>
#include <sqstdblob.h>
#include <sqstdio.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdsystem.h>

#include "SquirrelNET.h"

usings;

#define MAKE_FUNC(Name, RootName, RetVal) RetVal Name(IntPtr S) { return RootName(ToVM(S)); }

namespace SquirrelNET {
	MAKE_FUNC(SqStd::SetErrorHandlers, sqstd_seterrorhandlers, void);
	MAKE_FUNC(SqStd::RegisterBlobLib, sqstd_register_bloblib, int);
	MAKE_FUNC(SqStd::RegisterIOLib, sqstd_register_iolib, int);
	MAKE_FUNC(SqStd::RegisterSystemLib, sqstd_register_systemlib, int);
	MAKE_FUNC(SqStd::RegisterMathLib, sqstd_register_mathlib, int);
	MAKE_FUNC(SqStd::RegisterStringLib, sqstd_register_stringlib, int);
}