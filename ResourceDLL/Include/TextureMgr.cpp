#include "TextureMgr.h"

IMPLEMENT_SINGLETONE_RESDLL(C_TextureMgr);

C_TextureMgr::C_TextureMgr()
{
}


C_TextureMgr::~C_TextureMgr()
{
	
}

HRESULT C_TextureMgr::InsertTexture(LPDIRECT3DDEVICE9 pDevice, TEXTYPE Type, const TCHAR* pTextureName, const TCHAR* pStateKey, const int& nCnt /*= 1*/)
{
	std::map<const TCHAR*, C_Texture*>::iterator iter = m_MapTexture.find(pStateKey);
	if (iter!=m_MapTexture.end())
	{
		TCHAR szTmp[128] = L"This key already exists StateKey:";
		lstrcat(szTmp, pStateKey);

		MSGBOX_OK(szTmp);
		return E_FAIL;
	}

	C_Texture* pTexture = NULL;
	switch (Type)
	{
	case TEX_GENERAL:
		pTexture = new C_TexGeneral();
		break;
	case TEX_CUBE:
		pTexture = new C_TexCube();
		break;
	default:
		break;
	}
	if (!pTexture)
	{
		MSGBOX_OK(L"Texture Type is None");
		return E_FAIL;
	}

	if (FAILED(pTexture->InitTexture(pDevice,pTextureName,pStateKey,nCnt)))
	{
		MSGBOX_OK(L"Don't Insert Texture");
		return E_FAIL;
	}

	m_MapTexture.insert(std::make_pair(pStateKey, pTexture));

	return S_OK;
}

const TEXINFO* C_TextureMgr::GetTexInfo(const TCHAR* pStateKey, const int& nIndex/*=0*/)
{
	std::map<const TCHAR*, C_Texture*>::iterator iter = m_MapTexture.find(pStateKey);
	if (iter == m_MapTexture.end())
	{
		MSGBOX_OK(L"Don't Find Key");
		return NULL;
	}

	return iter->second->GetTexInfo(pStateKey, nIndex);
}

void C_TextureMgr::Release()
{
	std::map<const TCHAR*, C_Texture*>::iterator iter = m_MapTexture.begin();

	while (iter!=m_MapTexture.end())
	{
		if (iter->second)
		{
			iter->second->Relaese();
			delete iter->second;
			iter->second = NULL;
		}
		iter++;
	}

	m_MapTexture.clear();
}
