#pragma once
#include "DynamicMesh.h"

class C_SkinedMesh:public C_DynamicMesh
{
public:
	HRESULT InitMesh(LPDIRECT3DDEVICE9 pDevice
		, const TCHAR* pPathName, const TCHAR* pFileName);

	virtual void InvalidateMesh(D3DXMATRIX* pMatWorld);

	void UpdateMatrix(BONE* pBone, D3DXMATRIX* pParentMatrix);
	void SetUpBoneMatrixPointer(BONE* pBone);
	virtual void Render(LPDIRECT3DDEVICE9 pDevice, const BONE* pBone = NULL);
	virtual void Release(void);

public:
	void GetAnimationSet(char* pAniSetName);
public:
	C_SkinedMesh(void);
	virtual ~C_SkinedMesh(void);
};

