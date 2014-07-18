#include "stdafx.h"

#include <squirrel.h>
#include <sqstdaux.h>
#include <sqstdblob.h>
#include <sqstdio.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdsystem.h>

#include "SquirrelNET.h"

usings

#define ToVM(S) ((HSQUIRRELVM)S.ToPointer())
#define MAKE_FUNC(Name, RootName, RetVal) RetVal Name(IntPtr S) { return RootName(ToVM(S)); }

#ifdef SQUNICODE 
#define scvprintf vfwprintf
#else 
#define scvprintf vfprintf
#endif 

// TODO: Strip this shit off and spread on multiple files

namespace SquirrelNET {
	MAKE_FUNC(Sq::PushRootTable, sq_pushroottable, void);
	MAKE_FUNC(SqStd::SetErrorHandlers, sqstd_seterrorhandlers, void);
	MAKE_FUNC(SqStd::RegisterBlobLib, sqstd_register_bloblib, int);
	MAKE_FUNC(SqStd::RegisterIOLib, sqstd_register_iolib, int);
	MAKE_FUNC(SqStd::RegisterSystemLib, sqstd_register_systemlib, int);
	MAKE_FUNC(SqStd::RegisterMathLib, sqstd_register_mathlib, int);
	MAKE_FUNC(SqStd::RegisterStringLib, sqstd_register_stringlib, int);

	IntPtr Sq::Open(SQInteger S) {
		return IntPtr(sq_open(S));
	}

	void Sq::Close(IntPtr S) {
		sq_close(ToVM(S));
	}

	void Sq::Pop(IntPtr S, SQInteger Count) {
		sq_pop(ToVM(S), Count);
	}

	void Sq::SetPrintFunc(IntPtr S, Sq::PrintFunc^ P, Sq::PrintFunc^ E) {
		sq_setprintfunc(ToVM(S), (SQPRINTFUNCTION)ToFuncPtr(P), (SQPRINTFUNCTION)ToFuncPtr(E));
	}

	Sq::PrintFunc^ Sq::GetPrintFunc(IntPtr S) {
		return ToDelegate(sq_getprintfunc(ToVM(S)), Sq::PrintFunc);
	}

	Sq::PrintFunc^ Sq::GetErrorFunc(IntPtr S) {
		return ToDelegate(sq_geterrorfunc(ToVM(S)), Sq::PrintFunc);
	}

	SQInteger Sq::CompileBuffer(IntPtr S, String^ St, String^ N, bool R) {
		pin_ptr<const SQChar> Str = PtrToStringChars(St);
		pin_ptr<const SQChar> NStr = PtrToStringChars(N);
		return sq_compilebuffer(ToVM(S), Str, St->Length, NStr, R);
	}

	SQInteger Sq::Call(IntPtr S, SQInteger params, SQBool retval, SQBool raiseerror) {
		return sq_call(ToVM(S), params, retval, raiseerror);
	}
}