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

namespace SquirrelNET {
	SQRESULT Sq::Call(IntPtr v, SQInteger params, SQBool retval, SQBool raiseerror) {
		return sq_call(ToVM(v), params, retval, raiseerror);
	}

	SQRESULT Sq::Resume(IntPtr v, SQBool retval, SQBool raiseerror) {
		return sq_resume(ToVM(v), retval, raiseerror);
	}

	String^ Sq::GetLocal(IntPtr v, SQUnsignedInteger level, SQUnsignedInteger idx) {
		return gcnew String(sq_getlocal(ToVM(v), level, idx));
	}

	SQRESULT Sq::GetCallee(IntPtr v) {
		return sq_getcallee(ToVM(v));
	}

	String^ Sq::GetFreeVariable(IntPtr v, SQInteger idx, SQUnsignedInteger nval) {
		return gcnew String(sq_getfreevariable(ToVM(v), idx, nval));
	}

	SQRESULT Sq::ThrowError(IntPtr v, String^ err) {
		GetSQCharPtr(err, Err);
		return sq_throwerror(ToVM(v), Err);
	}

	SQRESULT Sq::ThrowObject(IntPtr v) {
		return sq_throwobject(ToVM(v));
	}

	void Sq::ResetError(IntPtr v) {
		sq_reseterror(ToVM(v));
	}

	void Sq::GetLastError(IntPtr v) {
		sq_getlasterror(ToVM(v));
	}
}