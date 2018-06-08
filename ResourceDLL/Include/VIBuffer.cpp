#include "VIBuffer.h"


C_VIBuffer::C_VIBuffer() :m_pIB(NULL), m_pVB(NULL), m_nVtxCnt(0), m_nVtxSize(0),m_dwVtxFVF(0),m_nIdxSize(0) ,m_IdxFmt(),m_dwTriCnt(0)
{
	ZeroMemory(&m_IdxFmt, sizeof(D3DFORMAT));
}


C_VIBuffer::~C_VIBuffer()
{
}

HRESULT C_VIBuffer::InitializeBuffer(LPDIRECT3DDEVICE9 pDevice
	, const int& nVtxCntX
	, const int& nVtxCntZ
	, const float& fGap
	, const TCHAR* pFileName)
{

	if (pDevice->CreateVertexBuffer(m_nVtxCnt*m_nVtxSize,0,m_dwVtxFVF,D3DPOOL_DEFAULT,&m_pVB,NULL))
	{
		MSGBOX_OK(L"Don't CreateVeretexBuffer");
		return E_FAIL;
	}

	if (pDevice->CreateIndexBuffer(m_nIdxSize*m_dwTriCnt,0,m_IdxFmt,D3DPOOL_DEFAULT,&m_pIB,NULL))
	{
		MSGBOX_OK(L"Don't CreateIndexBuffer");
		return E_FAIL;
	}

	return S_OK;
}

void C_VIBuffer::Release()
{
	if (m_pIB)
	{
		m_pIB->Release();
		m_pIB = NULL;
	}
	if (m_pVB)
	{
		m_pVB->Release();
		m_pVB = NULL;
	}
}

void C_VIBuffer::CopyVertexInfo(void* pVtxOri)
{
	//VTXTEX* pVerTex=NULL;
	void* pVertex=NULL;

	m_pVB->Lock(0, 0, &pVtxOri, 0);

	memcpy(pVertex, pVtxOri, m_nVtxCnt*m_nVtxSize);

	m_pVB->Unlock();
}

void C_VIBuffer::CopyIndexInfo(INDEX* pIndex, int nTricnt)
{
	INDEX* pOrnIndex = NULL;
	
	m_dwTriCnt = (DWORD)nTricnt;

	m_pIB->Lock(0, 0, (void**)&pOrnIndex, 0);

	memcpy(&pOrnIndex, &pIndex, nTricnt*m_nIdxSize);

	m_pIB->Unlock();

}

void C_VIBuffer::PasteVertexInfo(void* pVertex)
{
	//VTXTEX* pVerTex=NULL;
	void* pVtxtmp=NULL;

	m_pVB->Lock(0, 0, &pVtxtmp, 0);

	memcpy(&pVertex, &pVtxtmp, m_nVtxSize*m_nVtxCnt);

	m_pVB->Unlock();
}
