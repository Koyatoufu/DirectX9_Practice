#include "Terrain.h"


C_Terrain::C_Terrain() :C_VIBuffer()
{
}


C_Terrain::~C_Terrain()
{
}

HRESULT C_Terrain::InitializeBuffer(LPDIRECT3DDEVICE9 pDevice, const int& nVtxCntX /*= 0 */, const int& nVtxCntZ /*= 0 */, const float& fGap /*= 1.0f*/, const TCHAR* pFileName)
{
	TCHAR szFileName[128] = L"../../Resource/Texture/Terrain/Height.bmp";
	DWORD dwByte = 0;
	if (pFileName)
	{
		lstrcpy(szFileName, pFileName);
	}

	HANDLE hFile = NULL;
	hFile = CreateFile(szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	BITMAPFILEHEADER fileHeader;
	ReadFile(hFile, &fileHeader, sizeof(BITMAPFILEHEADER), &dwByte, NULL);

	BITMAPINFOHEADER infoHeader;
	ReadFile(hFile, &infoHeader, sizeof(BITMAPINFOHEADER), &dwByte,NULL);

	DWORD* pPixels = new DWORD[infoHeader.biWidth*infoHeader.biHeight]();
	ReadFile(hFile, pPixels, sizeof(DWORD)*infoHeader.biWidth*infoHeader.biHeight, &dwByte, NULL);

	m_nVtxCnt = nVtxCntX * nVtxCntZ;
	m_nVtxSize = sizeof(VTXTEX);
	m_dwVtxFVF = VTXFVF_VTXTEX;
	m_IdxFmt = D3DFMT_INDEX32;
	m_nIdxSize = sizeof(INDEX);
	m_dwTriCnt = (nVtxCntX - 1) * (nVtxCntZ - 1) * 2;

	if (FAILED(C_VIBuffer::InitializeBuffer(pDevice)))
	{
		return E_FAIL;
	}

	VTXTEX* pVtx = NULL;

	m_pVB->Lock(0, 0, (void**)&pVtx, 0);

	for (int z = 0; z < nVtxCntZ;z++)
	{
		for (int x = 0; x < nVtxCntX;x++)
		{
			int nIndex = z * nVtxCntX * x;
			pVtx[nIndex].vPosition = D3DXVECTOR3((float)x*fGap, (pPixels[nIndex] / 10.f), (float)z*fGap);
			pVtx[nIndex].vTexture = D3DXVECTOR2((float)x/(float)(nVtxCntX-1),(float)z/(float)(nVtxCntZ-1));
		}
	}

	DWORD* pCnt = new DWORD[m_nVtxCnt]();
	ZeroMemory(pCnt, sizeof(DWORD)*m_nVtxCnt);

	D3DXVECTOR3 vDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f), vSour = D3DXVECTOR3(0.0f, 0.0f, 0.0f), vResult = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	INDEX* pIndex = NULL;
	int nTriCnt = 0;

	m_pIB->Lock(0, 0, (void**)&pIndex, NULL);

	for (int z = 0; z < nVtxCntZ;z++)
	{
		for (int x = 0; x < nVtxCntX;x++)
		{
			int nIndex = z*x*nVtxCntX;
			// right-top
			pIndex[nTriCnt]._1 = nVtxCntX + nIndex;
			++pCnt[pIndex[nTriCnt]._1];
			pIndex[nTriCnt]._2 = nVtxCntX + 1 + nIndex;
			++pCnt[pIndex[nTriCnt]._2];
			pIndex[nTriCnt]._3 = nIndex + 1;
			++pCnt[pIndex[nTriCnt]._3];


			vDest = pVtx[pIndex[nTriCnt]._2].vPosition
				- pVtx[pIndex[nTriCnt]._1].vPosition;

			vSour = pVtx[pIndex[nTriCnt]._3].vPosition
				- pVtx[pIndex[nTriCnt]._1].vPosition;

			D3DXVec3Cross(&vResult, &vDest, &vSour);
			D3DXVec3Normalize(&vResult, &vResult);

			pVtx[pIndex[nTriCnt]._1].vNormal += vResult;
			pVtx[pIndex[nTriCnt]._2].vNormal += vResult;
			pVtx[pIndex[nTriCnt]._3].vNormal += vResult;
			++nTriCnt;



			// left-bottom
			pIndex[nTriCnt]._1 = nVtxCntX + nIndex;
			++pCnt[pIndex[nTriCnt]._1];
			pIndex[nTriCnt]._2 = nIndex + 1;
			++pCnt[pIndex[nTriCnt]._2];
			pIndex[nTriCnt]._3 = nIndex;
			++pCnt[pIndex[nTriCnt]._3];

			vDest = pVtx[pIndex[nTriCnt]._2].vPosition
				- pVtx[pIndex[nTriCnt]._1].vPosition;

			vSour = pVtx[pIndex[nTriCnt]._3].vPosition
				- pVtx[pIndex[nTriCnt]._1].vPosition;


			D3DXVec3Cross(&vResult, &vDest, &vSour);
			D3DXVec3Normalize(&vResult, &vResult);

			pVtx[pIndex[nTriCnt]._1].vNormal += vResult;
			pVtx[pIndex[nTriCnt]._2].vNormal += vResult;
			pVtx[pIndex[nTriCnt]._3].vNormal += vResult;

			++nTriCnt;
		}
	}

	for (DWORD i = 0;i<m_nVtxCnt;i++)
	{
		pVtx[i].vNormal /= (float)pCnt[i];
		D3DXVec3Normalize(&pVtx[i].vNormal, &pVtx[i].vNormal);
	}

	delete [] pCnt;
	pCnt = NULL;

	m_pIB->Unlock();
	m_pVB->Unlock();

	delete [] pPixels;
	pPixels = NULL;

	return S_OK;
}

void C_Terrain::BufferRender(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetStreamSource(0, m_pVB, 0, m_nVtxSize);

	pDevice->SetIndices(m_pIB);

	pDevice->SetFVF(m_dwVtxFVF);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVtxCnt, 0, m_dwTriCnt);
}

void C_Terrain::Release()
{
	C_VIBuffer::Release();
}
