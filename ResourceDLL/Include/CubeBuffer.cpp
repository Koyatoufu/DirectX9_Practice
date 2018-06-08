#include "CubeBuffer.h"


C_CubeBuffer::C_CubeBuffer()
{
}


C_CubeBuffer::~C_CubeBuffer()
{
}

HRESULT C_CubeBuffer::InitializeBuffer(LPDIRECT3DDEVICE9 pDevice, const int& nVtxCntX /*= 0 */, const int& nVtxCntZ /*= 0 */, const float& fGap /*= 1.0f*/, const TCHAR* pFileName)
{
	m_nVtxSize = sizeof(VTXCUBE);
	m_nVtxCnt = 8;
	m_dwVtxFVF = VTXFVF_CUBETEX;
	m_dwTriCnt = 12;

	m_nIdxSize = sizeof(INDEX);
	m_IdxFmt = D3DFMT_INDEX32;

	if (C_VIBuffer::InitializeBuffer(pDevice,nVtxCntX,nVtxCntZ,fGap))
	{
		return E_FAIL;
	}

	VTXCUBE* pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	ZeroMemory(pVertex, m_nVtxCnt*m_nVtxSize);

	// ¾Õ
	pVertex[0].vPosition = D3DXVECTOR3(-1.f, 1.f, -1.f);
	pVertex[0].vTexture = pVertex[0].vPosition;

	pVertex[1].vPosition = D3DXVECTOR3(1.f, 1.f, -1.f);
	pVertex[1].vTexture = pVertex[1].vPosition;

	pVertex[2].vPosition = D3DXVECTOR3(1.f, -1.f, -1.f);
	pVertex[2].vTexture = pVertex[2].vPosition;

	pVertex[3].vPosition = D3DXVECTOR3(-1.f, -1.f, -1.f);
	pVertex[3].vTexture = pVertex[3].vPosition;

	// µÚ
	pVertex[4].vPosition = D3DXVECTOR3(-1.f, 1.f, 1.f);
	pVertex[4].vTexture = pVertex[4].vPosition;

	pVertex[5].vPosition = D3DXVECTOR3(1.f, 1.f, 1.f);
	pVertex[5].vTexture = pVertex[5].vPosition;

	pVertex[6].vPosition = D3DXVECTOR3(1.f, -1.f, 1.f);
	pVertex[6].vTexture = pVertex[6].vPosition;

	pVertex[7].vPosition = D3DXVECTOR3(-1.f, -1.f, 1.f);
	pVertex[7].vTexture = pVertex[7].vPosition;

	m_pVB->Unlock();

	INDEX* pIndex = NULL;

	int	 nTriCnt = 0;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// +x
	pIndex[nTriCnt]._1 = 1; pIndex[nTriCnt]._2 = 5; pIndex[nTriCnt]._3 = 6;
	++nTriCnt;
	pIndex[nTriCnt]._1 = 1; pIndex[nTriCnt]._2 = 6; pIndex[nTriCnt]._3 = 2;
	++nTriCnt;

	// -x
	pIndex[nTriCnt]._1 = 4; pIndex[nTriCnt]._2 = 0; pIndex[nTriCnt]._3 = 3;
	++nTriCnt;
	pIndex[nTriCnt]._1 = 4; pIndex[nTriCnt]._2 = 3; pIndex[nTriCnt]._3 = 7;
	++nTriCnt;

	// +y
	pIndex[nTriCnt]._1 = 4; pIndex[nTriCnt]._2 = 5; pIndex[nTriCnt]._3 = 1;
	++nTriCnt;
	pIndex[nTriCnt]._1 = 4; pIndex[nTriCnt]._2 = 1; pIndex[nTriCnt]._3 = 0;
	++nTriCnt;

	// -y
	pIndex[nTriCnt]._1 = 7; pIndex[nTriCnt]._2 = 6; pIndex[nTriCnt]._3 = 2;
	++nTriCnt;
	pIndex[nTriCnt]._1 = 7; pIndex[nTriCnt]._2 = 2; pIndex[nTriCnt]._3 = 3;
	++nTriCnt;

	// +z
	pIndex[nTriCnt]._1 = 4; pIndex[nTriCnt]._2 = 5; pIndex[nTriCnt]._3 = 6;
	++nTriCnt;
	pIndex[nTriCnt]._1 = 4; pIndex[nTriCnt]._2 = 6; pIndex[nTriCnt]._3 = 7;
	++nTriCnt;

	// -z
	pIndex[nTriCnt]._1 = 0; pIndex[nTriCnt]._2 = 1; pIndex[nTriCnt]._3 = 2;
	++nTriCnt;
	pIndex[nTriCnt]._1 = 0; pIndex[nTriCnt]._2 = 2; pIndex[nTriCnt]._3 = 3;
	++nTriCnt;

	m_pIB->Unlock();

	return S_OK;
}

void C_CubeBuffer::BufferRender(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetStreamSource(0, m_pVB, 0, m_nVtxSize);

	pDevice->SetIndices(m_pIB);

	pDevice->SetFVF(m_dwVtxFVF);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVtxCnt, 0, m_dwTriCnt);
}

void C_CubeBuffer::Release()
{
	C_VIBuffer::Release();
}
