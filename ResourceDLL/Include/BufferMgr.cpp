#include "BufferMgr.h"

IMPLEMENT_SINGLETONE_RESDLL(C_BufferMgr);

C_BufferMgr::C_BufferMgr() :m_mapBuffer()
{
}


C_BufferMgr::~C_BufferMgr()
{
}

HRESULT C_BufferMgr::AddBuffer(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pBufferKey, BUFFTYPE bufftype, const int& nVtxCntX , const int& nVtxCntZ , const float& fGap ,const TCHAR* pFileName)
{
	C_VIBuffer* pBuffer = NULL;

	switch (bufftype)
	{
	case BUFF_RECT:
		pBuffer = new C_RectBuffer();
		break;
	case BUFF_TriCor:
		pBuffer = new C_TriCor();
		break;
	case BUFF_CUBE:
		pBuffer = new C_CubeBuffer();
		break;
	case BUFF_GRID:
		pBuffer = new C_GridBuffer();
		break;
	default:
		break;
	}

	if (!pBuffer)
	{
		MSGBOX_OK(L"NULLBUFFER");
		return E_FAIL;
	}

	if (FAILED(pBuffer->InitializeBuffer(pDevice,nVtxCntX,nVtxCntZ,fGap,pFileName)))
	{
		MSGBOX_OK(L"Don't InitializeBuffer");
		
		delete pBuffer;
		pBuffer = NULL;
		
		return E_FAIL;
	}

	m_mapBuffer.insert(std::make_pair(pBufferKey,pBuffer));

	return S_OK;
}

void C_BufferMgr::Release()
{
	std::map<const TCHAR*, C_VIBuffer*>::iterator iter = m_mapBuffer.begin();

	while (iter!=m_mapBuffer.end())
	{
		iter->second->Release();
		delete iter->second;
		iter->second = NULL;
		iter++;
	}

	m_mapBuffer.clear();
}

void C_BufferMgr::CopyVertexInfo(const TCHAR* pBufferKey, void* pVtxOri)
{
	std::map<const TCHAR*, C_VIBuffer*>::iterator iter= m_mapBuffer.find(pBufferKey);

	if (iter==m_mapBuffer.end())
		return;

	iter->second->CopyVertexInfo(pVtxOri);
}

void C_BufferMgr::CopyIndexInfo(const TCHAR* pBufferKey, INDEX* pIndex, int nTricnt)
{
	std::map<const TCHAR*, C_VIBuffer*>::iterator iter = m_mapBuffer.find(pBufferKey);

	if (iter == m_mapBuffer.end())
		return;

	iter->second->CopyIndexInfo(pIndex, nTricnt);
}

void C_BufferMgr::PasteVertexInfo(const TCHAR* pBufferKey, void* pVertex)
{
	std::map<const TCHAR*, C_VIBuffer*>::iterator iter = m_mapBuffer.find(pBufferKey);

	if (iter == m_mapBuffer.end())
		return;

	iter->second->PasteVertexInfo(pVertex);
}

void C_BufferMgr::Buffer_Render(LPDIRECT3DDEVICE9 pDevice,const TCHAR* pBufferKey)
{
	std::map<const TCHAR*, C_VIBuffer*>::iterator iter = m_mapBuffer.find(pBufferKey);

	if (iter == m_mapBuffer.end())
		return;

	iter->second->BufferRender(pDevice);
}

