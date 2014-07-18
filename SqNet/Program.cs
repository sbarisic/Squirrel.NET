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

		static void Main(string[] args) {
			Console.Title = "SqNet";
			Console.WriteLine("Loading");


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