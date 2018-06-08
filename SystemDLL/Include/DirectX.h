#pragma once

#define SYSTEM_EXPORT

#include "SystemDef.h"
EXTERN class SYSTEM_DLL C_DirectX
{
	DECLARE_SINGLETONE_SYSDLL(C_DirectX);
private:
	LPDIRECT3D9 m_pD3D9;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE m_pSprite;
	LPD3DXFONT m_pFont;
	LPD3DXLINE m_pLine;
public:
	HRESULT InitDevice(HWND hWnd, int nSizeX, int nSizeY, bool bWinMode = false);
	void Release();

	void Begin_Render();
	void End_Render();
	void DrawFont(RECT rcFont, const TCHAR* pFont, DWORD dwFlag, DWORD dwColor);

	void SetRenderState(_D3DRENDERSTATETYPE Type, DWORD dwFlag);
	void SetTransformState(_D3DTRANSFORMSTATETYPE Type, const D3DXMATRIX* pMatrix);
	void GetTransform(D3DTRANSFORMSTATETYPE Type, D3DXMATRIX* pMatrix);
public:
	LPDIRECT3DDEVICE9 GetDevice();
	LPD3DXSPRITE GetSprite();
	LPD3DXFONT GetFont();
	LPD3DXLINE GetLine();
private:
	C_DirectX(void);
	C_DirectX(const C_DirectX&);
	C_DirectX& operator=(const C_DirectX);
public:
	~C_DirectX(void);
};

