#pragma once

#define RESOURCE_EXPORT

#include "ResourceDef.h"
#include "CubeBuffer.h"
#include "RectBuffer.h"
#include "GridBuffer.h"
#include "TriCor.h"

EXTERN class RESOURCE_DLL C_BufferMgr
{
	DECLARE_SINGLETONE_RESDLL(C_BufferMgr);
private:
	std::map<const TCHAR*, C_VIBuffer*> m_mapBuffer;
public:
	HRESULT AddBuffer(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pBufferKey, BUFFTYPE bufftype, const int& nVtxCntX = 0
		, const int& nVtxCntZ = 0
		, const float& fGap = 1.f
		, const TCHAR* pFileName = NULL);
	void Release();

	void CopyVertexInfo(const TCHAR* pBufferKey, void* pVtxOri);
	void CopyIndexInfo(const TCHAR* pBufferKey, INDEX* pIndex, int nTricnt);
	void PasteVertexInfo(const TCHAR* pBufferKey, void* pVertex);
	void Buffer_Render(LPDIRECT3DDEVICE9 pDevice,const TCHAR* pBufferKey);
private:
	C_BufferMgr();
	C_BufferMgr(const C_BufferMgr&);
	const C_BufferMgr& operator=(const C_BufferMgr&);
public:
	~C_BufferMgr();
};

