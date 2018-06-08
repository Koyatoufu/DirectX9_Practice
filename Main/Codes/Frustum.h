#pragma once
#include "Define.h"
#include "ResourceDef.h"
#include "SystemDef.h"
class C_Frustum
{
	DECLARE_SINGLETONE(C_Frustum);
private:
	D3DXVECTOR3			m_vPoint[8];
	D3DXPLANE			m_Plane[6];
public: // Make Frustum
	void InitFrustum(void);
	void ConvertFrustum(VTXTEX* pVtxTex, const D3DXMATRIX* pMatrix);
public:
	int Culling(VTXTEX* pVtxTex, INDEX* pIndex);
	bool VertexInFrustum(const D3DXVECTOR3* pPoint);
	bool SphereInFrustum(float fRadius, const D3DXVECTOR3* pPoint);
public:
	C_Frustum();
	~C_Frustum();
};

