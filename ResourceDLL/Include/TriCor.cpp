#include "TriCor.h"


C_TriCor::C_TriCor()
{
}


C_TriCor::~C_TriCor()
{
}

HRESULT C_TriCor::InitializeBuffer(LPDIRECT3DDEVICE9 pDevice, const int& nVtxCntX /*= 0 */, const int& nVtxCntZ /*= 0 */, const float& fGap /*= 1.0f */, const TCHAR* pTFileName /*= NULL*/)
{
	m_nVtxSize = sizeof(VTXCOR);
	m_nVtxCnt = 3;
	m_dwVtxFVF = VTXFVF_VTXCOR;
	m_dwTriCnt = 1;


	if (FAILED(pDevice->CreateVertexBuffer(m_nVtxSize * m_nVtxCnt
		, 0, m_dwVtxFVF, D3DPOOL_MANAGED, &m_pVB, NULL)))
	{
		return E_FAIL;
	}

	VTXCOR* pVtxCol = NULL;

	//버텍스에 대한 공간을 할당
	m_pVB->Lock(0, 0, (void**)&pVtxCol, 0);

	pVtxCol[0].vPosition = D3DXVECTOR3(0.f, 1.f, 0.f);
	pVtxCol[0].dwColor = D3DCOLOR_RGBA(0, 0, 0, 255);

	pVtxCol[1].vPosition = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVtxCol[1].dwColor = D3DCOLOR_RGBA(0, 0, 0, 255);

	pVtxCol[2].vPosition = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVtxCol[2].dwColor = D3DCOLOR_RGBA(0, 0, 0, 255);

	m_pVB->Unlock();




	return S_OK;
}

void C_TriCor::BufferRender(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetStreamSource(0, m_pVB, 0, m_nVtxSize);
	pDevice->SetFVF(m_dwVtxFVF);
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_dwTriCnt);
}

void C_TriCor::Release()
{
	C_VIBuffer::Release();
}
