#include "BoundarySphere.h"


C_BoundarySphere::C_BoundarySphere() :C_Bound()
{
}


C_BoundarySphere::~C_BoundarySphere()
{
}

HRESULT C_BoundarySphere::InitBound(LPDIRECT3DDEVICE9 pDevice)
{
	if (D3DXCreateSphere(pDevice,1.0f,10,10,&m_pMesh,NULL))//slice:�浵�� ���ؽ� ������,stack:������ ���ؽ� ������
	{
		return E_FAIL;
	}

	SetComputeBound();

	return S_OK;
}

void C_BoundarySphere::SetComputeBound()
{
	void *pVtx = NULL;

	m_pMesh->LockVertexBuffer(0, &pVtx);

	DWORD dwVtxCnt = m_pMesh->GetNumVertices();
	DWORD dwVtxFVF = m_pMesh->GetFVF();
	UINT nVtxSize = D3DXGetFVFVertexSize(dwVtxFVF);

	D3DXComputeBoundingSphere((D3DXVECTOR3*)pVtx, dwVtxCnt, nVtxSize, NULL, &m_fRadius);

	m_pMesh->UnlockVertexBuffer();
}

