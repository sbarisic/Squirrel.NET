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
	IntPtr Sq::AllocSQObject() {
		return IntPtr(calloc(1, sizeof(HSQOBJECT)));
	}

	void Sq::FreeSQObject(IntPtr O) {
		free(O.ToPointer());
	}

	SQRESULT Sq::GetStackObj(IntPtr v, SQInteger idx, IntPtr po) {
		HSQOBJECT* O = (HSQOBJECT*)AllocSQObject().ToPointer();
		auto R = sq_getstackobj(ToVM(v), idx, O);
		po = IntPtr(O);
		return R;
	}

	void Sq::PushObject(IntPtr v, IntPtr obj) {
		sq_pushobject(ToVM(v), *(HSQOBJECT*)obj.ToPointer());
	}

	void Sq::AddRef(IntPtr v, IntPtr po) {
		sq_addref(ToVM(v), (HSQOBJECT*)po.ToPointer());
	}

	SQBool Sq::Release(IntPtr v, IntPtr po) {
		return sq_release(ToVM(v), (HSQOBJECT*)po.ToPointer()) != 0;
	}

	SQUnsignedInteger Sq::GetRefCount(IntPtr v, IntPtr po) {
		return sq_getrefcount(ToVM(v), (HSQOBJECT*)po.ToPointer());
	}

	void Sq::ResetObject(IntPtr po) {
		sq_resetobject((HSQOBJECT*)po.ToPointer());
	}

	String^ Sq::ObjToString(IntPtr o) {
		return gcnew String(sq_objtostring((HSQOBJECT*)o.ToPointer()));
	}

	SQBool Sq::ObjToBool(IntPtr o) {
		return sq_objtobool((HSQOBJECT*)o.ToPointer()) != 0;
	}
	
	SQInteger Sq::ObjToInt(IntPtr o) {
		return sq_objtointeger((HSQOBJECT*)o.ToPointer());
	}

	SQFloat Sq::ObjToFloat(IntPtr o) {
		return sq_objtofloat((HSQOBJECT*)o.ToPointer());
	}

	IntPtr Sq::ObjToUserPointer(IntPtr o) {
		return IntPtr(sq_objtouserpointer((HSQOBJECT*)o.ToPointer()));
	}

	SQRESULT Sq::GetObjTypeTag(IntPtr o, OUT(IntPtr) TypeTag) {
		SQUserPointer* P = 0;
		auto R = sq_getobjtypetag((HSQOBJECT*)o.ToPointer(), P);
		TypeTag = IntPtr(P);
		return R;
	}

	SQObjectType Sq::Type(IntPtr o) {
		return (SQObjectType)(((HSQOBJECT*)o.ToPointer())->_type);
	}
}