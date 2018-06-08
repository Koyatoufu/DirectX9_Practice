#include "Bound.h"


C_Bound::C_Bound() :m_pMesh(NULL), m_vMin(0.0f, 0.0f, 0.0f), m_vMax(0.0f, 0.0f, 0.0f), m_fRadius(0.0f)
{
}


C_Bound::~C_Bound()
{

}

void C_Bound::BoundRender()
{
	SetComputeBound();
	m_pMesh->DrawSubset(0);
}

const D3DXVECTOR3* C_Bound::GetMin()
{
	return &m_vMin;
}

const D3DXVECTOR3* C_Bound::GetMax()
{
	return &m_vMax;
}

void C_Bound::Release()
{
	if (m_pMesh)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
}

float C_Bound::GetRadius()
{
	return m_fRadius;
}

void C_Bound::ScaleBound(float fScale)
{
	if (!m_pMesh)
	{
		return;
	}
	D3DXVECTOR3* pVtx = NULL;

	m_pMesh->LockVertexBuffer(0, (void**)&pVtx);

	DWORD dwVtxCnt = m_pMesh->GetNumVertices();
	DWORD dwVtxFVF = m_pMesh->GetFVF();
	UINT nVtxSize = D3DXGetFVFVertexSize(dwVtxFVF);

	for (DWORD i = 0; i < dwVtxCnt; i++)
	{
		pVtx->x *= fScale;
		pVtx->y *= fScale;
		pVtx->z *= fScale;

		pVtx++;
	}

	m_pMesh->UnlockVertexBuffer();

	SetComputeBound();
}

