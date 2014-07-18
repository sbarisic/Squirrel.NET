Squirrel.NET
============

Managed Squirrel programming language

For contributors
----------------

* Use ToDelegate and ToFuncPtr macros in stdafx.h to convert between delegates and function pointers
* Use squirrel types for example SQInteger instead of int and SQUnsignedInteger for uint for x86-x64 compatibility
* Add managed namespaces to the usings define in stdafx.h, keeps the source cleaner
* Use UniString^ macro instead of String^ type in delegate definitions because of String^ marshalling issues
* Use Cdecl calling convention for delegates
* Return using OUT(Type) macro instead of returning pairs (tuples) or ignoring SQRESULT
* Do not throw uncaught exceptions (See below)
* Stay true to the original C API

Contact me if you need help