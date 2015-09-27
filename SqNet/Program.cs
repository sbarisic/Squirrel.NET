using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using SquirrelNET;

namespace SqNet {
	class Program {
		const string Prmpt = ">";

		static void RegisterFunction(IntPtr S, string Name, Sq.Function Func) {
			Sq.PushString(S, Name);
			Sq.NewClosure(S, Func, 0);
			Sq.SetNativeClosureName(S, -1, Name);
			Sq.NewSlot(S, -3, false);
		}

		static void Main(string[] args) {
			Console.Title = "SqNet";

			IntPtr S = Sq.Open(1024);
			Sq.SetPrintFunc(S, (SS, Str) => {
				Console.WriteLine(Str);
			}, (SS, Str) => {
				Console.ForegroundColor = ConsoleColor.Red;
				Console.WriteLine(Str);
				Console.ResetColor();
			});

			Sq.PushRootTable(S);
			SqStd.RegisterBlobLib(S);
			SqStd.RegisterIOLib(S);
			SqStd.RegisterSystemLib(S);
			SqStd.RegisterMathLib(S);
			SqStd.RegisterStringLib(S);
			SqStd.SetErrorHandlers(S);

			RegisterFunction(S, "ManagedInt", (SS) => {
				Sq.PushInteger(SS, 42);
				return 1;
			});

			RegisterFunction(S, "ManagedStr", (SS) => {
				Sq.PushString(S, "Hello World!");
				return 1;
			});

			RegisterFunction(S, "PushSelf", (SS) => {
				Console.WriteLine("Pushed self!");
				Sq.PushRootTable(SS);
				Sq.PushString(SS, "PushSelf");
				Sq.Get(SS, -2);
				Sq.Remove(SS, -2);
				return 1;
			});

			RegisterFunction(S, "WriteStrings", (SS) => {
				string Str1, Str2;
				Sq.GetString(SS, -2, out Str1);
				Sq.GetString(SS, -1, out Str2);
				Console.WriteLine("A: {0}\nB: {1}", Str1, Str2);
				return 0;
			});

			Console.WriteLine("Running .NET version of Squirrel {0}\n", String.Join(".", Sq.GetVersion().ToString().ToCharArray()));

			while (true) {
				Console.Write(Prmpt);
				if (Sq.CompileBuffer(S, Console.ReadLine(), "Console", true) >= 0) {
					Sq.PushRootTable(S);
					Sq.Call(S, 1, false, true);
				}
			}
		}
	}
}