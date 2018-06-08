#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
#include "TexCube.h"
#include "TexGeneral.h"
EXTERN class RESOURCE_DLL C_TextureMgr
{
	DECLARE_SINGLETONE_RESDLL(C_TextureMgr);
private:
	std::map<const TCHAR*, C_Texture*> m_MapTexture;
public:
	HRESULT InsertTexture(LPDIRECT3DDEVICE9 pDevice,TEXTYPE Type, const TCHAR* pTextureName, const TCHAR* pStateKey,const int& nCnt = 1);

	const TEXINFO* GetTexInfo(const TCHAR* pStateKey,const int& nIndex=0);

	void Release();
private:
	C_TextureMgr();
	C_TextureMgr(const C_TextureMgr&);
public:
	~C_TextureMgr();
};

