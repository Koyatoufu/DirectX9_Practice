#include "StdAfx.h"
#include "ShaderMgr.h"

IMPLEMENT_SINGLETONE(C_ShaderMgr);

C_ShaderMgr::C_ShaderMgr()
{
}


C_ShaderMgr::~C_ShaderMgr()
{
	Release();
}

HRESULT C_ShaderMgr::AddEffect(LPDIRECT3DDEVICE9 pDevice, EFFECTTYPE Type, const TCHAR* pFileName)
{
	std::map<EFFECTTYPE, C_Effect*>::iterator iter = m_mapEffect.find(Type);

	if (iter != m_mapEffect.end())
	{
		MSGBOX_OK(L"EffectExist");
		return S_OK;
	}

	C_Effect* pEffect = new C_Effect();

	if (FAILED(pEffect->InitShader(pDevice,pFileName)))
	{
		return E_FAIL;
	}

	m_mapEffect.insert(std::make_pair(Type, pEffect));

	return S_OK;
}

void C_ShaderMgr::Release()
{
	std::map<EFFECTTYPE, C_Effect*>::iterator iter = m_mapEffect.begin();
	
	while (iter!=m_mapEffect.end())
	{
		if (iter->second)
		{
			iter->second->Realese();
			delete iter->second;
			iter->second = NULL;
		}
		iter++;
	}

	m_mapEffect.clear();
}

LPD3DXEFFECT C_ShaderMgr::GetEffect(EFFECTTYPE Type)
{
	std::map<EFFECTTYPE, C_Effect*>::iterator iter = m_mapEffect.find(Type);

	if (iter==m_mapEffect.end())
	{
		return NULL;
	}

	return iter->second->GetEffect();
}

void C_ShaderMgr::Begin_Render(EFFECTTYPE Type,UINT nPassCnt)
{
	std::map<EFFECTTYPE, C_Effect*>::iterator iter = m_mapEffect.find(Type);

	if (iter == m_mapEffect.end())
	{
		return;
	}

	iter->second->Begin_Render(nPassCnt);
}

void C_ShaderMgr::End_Render(LPDIRECT3DDEVICE9 pDevice,EFFECTTYPE Type)
{
	std::map<EFFECTTYPE, C_Effect*>::iterator iter = m_mapEffect.find(Type);

	if (iter == m_mapEffect.end())
	{
		return;
	}

	iter->second->End_Render(pDevice);
}
