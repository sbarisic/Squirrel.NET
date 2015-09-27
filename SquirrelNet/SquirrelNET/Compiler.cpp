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
	SQRESULT Sq::Compile(IntPtr v, Sq::LexReadFunc^ read, IntPtr p, String^ sourcename, bool raiseerror) {
		GetSQCharPtr(sourcename, SrcN);
		return sq_compile(ToVM(v), (SQLEXREADFUNC)ToFuncPtr(read), p.ToPointer(), SrcN, raiseerror);
	}

	SQRESULT Sq::CompileBuffer(IntPtr v, String^ Src, String^ SrcName, bool raiseerror) {
		GetSQCharPtr(Src, Str);
		GetSQCharPtr(SrcName, NStr);
		return sq_compilebuffer(ToVM(v), Str, Src->Length, NStr, raiseerror);
	}

	void Sq::EnableDebugInfo(IntPtr v, bool enable) {
		sq_enabledebuginfo(ToVM(v), enable);
	}

	void Sq::NotifyAllExceptions(IntPtr v, bool enable) {
		sq_notifyallexceptions(ToVM(v), enable);
	}

	void Sq::SetCompilerErrorHandler(IntPtr v, Sq::CompilerError^ f) {
		sq_setcompilererrorhandler(ToVM(v), (SQCOMPILERERROR)ToFuncPtr(f));
	}
}