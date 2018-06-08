#pragma once
#include "StaticObj.h"
#include "MeshMgr.h"
#include "DirectX.h"
#include "ShaderMgr.h"
class C_Road:public C_StaticObj
{
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
	virtual void SetConstandTable();
public:
	C_Road();
	virtual ~C_Road();
};

