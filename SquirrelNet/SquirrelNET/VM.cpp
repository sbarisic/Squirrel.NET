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
	IntPtr Sq::Open(SQInteger S) {
		return IntPtr(sq_open(S));
	}

	IntPtr Sq::NewThread(IntPtr friendvm, SQInteger initialstacksize) { 
		return IntPtr(sq_newthread(ToVM(friendvm), initialstacksize));
	}

	void Sq::SetErrorHandler(IntPtr v) {
		sq_seterrorhandler(ToVM(v));
	}

	void Sq::Close(IntPtr v) {
		sq_close(ToVM(v));
	}

	void Sq::SetForeignPtr(IntPtr v, IntPtr p) {
		sq_setforeignptr(ToVM(v), p.ToPointer());
	}

	IntPtr Sq::GetForeignPtr(IntPtr v) {
		return IntPtr(sq_getforeignptr(ToVM(v)));
	}

	void Sq::SetPrintFunc(IntPtr v, PrintFunc^ printfunc, PrintFunc^ errfunc) {
		sq_setprintfunc(ToVM(v), (SQPRINTFUNCTION)ToFuncPtr(printfunc), (SQPRINTFUNCTION)ToFuncPtr(errfunc));
	}

	Sq::PrintFunc^ Sq::GetPrintFunc(IntPtr v) {
		return ToDelegate(sq_getprintfunc(ToVM(v)), Sq::PrintFunc);
	}

	Sq::PrintFunc^ Sq::GetErrorFunc(IntPtr v) {
		return ToDelegate(sq_geterrorfunc(ToVM(v)), Sq::PrintFunc);
	}

	SQRESULT Sq::SuspendVM(IntPtr v) {
		return sq_suspendvm(ToVM(v));
	}

	SQRESULT Sq::WakeupVM(IntPtr v, bool resumedret, bool retval, bool raiseerror, bool throwerror) {
		return sq_wakeupvm(ToVM(v), resumedret, retval, raiseerror, throwerror);
	}

	SQInteger Sq::GetVMState(IntPtr v) {
		return sq_getvmstate(ToVM(v));
	}

	SQInteger Sq::GetVersion() {
		return sq_getversion();
	}
}