#include "Texture.h"


C_Texture::C_Texture()
{
}


C_Texture::~C_Texture()
{
	Relaese();
}

void C_Texture::Relaese()
{
	std::map<const TCHAR*, std::vector<TEXINFO*>>::iterator iter = m_MapTexture.begin();
	while (iter != m_MapTexture.end())
	{
		for (DWORD i = 0; i < iter->second.size(); i++)
		{
			if (iter->second[i])
			{
				if (iter->second[i]->pTexture)
				{
					iter->second[i]->pTexture->Release();
					iter->second[i]->pTexture = NULL;
				}

				if (iter->second[i]->pCubeTexture)
				{
					iter->second[i]->pCubeTexture->Release();
					iter->second[i]->pCubeTexture = NULL;
				}

				delete iter->second[i];
				iter->second[i] = NULL;
			}
		}
		iter->second.clear();
		iter->second.~vector<TEXINFO*>();

		iter++;
	}

	m_MapTexture.clear();
}

const TEXINFO* C_Texture::GetTexInfo(const TCHAR* pStateKey, const int& nIndex /*= 0*/)
{
	std::map<const TCHAR*, std::vector<TEXINFO*>>::iterator iter = m_MapTexture.find(pStateKey);

	if (iter == m_MapTexture.end())
	{
		return NULL;
	}

	return iter->second[nIndex];
}
