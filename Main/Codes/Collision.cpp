#include "StdAfx.h"
#include "Collision.h"

C_Collision::C_Collision()
{
}


C_Collision::~C_Collision()
{
}

bool C_Collision::AABB(D3DXVECTOR3 vDstMin, D3DXVECTOR3 vDstMax, D3DXVECTOR3 vSrcMin, D3DXVECTOR3 vSrcMax)
{
	if (max(vDstMin.x, vSrcMin.x) > min(vDstMax.x, vSrcMax.x))
		return false;

	if (max(vDstMin.y, vSrcMin.y) > min(vDstMax.y, vSrcMax.y))
		return false;

	if (max(vDstMin.z, vSrcMin.z) > min(vDstMax.z, vSrcMax.z))
		return false;

	return true;
}

bool C_Collision::AABBtoPoint(D3DXVECTOR3 vDstPoint, D3DXVECTOR3 vSrcMin, D3DXVECTOR3 vSrcMax)
{
	return true;
}

bool C_Collision::OBB(const D3DXVECTOR3* pDstMax, const D3DXVECTOR3* pDstMin, const D3DXMATRIX* pDstWorld,
	const D3DXVECTOR3* pSrcMax, const D3DXVECTOR3* pSrcMin, const D3DXMATRIX* pSrcWorld)
{

	//분리축 후보군을 생성한다.
	tagOBB  Obb[2];
	ZeroMemory(Obb, sizeof(tagOBB) * 2);

	SetPoint(&Obb[0], pDstMax, pDstMax);
	SetPoint(&Obb[1], pSrcMax, pSrcMin);

	for (int i = 0; i < 8; ++i)
	{
		D3DXVec3TransformCoord(&Obb[0].vPoint[i], &Obb[0].vPoint[i], pDstWorld);
		D3DXVec3TransformCoord(&Obb[1].vPoint[i], &Obb[1].vPoint[i], pSrcWorld);
	}

	D3DXVec3TransformCoord(&Obb[0].vCenter, &Obb[0].vCenter, pDstWorld);
	D3DXVec3TransformCoord(&Obb[1].vCenter, &Obb[1].vCenter, pSrcWorld);



	//분리축 후보군을 생성
	for (int i = 0; i < 2; ++i)
	{
		MakeAxis(&Obb[i]);
	}


	float    fDistance[3];

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			fDistance[0] = fabs(D3DXVec3Dot(&Obb[0].vProj[0], &Obb[i].vAxis[j]))
				+ fabs(D3DXVec3Dot(&Obb[0].vProj[1], &Obb[i].vAxis[j]))
				+ fabs(D3DXVec3Dot(&Obb[0].vProj[2], &Obb[i].vAxis[j]));

			fDistance[1] = fabs(D3DXVec3Dot(&Obb[1].vProj[0], &Obb[i].vAxis[j]))
				+ fabs(D3DXVec3Dot(&Obb[1].vProj[1], &Obb[i].vAxis[j]))
				+ fabs(D3DXVec3Dot(&Obb[1].vProj[2], &Obb[i].vAxis[j]));

			D3DXVECTOR3	 vTmp = Obb[0].vCenter - Obb[1].vCenter;
			fDistance[2] = fabs(D3DXVec3Dot(&vTmp, &Obb[i].vAxis[j]));

			if (fDistance[0] + fDistance[1] < fDistance[2])
				return false;

		}
	}

	return true;
}

bool C_Collision::SpehereCollision(D3DXVECTOR3 vDstPos, float fDstRadius, D3DXVECTOR3 vSrcPos, float fSrcRadius)
{
	return true;
}

void C_Collision::SetPoint(tagOBB* pOBB, const D3DXVECTOR3* pMax, const D3DXVECTOR3* pMin)
{
	pOBB->vPoint[0] = D3DXVECTOR3(pMin->x, pMax->y, pMin->z);
	pOBB->vPoint[1] = D3DXVECTOR3(pMax->x, pMax->y, pMin->z);
	pOBB->vPoint[2] = D3DXVECTOR3(pMax->x, pMin->y, pMin->z);
	pOBB->vPoint[3] = D3DXVECTOR3(pMin->x, pMin->y, pMin->z);

	pOBB->vPoint[4] = D3DXVECTOR3(pMin->x, pMax->y, pMax->z);
	pOBB->vPoint[5] = D3DXVECTOR3(pMax->x, pMax->y, pMax->z);
	pOBB->vPoint[6] = D3DXVECTOR3(pMax->x, pMin->y, pMax->z);
	pOBB->vPoint[7] = D3DXVECTOR3(pMin->x, pMin->y, pMax->z);

	pOBB->vCenter = (*pMax + *pMin) / 2.f;
}

void C_Collision::MakeAxis(tagOBB* pOBB)
{
	pOBB->vAxis[0] = pOBB->vPoint[1] - pOBB->vPoint[0];
	pOBB->vAxis[1] = pOBB->vPoint[1] - pOBB->vPoint[2];
	pOBB->vAxis[2] = pOBB->vPoint[5] - pOBB->vPoint[1];

	for (int i = 0; i < 3; ++i)
	{
		D3DXVec3Normalize(&pOBB->vAxis[i], &pOBB->vAxis[i]);
	}

	pOBB->vProj[0] = (pOBB->vPoint[1] + pOBB->vPoint[2] + pOBB->vPoint[5]
		+ pOBB->vPoint[6]) / 4.f - pOBB->vCenter;
	pOBB->vProj[1] = (pOBB->vPoint[0] + pOBB->vPoint[1] +
		pOBB->vPoint[4] + pOBB->vPoint[5]) / 4.f - pOBB->vCenter;
	pOBB->vProj[2] = (pOBB->vPoint[4] + pOBB->vPoint[5] +
		pOBB->vPoint[7] + pOBB->vPoint[6]) / 4.f - pOBB->vCenter;

}

bool C_Collision::CollSpriteMouse(D3DXVECTOR3 vMousePos, D3DXVECTOR3 vPos, D3DXVECTOR3 vCenter)
{
	if (vMousePos.x > vPos.x - vCenter.x && vMousePos.x <= vPos.x + vCenter.x &&
		vMousePos.y > vPos.y - vCenter.y && vMousePos.y <= vPos.y + vCenter.y)
	{
		return true;
	}

	return false;
}
