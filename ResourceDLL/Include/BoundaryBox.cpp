#include "BoundaryBox.h"


C_BoundaryBox::C_BoundaryBox() :C_Bound()
{
}


C_BoundaryBox::~C_BoundaryBox()
{
	Release();
}

HRESULT C_BoundaryBox::InitBound(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(D3DXCreateBox(pDevice, 1.0f, 1.0f, 1.0f, &m_pMesh, NULL)))
		return E_FAIL;

	SetComputeBound();

	return S_OK;
}

void C_BoundaryBox::SetComputeBound()
{
	void* pVtx = NULL;

	m_pMesh->LockVertexBuffer(0, &pVtx);

	DWORD dwVtxCnt = m_pMesh->GetNumVertices();
	DWORD dwVtxFVF = m_pMesh->GetFVF();
	UINT nVtxSize = D3DXGetFVFVertexSize(dwVtxFVF);

	D3DXComputeBoundingBox((D3DXVECTOR3*)pVtx, dwVtxCnt, nVtxSize, &m_vMin, &m_vMax);

	m_pMesh->UnlockVertexBuffer();
}
