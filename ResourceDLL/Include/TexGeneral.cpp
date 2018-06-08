#include "TexGeneral.h"


C_TexGeneral::C_TexGeneral() :C_Texture()
{
}


C_TexGeneral::~C_TexGeneral()
{
	Relaese();
}

HRESULT C_TexGeneral::InitTexture(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pTextureName, const TCHAR* pStateKey, const int& nCnt /*= 1*/)
{
	std::map<const TCHAR*, std::vector<TEXINFO*>>::iterator iter = m_MapTexture.find(pStateKey);

	if (iter!=m_MapTexture.end())
	{
		return E_FAIL;
	}

	std::vector<TEXINFO*> vecTexure;
	vecTexure.reserve(nCnt);
	vecTexure.resize(nCnt);

	for (int i = 0; i < nCnt;i++)
	{
		TEXINFO* pTexInfo = new TEXINFO();

		TCHAR szTmp[128] = L"";

		wsprintf(szTmp,pTextureName,i);

		if (FAILED(D3DXGetImageInfoFromFile(szTmp, &pTexInfo->TexInfo)))
			return E_FAIL;

		if (FAILED(D3DXCreateTextureFromFileEx(pDevice,szTmp,
			pTexInfo->TexInfo.Width,pTexInfo->TexInfo.Height,pTexInfo->TexInfo.MipLevels,0,pTexInfo->TexInfo.Format,
			D3DPOOL_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_ARGB(0,255,255,0),
			&pTexInfo->TexInfo,NULL,&pTexInfo->pTexture)))
		{
			return E_FAIL;
		}

		vecTexure[i] = pTexInfo;

	}

	m_MapTexture.insert(std::make_pair(pStateKey, vecTexure));

	return S_OK;
}

void C_TexGeneral::Relaese()
{
	C_Texture::Relaese();
}
