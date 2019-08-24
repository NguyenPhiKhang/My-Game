#ifndef _DEBUG_H             // Prevent multiple definitions if this 
#define _DEBUG_H             // file is included in more than one place

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

void DebugOut(const char* fmt, ...);

#endif