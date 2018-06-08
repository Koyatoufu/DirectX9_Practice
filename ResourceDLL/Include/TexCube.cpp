#include "TexCube.h"


C_TexCube::C_TexCube() :C_Texture()
{
}


C_TexCube::~C_TexCube()
{
	Relaese();
}

HRESULT C_TexCube::InitTexture(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pTextureName, const TCHAR* pStateKey, const int& nCnt /*= 1*/)
{
	std::map<const TCHAR*, std::vector<TEXINFO*>>::iterator iter = m_MapTexture.find(pStateKey);

	if (iter != m_MapTexture.end())
	{
		return E_FAIL;
	}

	std::vector<TEXINFO*> vecTexure;
	vecTexure.reserve(nCnt);
	vecTexure.resize(nCnt);

	for (int i = 0; i < nCnt; i++)
	{
		TEXINFO* pTexInfo = new TEXINFO();

		TCHAR szTmp[128] = L"";

		wsprintf(szTmp, pTextureName, i);

		if (FAILED(D3DXGetImageInfoFromFile(szTmp, &pTexInfo->TexInfo)))
			return E_FAIL;

		if (FAILED(D3DXCreateCubeTextureFromFile(pDevice,szTmp,&pTexInfo->pCubeTexture)))
		{
			return E_FAIL;
		}

		vecTexure[i] = pTexInfo;

	}

	m_MapTexture.insert(make_pair(pStateKey,vecTexure));

	return S_OK;
}

void C_TexCube::Relaese()
{
	C_Texture::Relaese();
}
