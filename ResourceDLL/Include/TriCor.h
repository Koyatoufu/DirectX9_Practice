#pragma once
#include "VIBuffer.h"
class C_TriCor:public C_VIBuffer
{
	virtual HRESULT InitializeBuffer(LPDIRECT3DDEVICE9 pDevice
		, const int& nVtxCntX = 0
		, const int& nVtxCntZ = 0
		, const float& fGap = 1.0f
		, const TCHAR* pTFileName = NULL);
	virtual void BufferRender(LPDIRECT3DDEVICE9 pDevice);
	virtual void Release();
public:
	C_TriCor();
	~C_TriCor();
};

