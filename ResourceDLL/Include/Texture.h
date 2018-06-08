#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
EXTERN class RESOURCE_DLL C_Texture
{
protected:
	std::map<const TCHAR*, std::vector<TEXINFO*>> m_MapTexture;
public:
	virtual HRESULT InitTexture(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pTextureName, const TCHAR* pStateKey, const int& nCnt = 1)=0;
	virtual void Relaese();

	const TEXINFO* GetTexInfo(const TCHAR* pStateKey, const int& nIndex = 0);

public:
	C_Texture();
	virtual ~C_Texture();
};

