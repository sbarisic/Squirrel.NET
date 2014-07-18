#pragma once
usings

#define SQBool bool

namespace SquirrelNET {
	public enum class SQObjectType {
		OT_NULL =			(_RT_NULL | SQOBJECT_CANBEFALSE),
		OT_INTEGER =		(_RT_INTEGER | SQOBJECT_NUMERIC | SQOBJECT_CANBEFALSE),
		OT_FLOAT =			(_RT_FLOAT | SQOBJECT_NUMERIC | SQOBJECT_CANBEFALSE),
		OT_BOOL =			(_RT_BOOL | SQOBJECT_CANBEFALSE),
		OT_STRING =			(_RT_STRING | SQOBJECT_REF_COUNTED),
		OT_TABLE =			(_RT_TABLE | SQOBJECT_REF_COUNTED | SQOBJECT_DELEGABLE),
		OT_ARRAY =			(_RT_ARRAY | SQOBJECT_REF_COUNTED),
		OT_USERDATA =		(_RT_USERDATA | SQOBJECT_REF_COUNTED | SQOBJECT_DELEGABLE),
		OT_CLOSURE =		(_RT_CLOSURE | SQOBJECT_REF_COUNTED),
		OT_NATIVECLOSURE =	(_RT_NATIVECLOSURE | SQOBJECT_REF_COUNTED),
		OT_GENERATOR =		(_RT_GENERATOR | SQOBJECT_REF_COUNTED),
		OT_USERPOINTER =	(_RT_USERPOINTER),
		OT_THREAD =			(_RT_THREAD | SQOBJECT_REF_COUNTED) ,
		OT_FUNCPROTO =		(_RT_FUNCPROTO | SQOBJECT_REF_COUNTED), //internal usage only
		OT_CLASS =			(_RT_CLASS | SQOBJECT_REF_COUNTED),
		OT_INSTANCE =		(_RT_INSTANCE | SQOBJECT_REF_COUNTED | SQOBJECT_DELEGABLE),
		OT_WEAKREF =		(_RT_WEAKREF | SQOBJECT_REF_COUNTED),
		OT_OUTER =			(_RT_OUTER | SQOBJECT_REF_COUNTED) //internal usage only
	};

	public value class SQFunctionInfo {
		IntPtr FuncID;
		String^ Name;
		String^ Source;
	};

	public ref class Sq {
	public:
		// TODO: Implement function pointers as delegates. Use UniString^ instead of String^
		// Use ToDelegate and ToFuncPtr macros to marshal between unanaged and managed
		CConv(Cdecl) delegate void PrintFunc(IntPtr S, UniString^ StrPtr);

		// TODO: Implement in VM.cpp
		static IntPtr Open(SQInteger initialstacksize);
		static IntPtr NewThread(IntPtr friendvm, SQInteger initialstacksize) { return IntPtr(0); } // TO IPLEMENT
		static void SetErrorHandler(IntPtr v) { return; } // TO IMPLEMENT
		static void Close(IntPtr v);
		static void SetForeignPtr(IntPtr v, IntPtr p) { return; } // TO IMPLEMENT
		static IntPtr GetForeignPtr(IntPtr v) { return IntPtr(0); } // TO IMPLEMENT
		static void SetPrintFunc(IntPtr v, PrintFunc^ printfunc, PrintFunc^ errfunc);
		static PrintFunc^ GetPrintFunc(IntPtr v);
		static PrintFunc^ GetErrorFunc(IntPtr v);
		static SQRESULT SuspendVM(IntPtr v) { return NULL; } // TO IMPLEMENT
		static SQRESULT WakeupVM(IntPtr v, bool resumedret, bool retval, bool raiseerror, bool throwerror) { return NULL; } // TO IMPLEMENT
		static SQInteger GetVMState(IntPtr v) { return NULL; } // TO IMPLEMENT
		static SQInteger GetVersion() { return NULL; } // TO IMPLEMENT

		// TODO: Implement in Compiler.cpp
		static SQRESULT Compile(IntPtr v, SQLEXREADFUNC read, IntPtr p, String^ sourcename, bool raiseerror) { return NULL; } // TO IMPLEMENT // TODO
		static SQRESULT CompileBuffer(IntPtr v, String^ Src, String^ SrcName, bool raiseerror);
		static void EnableDebugInfo(IntPtr v, bool enable) { return; } // TO IMPLEMENT
		static void NotifyAllExceptions(IntPtr v, bool enable) { return; } // TO IMPLEMENT
		static void SetCompilerErrorHandler(IntPtr v, SQCOMPILERERROR f) { return; } // TO IMPLEMENT // TODO

		// TODO: Implement in Stack.cpp
		static void Push(IntPtr v, SQInteger idx) { return; } // TO IMPLEMENT
		static void Pop(IntPtr v, SQInteger nelemstopop);
		static void PopTop(IntPtr v) { return; } // TO IMPLEMENT
		static void Remove(IntPtr v, SQInteger idx) { return; } // TO IMPLEMENT
		static SQInteger GetTop(IntPtr v) { return NULL; } // TO IMPLEMENT
		static void SetTop(IntPtr v, SQInteger newtop) { return; } // TO IMPLEMENT
		static SQRESULT ReserveStack(IntPtr v, SQInteger nsize) { return NULL; } // TO IMPLEMENT
		static SQInteger Cmp(IntPtr v) { return NULL; } // TO IMPLEMENT
		static void Move(IntPtr dest, IntPtr src, SQInteger idx) { return; } // TO IMPLEMENT

		// TODO: Implement in ObjectCreation.cpp
		static IntPtr NewUserdata(IntPtr v, SQUnsignedInteger size) { return IntPtr(0); } // TO IMPLEMENT
		static void NewTable(IntPtr v) { return; } // TO IMPLEMENT
		static void NewTableEx(IntPtr v, SQInteger initialcapacity) { return; } // TO IMPLEMENT
		static void NewArray(IntPtr v, SQInteger size) { return; } // TO IMPLEMENT
		static void NewClosure(IntPtr v, SQFUNCTION func, SQUnsignedInteger nfreevars) { return; } // TO IMPLEMENT
		static SQRESULT SetParasCheck(IntPtr v, SQInteger nparamscheck, String^ typemask) { return NULL; } // TO IMPLEMENT
		static SQRESULT BindEnv(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static void PushString(IntPtr v, String^ s) { return; } // TO IMPLEMENT
		static void PushFloat(IntPtr v, SQFloat f) { return; } // TO IMPLEMENT
		static void PushInteger(IntPtr v, SQInteger n) { return; } // TO IMPLEMENT
		static void PushBool(IntPtr v, SQBool b) { return; } // TO IMPLEMENT
		static void PushUserPointer(IntPtr v, IntPtr p) { return; } // TO IMPLEMENT
		static void PushNull(IntPtr v) { return; } // TO IMPLEMENT
		static SQObjectType GetType(IntPtr v, SQInteger idx) { return SQObjectType::OT_NULL; } // TO IMPLEMENT
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

		// TODO: Implement in ObjectManipulation.cpp
		static void PushRootTable(IntPtr v);
		static void PushRegistryTable(IntPtr v) { return; } // TO IMPLEMENT
		static void PushConstantTable(IntPtr v) { return ; } // TO IMPLEMENT
		static SQRESULT SetRootTable(IntPtr v) { return NULL; } // TO IMPLEMENT
		static SQRESULT SetConstantTable(IntPtr v) { return NULL; } // TO IMPLEMENT
		static SQRESULT NewSlot(IntPtr v, SQInteger idx, SQBool bstatic) { return NULL; } // TO IMPLEMENT
		static SQRESULT DeleteSlot(IntPtr v, SQInteger idx, SQBool pushval) { return NULL; } // TO IMPLEMENT
		static SQRESULT Set(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT Get(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT RawGet(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT RawSet(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT RawDeleteSlot(IntPtr v, SQInteger idx, SQBool pushval) { return NULL; } // TO IMPLEMENT
		static SQRESULT NewMember(IntPtr v, SQInteger idx, SQBool bstatic) { return NULL; } // TO IMPLEMENT
		static SQRESULT RawNewMember(IntPtr v, SQInteger idx, SQBool bstatic) { return NULL; } // TO IMPLEMENT
		static SQRESULT ArrayAppend(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT ArrayPop(IntPtr v, SQInteger idx, SQBool pushval) { return NULL; } // TO IMPLEMENT 
		static SQRESULT ArrayResize(IntPtr v, SQInteger idx, SQInteger newsize) { return NULL; } // TO IMPLEMENT 
		static SQRESULT ArrayReverse(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT 
		static SQRESULT ArrayRemove(IntPtr v, SQInteger idx, SQInteger itemidx) { return NULL; } // TO IMPLEMENT
		static SQRESULT ArrayInsert(IntPtr v, SQInteger idx, SQInteger destpos) { return NULL; } // TO IMPLEMENT
		static SQRESULT SetDelegate(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT GetDelegate(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT Clone(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT SetFreeVariable(IntPtr v, SQInteger idx, SQUnsignedInteger nval) { return NULL; } // TO IMPLEMENT
		static SQRESULT Next(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT GetWeakRefVal(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT
		static SQRESULT Clear(IntPtr v, SQInteger idx) { return NULL; } // TO IMPLEMENT

		// TODO: Implement in Calls.cpp
		static SQRESULT Call(IntPtr v, SQInteger params, SQBool retval, SQBool raiseerror);
		static SQRESULT Resume(IntPtr v, SQBool retval, SQBool raiseerror) { return NULL; } // TO IMPLEMENT
		static String^ GetLocal(IntPtr v, SQUnsignedInteger level, SQUnsignedInteger idx) { return ""; } // TO IMPLEMENT
		static SQRESULT GetCallee(IntPtr v) { return NULL; } // TO IMPLEMENT
		static String^ GetFreeVariable(IntPtr v, SQInteger idx, SQUnsignedInteger nval) { return ""; } // TO IMPLEMENT
		static SQRESULT ThrowError(IntPtr v, String^ err) { return NULL; } // TO IMPLEMENT
		static SQRESULT ThrowObject(IntPtr v) { return NULL; } // TO IMPLEMENT
		static void ResetError(IntPtr v) { return; } // TO IMPLEMENT
		static void GetLastError(IntPtr v) { return; } // TO IMPLEMENT

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
		static SQRESULT sq_writeclosure(IntPtr vm, SQWRITEFUNC writef, IntPtr up) { return NULL; } // TO IMPLEMENT // TODO
		static SQRESULT sq_readclosure(IntPtr vm, SQREADFUNC readf, IntPtr up) { return NULL; } // TO IMPLEMENT // TODO
		static IntPtr Malloc(SQUnsignedInteger size) { return IntPtr(0); } // TO IMPLEMENT
		static IntPtr Realloc(IntPtr p, SQUnsignedInteger oldsize, SQUnsignedInteger newsize) { return IntPtr(0); } // TO IMPLEMENT
		static void Free(IntPtr p, SQUnsignedInteger size) { return; } // TO IMPLEMENT
		static SQRESULT StackInfos(IntPtr v, SQInteger level, IntPtr si) { return NULL; } // TO IMPLEMENT
		static void SetDebugHook(IntPtr v) { return; } // TO IMPLEMENT
		static void SetNativeDebugHook(IntPtr v, SQDEBUGHOOK hook) { return; } // TO IMPLEMENT // TODO

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
