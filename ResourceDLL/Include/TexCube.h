#pragma once
#include "Texture.h"
class C_TexCube:public C_Texture
{
public:
	virtual HRESULT InitTexture(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pTextureName, const TCHAR* pStateKey, const int& nCnt = 1);
	virtual void Relaese();
public:
	C_TexCube();
	virtual ~C_TexCube();
};

