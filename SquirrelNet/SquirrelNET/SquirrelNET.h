#pragma once
usings

#define SQBool bool

namespace SquirrelNET {
	public enum class SQObjectType {
		Null =			(_RT_NULL | SQOBJECT_CANBEFALSE),
		Integer =		(_RT_INTEGER | SQOBJECT_NUMERIC | SQOBJECT_CANBEFALSE),
		Float =			(_RT_FLOAT | SQOBJECT_NUMERIC | SQOBJECT_CANBEFALSE),
		Bool =			(_RT_BOOL | SQOBJECT_CANBEFALSE),
		String =		(_RT_STRING | SQOBJECT_REF_COUNTED),
		Table =			(_RT_TABLE | SQOBJECT_REF_COUNTED | SQOBJECT_DELEGABLE),
		Array =			(_RT_ARRAY | SQOBJECT_REF_COUNTED),
		Userdata =		(_RT_USERDATA | SQOBJECT_REF_COUNTED | SQOBJECT_DELEGABLE),
		Closure =		(_RT_CLOSURE | SQOBJECT_REF_COUNTED),
		NativeClosure =	(_RT_NATIVECLOSURE | SQOBJECT_REF_COUNTED),
		Generator =		(_RT_GENERATOR | SQOBJECT_REF_COUNTED),
		Userpointer =	(_RT_USERPOINTER),
		Thread =		(_RT_THREAD | SQOBJECT_REF_COUNTED) ,
		_FuncProto =	(_RT_FUNCPROTO | SQOBJECT_REF_COUNTED), //internal usage only
		Class =			(_RT_CLASS | SQOBJECT_REF_COUNTED),
		Instance =		(_RT_INSTANCE | SQOBJECT_REF_COUNTED | SQOBJECT_DELEGABLE),
		WeakRef =		(_RT_WEAKREF | SQOBJECT_REF_COUNTED),
		_Outer =		(_RT_OUTER | SQOBJECT_REF_COUNTED) //internal usage only
	};

	public value class SQFunctionInfo {
		IntPtr FuncID;
		String^ Name;
		String^ Source;
	};

	public ref class Sq {
	public:
		// Implement function pointers as delegates. Use UniString^ instead of String^
		// Use ToDelegate and ToFuncPtr macros to marshal between unanaged and managed
		CConv(Cdecl) delegate void PrintFunc(IntPtr S, UniString^ StrPtr);
		CConv(Cdecl) delegate SQInteger Function(IntPtr S);
		CConv(Cdecl) delegate SQInteger ReleaseHook(IntPtr U, SQInteger size);
		CConv(Cdecl) delegate void CompilerError(IntPtr S, UniString^ Desc, UniString^ Src, SQInteger Line, SQInteger Col);
		CConv(Cdecl) delegate void DebugHook(IntPtr S, SQInteger Typ, UniString^ Src, SQInteger Ln, UniString^ FuncName);
		CConv(Cdecl) delegate SQInteger WriteFunc(IntPtr U, IntPtr U2, SQInteger I);
		CConv(Cdecl) delegate SQInteger ReadFunc(IntPtr U, IntPtr U2, SQInteger I);
		CConv(Cdecl) delegate SQInteger LexReadFunc(IntPtr U);

		static IntPtr Open(SQInteger initialstacksize);
		static IntPtr NewThread(IntPtr friendvm, SQInteger initialstacksize);
		static void SetErrorHandler(IntPtr v);
		static void Close(IntPtr v);
		static void SetForeignPtr(IntPtr v, IntPtr p);
		static IntPtr GetForeignPtr(IntPtr v);
		static void SetPrintFunc(IntPtr v, PrintFunc^ printfunc, PrintFunc^ errfunc);
		static PrintFunc^ GetPrintFunc(IntPtr v);
		static PrintFunc^ GetErrorFunc(IntPtr v);
		static SQRESULT SuspendVM(IntPtr v);
		static SQRESULT WakeupVM(IntPtr v, bool resumedret, bool retval, bool raiseerror, bool throwerror);
		static SQInteger GetVMState(IntPtr v);
		static SQInteger GetVersion();

		static SQRESULT Compile(IntPtr v, LexReadFunc^ read, IntPtr p, String^ sourcename, bool raiseerror);
		static SQRESULT CompileBuffer(IntPtr v, String^ Src, String^ SrcName, bool raiseerror);
		static void EnableDebugInfo(IntPtr v, bool enable);
		static void NotifyAllExceptions(IntPtr v, bool enable);
		static void SetCompilerErrorHandler(IntPtr v, CompilerError^ f);

		static void Push(IntPtr v, SQInteger idx);
		static void Pop(IntPtr v, SQInteger nelemstopop);
		static void PopTop(IntPtr v);
		static void Remove(IntPtr v, SQInteger idx);
		static SQInteger GetTop(IntPtr v);
		static void SetTop(IntPtr v, SQInteger newtop);
		static SQRESULT ReserveStack(IntPtr v, SQInteger nsize);
		static SQInteger Cmp(IntPtr v);
		static void Move(IntPtr dest, IntPtr src, SQInteger idx);

		static SQRESULT Call(IntPtr v, SQInteger params, SQBool retval, SQBool raiseerror);
		static SQRESULT Resume(IntPtr v, SQBool retval, SQBool raiseerror);
		static String^ GetLocal(IntPtr v, SQUnsignedInteger level, SQUnsignedInteger idx);
		static SQRESULT GetCallee(IntPtr v);
		static String^ GetFreeVariable(IntPtr v, SQInteger idx, SQUnsignedInteger nval);
		static SQRESULT ThrowError(IntPtr v, String^ err);
		static SQRESULT ThrowObject(IntPtr v);
		static void ResetError(IntPtr v);
		static void GetLastError(IntPtr v);

		static void PushRootTable(IntPtr v);
		static void PushRegistryTable(IntPtr v);
		static void PushConstantTable(IntPtr v);
		static SQRESULT SetRootTable(IntPtr v);
		static SQRESULT SetConstantTable(IntPtr v);
		static SQRESULT NewSlot(IntPtr v, SQInteger idx, SQBool bstatic);
		static SQRESULT DeleteSlot(IntPtr v, SQInteger idx, SQBool pushval);
		static SQRESULT Set(IntPtr v, SQInteger idx);
		static SQRESULT Get(IntPtr v, SQInteger idx);
		static SQRESULT RawGet(IntPtr v, SQInteger idx);
		static SQRESULT RawSet(IntPtr v, SQInteger idx);
		static SQRESULT RawDeleteSlot(IntPtr v, SQInteger idx, SQBool pushval);
		static SQRESULT NewMember(IntPtr v, SQInteger idx, SQBool bstatic);
		static SQRESULT RawNewMember(IntPtr v, SQInteger idx, SQBool bstatic);
		static SQRESULT ArrayAppend(IntPtr v, SQInteger idx);
		static SQRESULT ArrayPop(IntPtr v, SQInteger idx, SQBool pushval);
		static SQRESULT ArrayResize(IntPtr v, SQInteger idx, SQInteger newsize);
		static SQRESULT ArrayReverse(IntPtr v, SQInteger idx);
		static SQRESULT ArrayRemove(IntPtr v, SQInteger idx, SQInteger itemidx);
		static SQRESULT ArrayInsert(IntPtr v, SQInteger idx, SQInteger destpos);
		static SQRESULT SetDelegate(IntPtr v, SQInteger idx);
		static SQRESULT GetDelegate(IntPtr v, SQInteger idx);
		static SQRESULT Clone(IntPtr v, SQInteger idx);
		static SQRESULT SetFreeVariable(IntPtr v, SQInteger idx, SQUnsignedInteger nval);
		static SQRESULT Next(IntPtr v, SQInteger idx);
		static SQRESULT GetWeakRefVal(IntPtr v, SQInteger idx);
		static SQRESULT Clear(IntPtr v, SQInteger idx);

		// TODO: Implement in ObjectCreation.cpp
		static IntPtr NewUserdata(IntPtr v, SQUnsignedInteger size) { return IntPtr(0); } // TO IMPLEMENT
		static void NewTable(IntPtr v) { return; } // TO IMPLEMENT
		static void NewTableEx(IntPtr v, SQInteger initialcapacity) { return; } // TO IMPLEMENT
		static void NewArray(IntPtr v, SQInteger size) { return; } // TO IMPLEMENT
		static void NewClosure(IntPtr v, Function^ func, SQUnsignedInteger nfreevars) { return; } // TO IMPLEMENT
		static SQRESULT SetParasCheck(IntPtr v, SQInteger nparamscheck, String^ typemask) { return NULL; } // TO IMPLEMENT
		static SQRESULT BindEnv(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static void PushString(IntPtr v, String^ s) { return; } // TO IMPLEMENT
		static void PushFloat(IntPtr v, SQFloat f) { return; } // TO IMPLEMENT
		static void PushInteger(IntPtr v, SQInteger n) { return; } // TO IMPLEMENT
		static void PushBool(IntPtr v, SQBool b) { return; } // TO IMPLEMENT
		static void PushUserPointer(IntPtr v, IntPtr p) { return; } // TO IMPLEMENT
		static void PushNull(IntPtr v) { return; } // TO IMPLEMENT
		static SQObjectType GetType(IntPtr v, SQInteger idx) { return SQObjectType::Null; } // TO IMPLEMENT
		static SQRESULT TypeOf(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQInteger GetSize(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQHash GetHash(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT GetBase(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQBool InstanceOf(IntPtr v) { return NULL; } // TO IMPLEMENT
		static SQRESULT ToString(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static bool ToBool(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static String^ GetString(IntPtr v, SQInteger idx) { return ""; } // TO IMPLEMENT
		static int GetInt(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static float GetFloat(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static bool GetBool(IntPtr v, SQInteger idx, SQBool) { return NULL; } // TO IMPLEMENT
		static IntPtr GetThread(IntPtr v, SQInteger idx) { return IntPtr(0); } // TO IMPLEMENT
		static IntPtr GetUserPointer(IntPtr v, SQInteger idx) { return IntPtr(0); } // TO IMPLEMENT
		static Tuple<IntPtr, IntPtr>^ GetUserData(IntPtr v, SQInteger idx) { return gcnew Tuple<IntPtr, IntPtr>(IntPtr(0), IntPtr(0)); } // TO IMPLEMENT
		static SQRESULT SetTypeTag(IntPtr v, SQInteger idx, IntPtr typetag) { return NULL; } // TO IMPLEMENT
		static IntPtr GetTypeTag(IntPtr v, SQInteger idx) { return IntPtr(0); } // TO IMPLEMENT
		static void SetReleaseHook(IntPtr v, SQInteger idx, SQRELEASEHOOK hook) { return; } // TO IMPLEMENT // TODO
		static String^ GetScratchPad(IntPtr v, SQInteger minsize) { return ""; } // TO IMPLEMENT
		static SQFunctionInfo GetFunctionInfo(IntPtr v, SQInteger level) { return SQFunctionInfo(); } // TO IMPLEMENT
		static Tuple<unsigned int, unsigned int>^ GetClosureInfo(IntPtr v, SQInteger idx) { return gcnew Tuple<unsigned int, unsigned int>(0, 0); } // TO IMPLEMENT
		static SQRESULT GetClosureName(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT GetNativeClosureName(IntPtr v, SQInteger idx, String^ name) { return NULL; } // TO IMPLEMENT
		static SQRESULT SetInstanceUp(IntPtr v, SQInteger idx, IntPtr p) { return NULL; } // TO IMPLEMENT
		static IntPtr GetInstanceUp(IntPtr v, SQInteger idx, IntPtr typetag) { return IntPtr(0); } // TO IMPLEMENT
		static SQRESULT SetClassUDSize(IntPtr v, SQInteger idx, SQInteger udsize) { return NULL; } // TO IMPLEMENT
		static SQRESULT NewClass(IntPtr v, SQBool hasbase) { return NULL; } // TO IMPLEMENT
		static SQRESULT CreateInstance(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT SetAttributes(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT GetAttributes(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT GetClass(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static void WeakRef(IntPtr v, SQInteger idx) { return; } // TO IMPLEMENT
		static SQRESULT GetDefaultDelegate(IntPtr v, SQObjectType t) { return NULL; } // TO IMPLEMENT
		static IntPtr GetMemberHandle(IntPtr v, SQInteger idx) { return IntPtr(0); } // TO IMPLEMENT
		static SQRESULT GetByHandle(IntPtr v, SQInteger idx, IntPtr handle) { return NULL; } // TO IMPLEMENT
		static SQRESULT SetByHandle(IntPtr v, SQInteger idx, IntPtr handle) { return NULL; } // TO IMPLEMENT

		// TODO: Implement in ObjectHandling.cpp
		static SQRESULT GetStackObj(IntPtr v, SQInteger idx, IntPtr po) { return NULL; } // TO IMPLEMENT
		static void PushObject(IntPtr v, HSQOBJECT obj) { return; } // TO IMPLEMENT
		static void AddRef(IntPtr v, IntPtr po) { return; } // TO IMPLEMENT
		static SQBool Release(IntPtr v, IntPtr po) { return NULL; } // TO IMPLEMENT
		static SQUnsignedInteger GetRefCount(IntPtr v, IntPtr po) { return NULL; } // TO IMPLEMENT
		static void ResetObject(IntPtr po) { return; } // TO IMPLEMENT
		static String^ ObjToString(IntPtr o) { return ""; } // TO IMPLEMENT
		static SQBool ObjToBool(IntPtr o) { return NULL; } // TO IMPLEMENT
		static SQInteger ObjToInt(IntPtr o) { return NULL; } // TO IMPLEMENT
		static SQFloat ObjToFloat(IntPtr o) { return NULL; } // TO IMPLEMENT
		static IntPtr ObjToUserPointer(IntPtr o) { return IntPtr(0); } // TO IMPLEMENT
		static IntPtr GetObjTypeTag(IntPtr o) { return IntPtr(0); } // TO IMPLEMENT

		// TODO: Implement in Misc.cpp
		static SQInteger CollectGarbage(IntPtr v) { return NULL; } // TO IMPLEMENT
		static SQRESULT ResurrectUnreachable(IntPtr v) { return NULL; } // TO IMPLEMENT
		static SQRESULT sq_writeclosure(IntPtr vm, WriteFunc^ writef, IntPtr up) { return NULL; } // TO IMPLEMENT // TODO
		static SQRESULT sq_readclosure(IntPtr vm, ReadFunc^ readf, IntPtr up) { return NULL; } // TO IMPLEMENT // TODO
		static IntPtr Malloc(SQUnsignedInteger size) { return IntPtr(0); } // TO IMPLEMENT
		static IntPtr Realloc(IntPtr p, SQUnsignedInteger oldsize, SQUnsignedInteger newsize) { return IntPtr(0); } // TO IMPLEMENT
		static void Free(IntPtr p, SQUnsignedInteger size) { return; } // TO IMPLEMENT
		static SQRESULT StackInfos(IntPtr v, SQInteger level, IntPtr si) { return NULL; } // TO IMPLEMENT
		static void SetDebugHook(IntPtr v) { return; } // TO IMPLEMENT
		static void SetNativeDebugHook(IntPtr v, DebugHook^ hook) { return; } // TO IMPLEMENT // TODO

		// TODO: Port these fuckers and implement
		/* 
		sq_isnumeric(o) ((o)._type&SQOBJECT_NUMERIC)
		sq_istable(o) ((o)._type==OT_TABLE)
		sq_isarray(o) ((o)._type==OT_ARRAY)
		sq_isfunction(o) ((o)._type==OT_FUNCPROTO)
		sq_isclosure(o) ((o)._type==OT_CLOSURE)
		sq_isgenerator(o) ((o)._type==OT_GENERATOR)
		sq_isnativeclosure(o) ((o)._type==OT_NATIVECLOSURE)
		sq_isstring(o) ((o)._type==OT_STRING)
		sq_isinteger(o) ((o)._type==OT_INTEGER)
		sq_isfloat(o) ((o)._type==OT_FLOAT)
		sq_isuserpointer(o) ((o)._type==OT_USERPOINTER)
		sq_isuserdata(o) ((o)._type==OT_USERDATA)
		sq_isthread(o) ((o)._type==OT_THREAD)
		sq_isnull(o) ((o)._type==OT_NULL)
		sq_isclass(o) ((o)._type==OT_CLASS)
		sq_isinstance(o) ((o)._type==OT_INSTANCE)
		sq_isbool(o) ((o)._type==OT_BOOL)
		sq_isweakref(o) ((o)._type==OT_WEAKREF)
		sq_type(o) ((o)._type)
		//*/
	};

	public ref class SqStd {
	public:
		static void SetErrorHandlers(IntPtr S);

		static int RegisterBlobLib(IntPtr S);
		static int RegisterIOLib(IntPtr S);
		static int RegisterSystemLib(IntPtr S);
		static int RegisterMathLib(IntPtr S);
		static int RegisterStringLib(IntPtr S);
	};

	public ref class SqUtil {
	};
}
