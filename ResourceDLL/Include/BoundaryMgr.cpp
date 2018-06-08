#include "BoundaryMgr.h"

IMPLEMENT_SINGLETONE_RESDLL(C_BoundaryMgr);

C_BoundaryMgr::C_BoundaryMgr()
{
}


C_BoundaryMgr::~C_BoundaryMgr()
{
}

HRESULT C_BoundaryMgr::AddBoundary(LPDIRECT3DDEVICE9 pDevice, BOUNDTYPE Type)
{
	std::map<BOUNDTYPE,C_Bound*>::iterator iter=m_mapBound.find(Type);
	if (iter!=m_mapBound.end())
	{
		return E_FAIL;
	}

	C_Bound* pBound=NULL;

	switch (Type)
	{
	case BOUND_BOX:
		pBound = new C_BoundaryBox();
		break;
	case BOUND_CYLINDER:
		break;
	case BOUND_SPHERE:
		pBound = new C_BoundarySphere();
		break;
	default:
		break;
	}

	if (!pBound)
	{
		return E_FAIL;
	}

	if (FAILED(pBound->InitBound(pDevice)))
	{
		return E_FAIL;
	}

	m_mapBound.insert(std::make_pair(Type, pBound));

	return S_OK;
}

void C_BoundaryMgr::Release()
{
	std::map<BOUNDTYPE, C_Bound*>::iterator iter = m_mapBound.begin();

	while (iter != m_mapBound.end())
	{
		if (iter->second)
		{
			iter->second->Release();
			delete iter->second;
			iter->second = NULL;
		}
		iter++;
	}

	m_mapBound.clear();
}

const D3DXVECTOR3* C_BoundaryMgr::GetMin(BOUNDTYPE Type)
{
	std::map<BOUNDTYPE, C_Bound*>::iterator iter = m_mapBound.find(Type);
	if (iter == m_mapBound.end())
	{
		return NULL;
	}

	return iter->second->GetMin();
}

const D3DXVECTOR3* C_BoundaryMgr::GetMax(BOUNDTYPE Type)
{
	std::map<BOUNDTYPE, C_Bound*>::iterator iter = m_mapBound.find(Type);
	if (iter == m_mapBound.end())
	{
		return NULL;
	}

	return iter->second->GetMax();
}

float C_BoundaryMgr::GetRadius(BOUNDTYPE Type)
{
	std::map<BOUNDTYPE, C_Bound*>::iterator iter = m_mapBound.find(Type);
	if (iter == m_mapBound.end())
	{
		return 0.0f;
	}

	return iter->second->GetRadius();
}

void C_BoundaryMgr::ScaleBound(BOUNDTYPE Type, float fScale)
{
	std::map<BOUNDTYPE, C_Bound*>::iterator iter = m_mapBound.find(Type);
	if (iter == m_mapBound.end())
	{
		return;
	}
}
