#include "StdAfx.h"
#include "Effect.h"


C_Effect::C_Effect() :m_pEffect(NULL), m_pError(NULL)
{
}


C_Effect::~C_Effect()
{
}

HRESULT C_Effect::InitShader(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pFileName)
{
	if (FAILED(D3DXCreateEffectFromFile(pDevice,pFileName,NULL,NULL,D3DXSHADER_DEBUG,NULL,&m_pEffect,&m_pError)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void C_Effect::Realese()
{
	if (m_pError)
	{
		m_pError->Release();
		m_pError = NULL;
	}
	if (m_pEffect)
	{
		m_pEffect->Release();
		m_pEffect = NULL;
	}
}

void C_Effect::Begin_Render(UINT nPassCnt)
{
	m_pEffect->Begin(&nPassCnt, NULL);

	for (UINT i = 0; i < nPassCnt;i++)
	{
		m_pEffect->BeginPass(i);
	}

}

void C_Effect::End_Render(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetPixelShader(NULL);
	pDevice->SetVertexShader(NULL);
	m_pEffect->EndPass();
	m_pEffect->End();
}

LPD3DXEFFECT C_Effect::GetEffect()
{
	return m_pEffect;
}
