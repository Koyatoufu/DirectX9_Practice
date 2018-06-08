#include "RectBuffer.h"


C_RectBuffer::C_RectBuffer()
{
}


C_RectBuffer::~C_RectBuffer()
{
	C_VIBuffer::~C_VIBuffer();
}

HRESULT C_RectBuffer::InitializeBuffer(LPDIRECT3DDEVICE9 pDevice, const int& nVtxCntX /*= 0 */, const int& nVtxCntZ /*= 0 */, const float& fGap /*= 1.0f*/, const TCHAR* pFileName)
{
	m_nVtxSize = sizeof(VTXTEX);
	m_nVtxCnt = 4;
	m_dwVtxFVF = VTXFVF_VTXTEX;
	m_dwTriCnt = 2;

	m_nIdxSize = sizeof(INDEX);
	m_IdxFmt = D3DFMT_INDEX32;

	if (FAILED(C_VIBuffer::InitializeBuffer(pDevice,nVtxCntX,nVtxCntZ,fGap)))
	{
		return E_FAIL;
	}

	VTXTEX* pVtxTex=NULL;

	if (FAILED(m_pVB->Lock(0, 0, (void**)&pVtxTex, NULL)))
	{
		return E_FAIL;
	}

	memset(pVtxTex, 0, m_nVtxCnt*m_nVtxSize);

	pVtxTex[0].vPosition = D3DXVECTOR3(-1.f, 1.f, 0.f);
	pVtxTex[0].vTexture = D3DXVECTOR2(0.f, 0.f);

	pVtxTex[1].vPosition = D3DXVECTOR3(1.f, 1.f, 0.f);
	pVtxTex[1].vTexture = D3DXVECTOR2(1.f, 0.f);

	pVtxTex[2].vPosition = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVtxTex[2].vTexture = D3DXVECTOR2(1.f, 1.f);

	pVtxTex[3].vPosition = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVtxTex[3].vTexture = D3DXVECTOR2(0.f, 1.f);

	m_pVB->Unlock();

	INDEX*			pIndex = NULL;

	if (FAILED(m_pIB->Lock(0, 0, (void**)&pIndex, 0)))
	{
		return E_FAIL;
	}

	pIndex[0]._1 = 0;
	pIndex[0]._2 = 1;
	pIndex[0]._3 = 2;

	pIndex[1]._1 = 0;
	pIndex[1]._2 = 2;
	pIndex[1]._3 = 3;

	m_pIB->Unlock();

	return S_OK;
}

void C_RectBuffer::BufferRender(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetStreamSource(0, m_pVB, 0, m_nVtxSize);

	pDevice->SetIndices(m_pIB);

	pDevice->SetFVF(m_dwVtxFVF);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVtxCnt, 0, m_dwTriCnt);
}

void C_RectBuffer::Release()
{
	C_VIBuffer::Release();
}
