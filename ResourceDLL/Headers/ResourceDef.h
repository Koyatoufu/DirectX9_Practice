#pragma once

#pragma warning(disable:4273)//전처리기 일치,불일치
#pragma warning(disable:4251)//std:: import,export

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <vector>

#include "ResourceMcr.h"
#include "ResourceConst.h"
#include "ResourceStruct.h"



#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif


#ifdef RESOURCE_EXPORT
#define RESOURCE_DLL __declspec(dllexport)
#else
#define RESOURCE_DLL __declspec(dllimport)
#endif