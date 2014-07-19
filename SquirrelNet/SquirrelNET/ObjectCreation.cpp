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
	IntPtr Sq::NewUserdata(IntPtr v, SQUnsignedInteger size) {
		return IntPtr(sq_newuserdata(ToVM(v), size));
	}

	void Sq::NewTable(IntPtr v) {
		sq_newtable(ToVM(v));
	}

	void Sq::NewTableEx(IntPtr v, SQInteger initialcapacity) {
		sq_newtableex(ToVM(v), initialcapacity);
	}

	void Sq::NewArray(IntPtr v, SQInteger size) {
		sq_newarray(ToVM(v), size);
	}

	void Sq::NewClosure(IntPtr v, Function^ func, SQUnsignedInteger nfreevars) {
		sq_newclosure(ToVM(v), (SQFUNCTION)ToFuncPtr(func), nfreevars);
	}

	SQRESULT Sq::SetParamsCheck(IntPtr v, SQInteger nparamscheck, String^ typemask) {
		GetSQCharPtr(typemask, Typemsk);
		return sq_setparamscheck(ToVM(v), nparamscheck, Typemsk);
	}

	SQRESULT Sq::BindEnv(IntPtr v, SQInteger idx) {
		return sq_bindenv(ToVM(v), idx);
	}

	void Sq::PushString(IntPtr v, String^ s) {
		GetSQCharPtr(s, S);
		sq_pushstring(ToVM(v), S, s->Length);
	}

	void Sq::PushFloat(IntPtr v, SQFloat f) {
		sq_pushfloat(ToVM(v), f);
	}

	void Sq::PushInteger(IntPtr v, SQInteger n) {
		sq_pushinteger(ToVM(v), n);
	}

	void Sq::PushBool(IntPtr v, SQBool b) {
		sq_pushbool(ToVM(v), b);
	}

	void Sq::PushUserPointer(IntPtr v, IntPtr p) {
		sq_pushuserpointer(ToVM(v), p.ToPointer());
	}

	void Sq::PushNull(IntPtr v) {
		sq_pushnull(ToVM(v));
	}

	SQObjectType Sq::GetType(IntPtr v, SQInteger idx) {
		return (SQObjectType)sq_gettype(ToVM(v), idx);
	}

	SQRESULT Sq::TypeOf(IntPtr v, SQInteger idx) {
		return sq_typeof(ToVM(v), idx);
	}

	SQInteger Sq::GetSize(IntPtr v, SQInteger idx) {
		return sq_getsize(ToVM(v), idx);
	}

	SQHash Sq::GetHash(IntPtr v, SQInteger idx) {
		return sq_gethash(ToVM(v), idx);
	}

	SQRESULT Sq::GetBase(IntPtr v, SQInteger idx) {
		return sq_getbase(ToVM(v), idx);
	}

	SQBool Sq::InstanceOf(IntPtr v) {
		return sq_instanceof(ToVM(v));
	}

	SQRESULT Sq::ToString(IntPtr v, SQInteger idx) {
		return sq_tostring(ToVM(v), idx);
	}

	bool Sq::ToBool(IntPtr v, SQInteger idx) {
		SQUnsignedInteger b = 0;
		sq_tobool(ToVM(v), idx, &b);
		return b;
	}

	SQRESULT Sq::GetString(IntPtr v, SQInteger idx, OUT(String^) Str) {
		const SQChar* strng;
		auto R = sq_getstring(ToVM(v), idx, &strng);
		Str = gcnew String(strng);
		return R;
	}

	SQRESULT Sq::GetInt(IntPtr v, SQInteger idx, OUT(SQInteger) I) {
		SQInteger _I = 0;
		auto R = sq_getinteger(ToVM(v), idx, &_I);
		I = _I;
		return R;
	}

	SQRESULT Sq::GetFloat(IntPtr v, SQInteger idx, OUT(SQFloat) F) {
		SQFloat f = 0;
		auto R = sq_getfloat(ToVM(v), idx, &f);
		F = f;
		return R;
	}

	SQRESULT Sq::GetBool(IntPtr v, SQInteger idx, OUT(SQBool) B) {
		SQUnsignedInteger b = 0;
		auto R = sq_getbool(ToVM(v), idx, &b);
		B = b;
		return R;
	}

	SQRESULT Sq::GetThread(IntPtr v, SQInteger idx, OUT(IntPtr) T) {
		HSQUIRRELVM Thr = 0;
		auto R = sq_getthread(ToVM(v), idx, &Thr);
		T = IntPtr(Thr);
		return R;
	}

	SQRESULT Sq::GetUserPointer(IntPtr v, SQInteger idx, OUT(IntPtr) U) {
		SQUserPointer P = 0;
		auto R = sq_getuserpointer(ToVM(v), idx, &P);
		U = IntPtr(P);
		return R;
	}

	SQRESULT Sq::GetUserData(IntPtr v, SQInteger idx, OUT(IntPtr) U, OUT(IntPtr) T) {
		SQUserPointer _U = 0;
		SQUserPointer _T = 0;
		auto R = sq_getuserdata(ToVM(v), idx, &_U, &_T);
		U = IntPtr(_U);
		T = IntPtr(_T);
		return R;
	}

	SQRESULT Sq::SetTypeTag(IntPtr v, SQInteger idx, IntPtr typetag) {
		return sq_settypetag(ToVM(v), idx, typetag.ToPointer());
	}

	SQRESULT Sq::GetTypeTag(IntPtr v, SQInteger idx, OUT(IntPtr) T) {
		SQUserPointer _T = 0;
		auto R = sq_gettypetag(ToVM(v), idx, &_T);
		T = IntPtr(_T);
		return R;
	}

	void Sq::SetReleaseHook(IntPtr v, SQInteger idx, Sq::ReleaseHook^ hook) {
		sq_setreleasehook(ToVM(v), idx, (SQRELEASEHOOK)ToFuncPtr(hook));
	}

	String^ Sq::GetScratchPad(IntPtr v, SQInteger minsize) {
		return gcnew String(sq_getscratchpad(ToVM(v), minsize));
	}

	SQRESULT Sq::GetFunctionInfo(IntPtr v, SQInteger level, OUT(SQFunctionInfo) Inf) {
		tagSQFunctionInfo FInf;
		auto R = sq_getfunctioninfo(ToVM(v), level, &FInf);
		Inf.FuncID = IntPtr(FInf.funcid);
		Inf.Name = gcnew String(FInf.name);
		Inf.Source = gcnew String(FInf.source);
		return R;
	}

	SQRESULT Sq::GetClosureInfo(IntPtr v, SQInteger idx, OUT(SQUnsignedInteger) Params, OUT(SQUnsignedInteger) FreeVars) {
		SQUnsignedInteger _Params = 0;
		SQUnsignedInteger _FreeVars = 0;
		auto R = sq_getclosureinfo(ToVM(v), idx, &_Params, &_FreeVars);
		Params = _Params;
		FreeVars = _FreeVars;
		return R;
	}

	SQRESULT Sq::GetClosureName(IntPtr v, SQInteger idx) {
		return sq_getclosurename(ToVM(v), idx);
	}

	/*SQRESULT Sq::GetNativeClosureName(IntPtr v, SQInteger idx, String^ name) {

	}*/

	SQRESULT Sq::SetInstanceUp(IntPtr v, SQInteger idx, IntPtr p) {
		return sq_setinstanceup(ToVM(v), idx, p.ToPointer());
	}

	SQRESULT Sq::GetInstanceUp(IntPtr v, SQInteger idx, OUT(IntPtr) UsrPtr, IntPtr typetag) {
		SQUserPointer _P = 0;
		auto R = sq_getinstanceup(ToVM(v), idx, &_P, typetag.ToPointer());
		UsrPtr = IntPtr(_P);
		return R;
	}

	SQRESULT Sq::SetClassUDSize(IntPtr v, SQInteger idx, SQInteger udsize) {
		return sq_setclassudsize(ToVM(v), idx, udsize);
	}

	SQRESULT Sq::NewClass(IntPtr v, SQBool hasbase) {
		return sq_newclass(ToVM(v), hasbase);
	}

	SQRESULT Sq::CreateInstance(IntPtr v, SQInteger idx) {
		return sq_createinstance(ToVM(v), idx);
	}

	SQRESULT Sq::SetAttributes(IntPtr v, SQInteger idx) {
		return sq_setattributes(ToVM(v), idx);
	}

	SQRESULT Sq::GetAttributes(IntPtr v, SQInteger idx) {
		return sq_getattributes(ToVM(v), idx);
	}

	SQRESULT Sq::GetClass(IntPtr v, SQInteger idx) {
		return sq_getclass(ToVM(v), idx);
	}

	void Sq::WeakRef(IntPtr v, SQInteger idx) {
		sq_weakref(ToVM(v), idx);
	}

	SQRESULT Sq::GetDefaultDelegate(IntPtr v, SQObjectType t) {
		return sq_getdefaultdelegate(ToVM(v), (tagSQObjectType)t);
	}

	SQRESULT Sq::GetMemberHandle(IntPtr v, SQInteger idx, OUT(SQMemberHandle) H) {
		tagSQMemberHandle _H;
		auto R = sq_getmemberhandle(ToVM(v), idx, &_H);
		H.Index = _H._index;
		H.Static = _H._static;
		return R;
	}

	SQRESULT Sq::GetByHandle(IntPtr v, SQInteger idx, SQMemberHandle handle) {
		tagSQMemberHandle H;
		H._index = handle.Index;
		H._static = handle.Static;
		return sq_getbyhandle(ToVM(v), idx, &H);
	}

	SQRESULT Sq::SetByHandle(IntPtr v, SQInteger idx, SQMemberHandle handle) {
		tagSQMemberHandle H;
		H._index = handle.Index;
		H._static = handle.Static;
		return sq_setbyhandle(ToVM(v), idx, &H);
	}
}