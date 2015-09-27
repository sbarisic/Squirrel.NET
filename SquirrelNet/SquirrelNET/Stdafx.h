// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <stdarg.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <vcclr.h>

#pragma warning(disable:4483)

// Use these for delegate<->function pointer
#define ToDelegate(F, Del) (Del^)Marshal::GetDelegateForFunctionPointer(IntPtr(F), Del::typeid)
#define ToFuncPtr(Del) Marshal::GetFunctionPointerForDelegate(Del).ToPointer()

#define CConv(C) [UnmanagedFunctionPointer(CallingConvention::C)]
#define MarshalAs(T) [MarshalAs(UnmanagedType::T)]
#define UniString MarshalAs(LPWStr) String
#define OUT(Typ) [Out] Typ%
#define ToVM(S) ((HSQUIRRELVM)S.ToPointer())
#define GetSQCharPtr(Str, Name) pin_ptr<const SQChar> Name = PtrToStringChars(Str)

#define usings\
	using namespace System; \
	using namespace System::Collections::Generic; \
	using namespace System::Runtime::InteropServices; \
	using namespace System::Runtime;