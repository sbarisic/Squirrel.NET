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
	void Sq::Push(IntPtr v, SQInteger idx) {
		sq_push(ToVM(v), idx);
	}

	void Sq::Pop(IntPtr v, SQInteger nelemstopop) {
		sq_pop(ToVM(v), nelemstopop);
	}

	void Sq::PopTop(IntPtr v) {
		sq_poptop(ToVM(v));
	}

	void Sq::Remove(IntPtr v, SQInteger idx) {
		sq_remove(ToVM(v), idx);
	}

	SQInteger Sq::GetTop(IntPtr v) {
		return sq_gettop(ToVM(v));
	}

	void Sq::SetTop(IntPtr v, SQInteger newtop) {
		sq_settop(ToVM(v), newtop);
	}

	SQRESULT Sq::ReserveStack(IntPtr v, SQInteger nsize) {
		return sq_reservestack(ToVM(v), nsize);
	}

	SQInteger Sq::Cmp(IntPtr v) {
		return sq_cmp(ToVM(v));
	}

	void Sq::Move(IntPtr dest, IntPtr src, SQInteger idx) {
		sq_move(ToVM(dest), ToVM(src), idx);
	}
}