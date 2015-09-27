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
	void Sq::PushRootTable(IntPtr v) {
		sq_pushroottable(ToVM(v));
	}

	void Sq::PushRegistryTable(IntPtr v) {
		sq_pushregistrytable(ToVM(v));
	}

	void Sq::PushConstantTable(IntPtr v) {
		sq_pushconsttable(ToVM(v));
	}

	SQRESULT Sq::SetRootTable(IntPtr v) {
		return sq_setroottable(ToVM(v));
	}

	SQRESULT Sq::SetConstantTable(IntPtr v) {
		return sq_setconsttable(ToVM(v));
	}

	SQRESULT Sq::NewSlot(IntPtr v, SQInteger idx, SQBool bstatic) {
		return sq_newslot(ToVM(v), idx, bstatic);
	}

	SQRESULT Sq::DeleteSlot(IntPtr v, SQInteger idx, SQBool pushval) {
		return sq_deleteslot(ToVM(v), idx, pushval);
	}

	SQRESULT Sq::Set(IntPtr v, SQInteger idx) {
		return sq_set(ToVM(v), idx);
	}

	SQRESULT Sq::Get(IntPtr v, SQInteger idx) {
		return sq_get(ToVM(v), idx);
	}

	SQRESULT Sq::RawGet(IntPtr v, SQInteger idx) {
		return sq_rawget(ToVM(v), idx);
	}

	SQRESULT Sq::RawSet(IntPtr v, SQInteger idx) {
		return sq_rawset(ToVM(v), idx);
	}

	SQRESULT Sq::RawDeleteSlot(IntPtr v, SQInteger idx, SQBool pushval) {
		return sq_rawdeleteslot(ToVM(v), idx, pushval);
	}

	SQRESULT Sq::NewMember(IntPtr v, SQInteger idx, SQBool bstatic) {
		return sq_newmember(ToVM(v), idx, bstatic);
	}

	SQRESULT Sq::RawNewMember(IntPtr v, SQInteger idx, SQBool bstatic) {
		return sq_rawnewmember(ToVM(v), idx, bstatic);
	}

	SQRESULT Sq::ArrayAppend(IntPtr v, SQInteger idx) {
		return sq_arrayappend(ToVM(v), idx);
	}

	SQRESULT Sq::ArrayPop(IntPtr v, SQInteger idx, SQBool pushval) {
		return sq_arraypop(ToVM(v), idx, pushval);
	}

	SQRESULT Sq::ArrayResize(IntPtr v, SQInteger idx, SQInteger newsize) {
		return sq_arrayresize(ToVM(v), idx, newsize);
	}

	SQRESULT Sq::ArrayReverse(IntPtr v, SQInteger idx) {
		return sq_arrayreverse(ToVM(v), idx);
	}

	SQRESULT Sq::ArrayRemove(IntPtr v, SQInteger idx, SQInteger itemidx) {
		return sq_arrayremove(ToVM(v), idx, itemidx);
	}

	SQRESULT Sq::ArrayInsert(IntPtr v, SQInteger idx, SQInteger destpos) {
		return sq_arrayinsert(ToVM(v), idx, destpos);
	}

	SQRESULT Sq::SetDelegate(IntPtr v, SQInteger idx) {
		return sq_setdelegate(ToVM(v), idx);
	}

	SQRESULT Sq::GetDelegate(IntPtr v, SQInteger idx) {
		return sq_getdelegate(ToVM(v), idx);
	}

	SQRESULT Sq::Clone(IntPtr v, SQInteger idx) {
		return sq_clone(ToVM(v), idx);
	}

	SQRESULT Sq::SetFreeVariable(IntPtr v, SQInteger idx, SQUnsignedInteger nval) {
		return sq_setfreevariable(ToVM(v), idx, nval);
	}

	SQRESULT Sq::Next(IntPtr v, SQInteger idx) {
		return sq_next(ToVM(v), idx);
	}

	SQRESULT Sq::GetWeakRefVal(IntPtr v, SQInteger idx) {
		return sq_getweakrefval(ToVM(v), idx);
	}

	SQRESULT Sq::Clear(IntPtr v, SQInteger idx) {
		return sq_clear(ToVM(v), idx);
	}
}