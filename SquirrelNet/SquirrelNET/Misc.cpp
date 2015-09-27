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
	SQInteger Sq::CollectGarbage(IntPtr v) {
		return sq_collectgarbage(ToVM(v));
	}

	SQRESULT Sq::ResurrectUnreachable(IntPtr v) {
		return sq_resurrectunreachable(ToVM(v));
	}

	SQRESULT Sq::WriteClosure(IntPtr vm, Sq::WriteFunc^ writef, IntPtr up) {
		return sq_writeclosure(ToVM(vm), (SQWRITEFUNC)ToFuncPtr(writef), up.ToPointer());
	}

	SQRESULT Sq::ReadClosure(IntPtr vm, Sq::ReadFunc^ readf, IntPtr up) {
		return sq_readclosure(ToVM(vm), (SQREADFUNC)ToFuncPtr(readf), up.ToPointer());
	}

	IntPtr Sq::Malloc(SQUnsignedInteger size) {
		return IntPtr(sq_malloc(size));
	}

	IntPtr Sq::Realloc(IntPtr p, SQUnsignedInteger oldsize, SQUnsignedInteger newsize) {
		return IntPtr(sq_realloc(p.ToPointer(), oldsize, newsize));
	}

	void Sq::Free(IntPtr p, SQUnsignedInteger size) {
		sq_free(p.ToPointer(), size);
	}

	SQRESULT Sq::StackInfos(IntPtr v, SQInteger level, IntPtr si) {
		tagSQStackInfos* SInf = 0;
		auto R = sq_stackinfos(ToVM(v), level, SInf); 
		si = IntPtr(SInf);
		return R;
	}

	void Sq::SetDebugHook(IntPtr v) {
		sq_setdebughook(ToVM(v));
	}

	void Sq::SetNativeDebugHook(IntPtr v, Sq::DebugHook^ hook) {
		sq_setnativedebughook(ToVM(v), (SQDEBUGHOOK)ToFuncPtr(hook));
	}
}