using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

using HSQUIRRELVM = System.IntPtr;
using SQInteger = System.Int32;
using SQBool = System.Boolean;
using SQRESULT = System.Int32;

namespace SquirrelNET {
#pragma warning disable CA2101 // Specify marshaling for P/Invoke string arguments

	public unsafe struct SQStackInfos {
		public byte* funcname;
		public byte* source;
		public SQInteger line;
	}

	public unsafe static class Sq {
		const string DllName = "squirrel31";
		const CallingConvention CConv = CallingConvention.Cdecl;
		const CharSet CSet = CharSet.Ansi;

		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		public delegate int Function(HSQUIRRELVM VM);

		[UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CSet)]
		public delegate void PrintFunc(HSQUIRRELVM VM, string Str);

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_pushstring")]
		public static extern void PushString(HSQUIRRELVM VM, string Str, int Length);

		public static void PushString(HSQUIRRELVM VM, string Str) {
			PushString(VM, Str, Str.Length);
		}

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_newclosure")]
		static extern void _NewClosure(HSQUIRRELVM VM, Function Func, int FreeVars);

		public static void NewClosure(HSQUIRRELVM VM, Function Func, int FreeVars) {
			GCHandle.Alloc(Func, GCHandleType.Normal);
			_NewClosure(VM, Func, FreeVars);
		}

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_setnativeclosurename")]
		public static extern SQRESULT SetNativeClosureName(HSQUIRRELVM v, SQInteger idx, string name);

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_newslot")]
		public static extern SQRESULT NewSlot(HSQUIRRELVM v, SQInteger idx, SQBool bstatic);

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_open")]
		public static extern HSQUIRRELVM Open(SQInteger initialstacksize);

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_pushroottable")]
		public static extern void PushRootTable(HSQUIRRELVM v);

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_getstring")]
		public static extern SQRESULT _GetString(HSQUIRRELVM v, SQInteger idx, byte** c);

		public static SQRESULT GetString(HSQUIRRELVM v, SQInteger idx, out string Str) {
			byte* StrPtr = null;
			SQRESULT ret = _GetString(v, idx, &StrPtr);
			Str = new string((sbyte*)StrPtr);
			return ret;
		}

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_get")]
		public static extern SQRESULT Get(HSQUIRRELVM v, SQInteger idx);

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_remove")]
		public static extern void Remove(HSQUIRRELVM v, SQInteger idx);

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_call")]
		public static extern SQRESULT Call(HSQUIRRELVM v, SQInteger parms, SQBool retval, SQBool raiseerror);

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_getversion")]
		public static extern SQInteger GetVersion();

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_setprintfunc")]
		public static extern void SetPrintFunc(HSQUIRRELVM v, PrintFunc printfunc, PrintFunc errfunc);

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_pushinteger")]
		public static extern void PushInteger(HSQUIRRELVM v, SQInteger n);

		[DllImport(DllName, CallingConvention = CConv, CharSet = CSet, EntryPoint = "sq_compilebuffer")]
		public static extern SQRESULT CompileBuffer(HSQUIRRELVM v, string s, SQInteger size, string sourcename, SQBool raiseerror);

		public static SQRESULT CompileBuffer(HSQUIRRELVM v, string s, string sourcename, SQBool raiseerror) {
			return CompileBuffer(v, s, s.Length, sourcename, raiseerror);
		}
	}

	public static class SqStd {
		public static void RegisterBlobLib(HSQUIRRELVM v) {
		}

		public static void RegisterIOLib(HSQUIRRELVM v) {
		}

		public static void RegisterSystemLib(HSQUIRRELVM v) {
		}

		public static void RegisterMathLib(HSQUIRRELVM v) {
		}

		public static void RegisterStringLib(HSQUIRRELVM v) {
		}

		public static void SetErrorHandlers(HSQUIRRELVM v) {
		}
	}

#pragma warning restore CA2101 // Specify marshaling for P/Invoke string arguments
}
