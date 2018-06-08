#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "SystemConst.h"
#include "SystemMcr.h"

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

#ifdef SYSTEM_EXPORT
#define SYSTEM_DLL _declspec(dllexport)
#else
#define SYSTEM_DLL _declspec(dllimport)
#endif // SYSTEM_EXPORT
