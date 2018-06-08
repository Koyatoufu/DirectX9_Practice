#pragma once

typedef struct tagVertexColor
{
	D3DXVECTOR3 vPosition;
	DWORD dwColor;
}VTXCOR;

const DWORD VTXFVF_VTXCOR = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

typedef struct tagVertexTexture
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vNormal;
	D3DXVECTOR2 vTexture;
}VTXTEX;

const DWORD VTXFVF_VTXTEX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

typedef struct tagVertexCube
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vTexture;
}VTXCUBE;

const DWORD VTXFVF_CUBETEX = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

typedef struct tagIndex
{
	DWORD _1, _2, _3;
}INDEX;

typedef struct tagTextureInfo
{
	D3DXIMAGE_INFO TexInfo;
	union 
	{
		LPDIRECT3DTEXTURE9 pTexture;
		LPDIRECT3DCUBETEXTURE9 pCubeTexture;
	};
}TEXINFO;

typedef struct tagBoneMesh : public D3DXMESHCONTAINER
{
	LPD3DXMESH pOriMesh;

	std::vector<D3DMATERIAL9> vecMtrl;
	std::vector<LPDIRECT3DTEXTURE9> vecTexture;

	DWORD dwAttCnt;

	D3DXATTRIBUTERANGE* pAttTable;

	D3DXMATRIX** ppBoneMatrix;
	D3DXMATRIX*					pBoneoffSetMatrix;
	D3DXMATRIX*					pCurrentBoneMatrix;

}BONEMESH;

typedef struct tagBone : public _D3DXFRAME 
{
	D3DXMATRIX matWorld;
}BONE;