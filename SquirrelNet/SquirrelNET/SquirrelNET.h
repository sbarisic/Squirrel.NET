#pragma once
usings;

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

	public value class SQMemberHandle {
	public:
		SQBool Static;
		SQInteger Index;
	};

	public value class SQFunctionInfo {
	public:
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

		static IntPtr NewUserdata(IntPtr v, SQUnsignedInteger size);
		static void NewTable(IntPtr v);
		static void NewTableEx(IntPtr v, SQInteger initialcapacity);
		static void NewArray(IntPtr v, SQInteger size);
		static void NewClosure(IntPtr v, Function^ func, SQUnsignedInteger nfreevars);
		static SQRESULT SetParamsCheck(IntPtr v, SQInteger nparamscheck, String^ typemask);
		static SQRESULT BindEnv(IntPtr v, SQInteger idx);
		static void PushString(IntPtr v, String^ s);
		static void PushFloat(IntPtr v, SQFloat f);
		static void PushInteger(IntPtr v, SQInteger n);
		static void PushBool(IntPtr v, SQBool b);
		static void PushUserPointer(IntPtr v, IntPtr p);
		static void PushNull(IntPtr v);
		static SQObjectType GetType(IntPtr v, SQInteger idx);
		static SQRESULT TypeOf(IntPtr v, SQInteger idx);
		static SQInteger GetSize(IntPtr v, SQInteger idx);
		static SQHash GetHash(IntPtr v, SQInteger idx);
		static SQRESULT GetBase(IntPtr v, SQInteger idx);
		static SQBool InstanceOf(IntPtr v);
		static SQRESULT ToString(IntPtr v, SQInteger idx);
		static bool ToBool(IntPtr v, SQInteger idx);
		static SQRESULT GetString(IntPtr v, SQInteger idx, OUT(String^) Str);
		static SQRESULT GetInt(IntPtr v, SQInteger idx, OUT(SQInteger) I);
		static SQRESULT GetFloat(IntPtr v, SQInteger idx, OUT(SQFloat) F);
		static SQRESULT GetBool(IntPtr v, SQInteger idx, OUT(SQBool) B);
		static SQRESULT GetThread(IntPtr v, SQInteger idx, OUT(IntPtr) T);
		static SQRESULT GetUserPointer(IntPtr v, SQInteger idx, OUT(IntPtr) U);
		static SQRESULT GetUserData(IntPtr v, SQInteger idx, OUT(IntPtr) U, OUT(IntPtr) T);
		static SQRESULT SetTypeTag(IntPtr v, SQInteger idx, IntPtr typetag);
		static SQRESULT GetTypeTag(IntPtr v, SQInteger idx, OUT(IntPtr) T);
		static void SetReleaseHook(IntPtr v, SQInteger idx, ReleaseHook^ hook);
		static String^ GetScratchPad(IntPtr v, SQInteger minsize);
		static SQRESULT GetFunctionInfo(IntPtr v, SQInteger level, OUT(SQFunctionInfo) Inf);
		static SQRESULT GetClosureInfo(IntPtr v, SQInteger idx, OUT(SQUnsignedInteger) Params, OUT(SQUnsignedInteger) FreeVars);
		static SQRESULT GetClosureName(IntPtr v, SQInteger idx);
		static SQRESULT SetNativeClosureName(IntPtr v, SQInteger idx, String^ name);
		//static SQRESULT GetNativeClosureName(IntPtr v, SQInteger idx, String^ name); // Doesn't exist, the fuck?
		static SQRESULT SetInstanceUp(IntPtr v, SQInteger idx, IntPtr p);
		static SQRESULT GetInstanceUp(IntPtr v, SQInteger idx, OUT(IntPtr) UsrPtr, IntPtr typetag);
		static SQRESULT SetClassUDSize(IntPtr v, SQInteger idx, SQInteger udsize);
		static SQRESULT NewClass(IntPtr v, SQBool hasbase);
		static SQRESULT CreateInstance(IntPtr v, SQInteger idx);
		static SQRESULT SetAttributes(IntPtr v, SQInteger idx);
		static SQRESULT GetAttributes(IntPtr v, SQInteger idx);
		static SQRESULT GetClass(IntPtr v, SQInteger idx);
		static void WeakRef(IntPtr v, SQInteger idx);
		static SQRESULT GetDefaultDelegate(IntPtr v, SQObjectType t);
		static SQRESULT GetMemberHandle(IntPtr v, SQInteger idx, OUT(SQMemberHandle) H);
		static SQRESULT GetByHandle(IntPtr v, SQInteger idx, SQMemberHandle handle);
		static SQRESULT SetByHandle(IntPtr v, SQInteger idx, SQMemberHandle handle);

		static IntPtr AllocSQObject();
		static void FreeSQObject(IntPtr o);
		static SQRESULT GetStackObj(IntPtr v, SQInteger idx, IntPtr po);
		static void PushObject(IntPtr v, IntPtr obj);
		static void AddRef(IntPtr v, IntPtr po);
		static SQBool Release(IntPtr v, IntPtr po);
		static SQUnsignedInteger GetRefCount(IntPtr v, IntPtr po);
		static void ResetObject(IntPtr po);
		static String^ ObjToString(IntPtr o);
		static SQBool ObjToBool(IntPtr o);
		static SQInteger ObjToInt(IntPtr o);
		static SQFloat ObjToFloat(IntPtr o);
		static IntPtr ObjToUserPointer(IntPtr o);
		static SQRESULT GetObjTypeTag(IntPtr o, OUT(IntPtr) TypeTag);
		static SQObjectType Type(IntPtr o);

		static SQInteger CollectGarbage(IntPtr v);
		static SQRESULT ResurrectUnreachable(IntPtr v);
		static SQRESULT WriteClosure(IntPtr vm, WriteFunc^ writef, IntPtr up);
		static SQRESULT ReadClosure(IntPtr vm, ReadFunc^ readf, IntPtr up);
		static IntPtr Malloc(SQUnsignedInteger size);
		static IntPtr Realloc(IntPtr p, SQUnsignedInteger oldsize, SQUnsignedInteger newsize);
		static void Free(IntPtr p, SQUnsignedInteger size);
		static SQRESULT StackInfos(IntPtr v, SQInteger level, IntPtr si);
		static void SetDebugHook(IntPtr v);
		static void SetNativeDebugHook(IntPtr v, DebugHook^ hook);
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
