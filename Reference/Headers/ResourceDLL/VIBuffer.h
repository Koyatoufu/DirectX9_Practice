#pragma once

#define RESOURCE_EXPORT
#include "ResourceDef.h"

EXTERN class RESOURCE_DLL C_VIBuffer
{
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	DWORD m_dwVtxFVF;
	UINT m_nVtxSize;
	UINT m_nVtxCnt;
protected:
	LPDIRECT3DINDEXBUFFER9 m_pIB;
	DWORD m_dwTriCnt;
	D3DFORMAT m_IdxFmt;
	UINT m_nIdxSize;
public:
	virtual HRESULT InitializeBuffer(LPDIRECT3DDEVICE9 pDevice
		, const int& nVtxCntX = 0
		, const int& nVtxCntZ = 0
		, const float& fGap = 1.0f
		, const TCHAR* pTFileName = NULL);
	virtual void BufferRender(LPDIRECT3DDEVICE9 pDevice) = 0;
	virtual void Release();
public:
	void CopyVertexInfo(void* pVtxOri);
	void CopyIndexInfo(INDEX* pIndex,int nTricnt);
	void PasteVertexInfo(void* pVertex);
public:
	C_VIBuffer();
	virtual ~C_VIBuffer();
};