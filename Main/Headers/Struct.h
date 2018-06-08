#pragma once

typedef struct tagObjectInfo
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vUp;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXMATRIX matWorld;
}OBJINFO;

typedef struct tagAttribute
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vDirection;
	DWORD dwColor;
	bool bAllive;
}ATTRIBUTE;

typedef struct tagStatusInfo
{
	float fLife;
	float fMaxLife;
	float fEnergy;
	float fMaxEnergy;
	float fAtk;
	float fDefece;
}STATUSINFO;

typedef struct tagCollisionInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vMin;
	D3DXVECTOR3 vMax;
	float fRadius;
}CollsionInfo;