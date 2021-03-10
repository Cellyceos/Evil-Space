// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#pragma comment(lib, "gdiplus.lib")

// Windows Header Files:
#include <windows.h>
#include <GdiPlus.h>

#define _USE_MATH_DEFINES
#define  WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// C++ RunTime Header Files
#include <iostream>
#include <typeinfo>
#include <string>
#include <cmath>

// TODO: reference additional headers your program requires here
#include "Keys.h"
#include "Random.h"
#include "ArrayList.h"
#include "targetver.h"