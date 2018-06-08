#include "GridBuffer.h"


C_GridBuffer::C_GridBuffer() :C_VIBuffer()
{
}


C_GridBuffer::~C_GridBuffer()
{
	C_VIBuffer::~C_VIBuffer();
}

HRESULT C_GridBuffer::InitializeBuffer(LPDIRECT3DDEVICE9 pDevice, const int& nVtxCntX /*= 0 */, const int& nVtxCntZ /*= 0 */, const float& fGap /*= 1.0f*/, const TCHAR* pFileName)
{
	m_nVtxSize = sizeof(VTXCOR);

	m_nVtxCnt = 400;

	m_dwVtxFVF = VTXFVF_VTXCOR;

	if (pDevice->CreateVertexBuffer(m_nVtxCnt*m_nVtxSize, 0, m_dwVtxFVF, D3DPOOL_DEFAULT, &m_pVB, NULL))
	{
		MSGBOX_OK(L"Don't CreateVeretexBuffer");
		return E_FAIL;
	}

	VTXCOR* pVertex = NULL;

	if (FAILED(m_pVB->Lock(0, 0, (void**)&pVertex, NULL)))
	{
		return E_FAIL;
	}

	memset(pVertex, 0, sizeof(VTXCOR)*m_nVtxCnt);

	int nQuaterHalf = (int)(m_nVtxCnt / 8);

	for (int i = 0; i < 100; i++)
	{

		pVertex[i * 4].vPosition.x = (float)(-nQuaterHalf) + (float)i;
		pVertex[i * 4].vPosition.z = (float)(nQuaterHalf);
		pVertex[i * 4].dwColor = 0xffffffff;

		pVertex[i * 4 + 1].vPosition.x = (float)(-nQuaterHalf) + (float)i;
		pVertex[i * 4 + 1].vPosition.z = (float)(-nQuaterHalf);
		pVertex[i * 4 + 1].dwColor = 0xffffffff;

		pVertex[i * 4 + 2].vPosition.z = (float)(-nQuaterHalf) + (float)i;
		pVertex[i * 4 + 2].vPosition.x = (float)(nQuaterHalf);
		pVertex[i * 4 + 2].dwColor = 0xffffffff;

		pVertex[i * 4 + 3].vPosition.z = (float)(-nQuaterHalf) + (float)i;
		pVertex[i * 4 + 3].vPosition.x = (float)(-nQuaterHalf);
		pVertex[i * 4 + 3].dwColor = 0xffffffff;

	}

	m_pVB->Unlock();

	return S_OK;
}

void C_GridBuffer::BufferRender(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetStreamSource(0, m_pVB, 0, m_nVtxSize);

	pDevice->SetFVF(m_dwVtxFVF);

	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_nVtxCnt / 2);
}

void C_GridBuffer::Release()
{
	C_VIBuffer::Release();
}
