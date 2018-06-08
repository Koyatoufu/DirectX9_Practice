#pragma once

#include "Mesh.h"

class C_StaticMesh:public C_Mesh
{
virtual HRESULT InitMesh(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pPath, const TCHAR* pFileName);
virtual void Render(LPDIRECT3DDEVICE9 pDevice
	, const BONE* pRootBone = NULL);
virtual void Release();
public:
	C_StaticMesh();
	virtual ~C_StaticMesh();
};

