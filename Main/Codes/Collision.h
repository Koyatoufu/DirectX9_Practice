#pragma once
#include "Define.h"

class C_Collision
{
private:
	typedef struct tagOBB
	{
		D3DXVECTOR3		vProj[3];
		D3DXVECTOR3		vAxis[3];
		D3DXVECTOR3		vPoint[8];
		D3DXVECTOR3		vCenter;
	};
public:
	static bool AABB(D3DXVECTOR3 vDstMin,D3DXVECTOR3 vDstMax,D3DXVECTOR3 vSrcMin,D3DXVECTOR3 vSrcMax);
	static bool AABBtoPoint(D3DXVECTOR3 vDstPoint , D3DXVECTOR3 vSrcMin, D3DXVECTOR3 vSrcMax);
	static bool OBB(const D3DXVECTOR3* pDstMax, const D3DXVECTOR3* pDstMin, const D3DXMATRIX* pDstWorld,
		const D3DXVECTOR3* pSrcMax, const D3DXVECTOR3* pSrcMin, const D3DXMATRIX* pSrcWorld);
	static bool SpehereCollision(D3DXVECTOR3 vDstPos, float fDstRadius, D3DXVECTOR3 vSrcPos, float fSrcRadius);
public:
	static bool CollSpriteMouse(D3DXVECTOR3 vMousePos,D3DXVECTOR3 vPos,D3DXVECTOR3 vCenter);
private:
	static void SetPoint(tagOBB* pOBB, const D3DXVECTOR3* pMax, const D3DXVECTOR3* pMin);
	static void MakeAxis(tagOBB* pOBB);
public:
	C_Collision();
	~C_Collision();
};

