#include "debug.h"
#include <windows.h>

void DebugOut(const char* fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	char dbg_out[4096];
	vsprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugString(dbg_out);
}