#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"

EXTERN class RESOURCE_DLL C_HierarchyLoader: public ID3DXAllocateHierarchy
{
private:
	TCHAR				m_szPath[128];
public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, 
		LPD3DXFRAME *ppNewFrame) ;
	STDMETHOD(CreateMeshContainer)(THIS_ 
		LPCSTR Name, 
		CONST D3DXMESHDATA *pMeshData, 
		CONST D3DXMATERIAL *pMaterials, 
		CONST D3DXEFFECTINSTANCE *pEffectInstances, 
		DWORD NumMaterials, 
		CONST DWORD *pAdjacency, 
		LPD3DXSKININFO pSkinInfo, 
		LPD3DXMESHCONTAINER *ppNewMeshContainer);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) ; 	
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree); 
public:
	C_HierarchyLoader(void);
	C_HierarchyLoader(const TCHAR* pPath);
	~C_HierarchyLoader(void);
};

