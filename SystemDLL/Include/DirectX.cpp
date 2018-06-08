#include "DirectX.h"

IMPLEMENT_SINGLETONE_SYSDLL(C_DirectX);

C_DirectX::C_DirectX(void) :m_pD3D9(NULL), m_pDevice(NULL),
m_pSprite(NULL), m_pFont(NULL), m_pLine(NULL)
{
}


C_DirectX::~C_DirectX(void)
{
}

HRESULT C_DirectX::InitDevice(HWND hWnd, int nSizeX, int nSizeY, bool bWinMode)
{
	m_pD3D9=Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 d3dcap;

	if (FAILED(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&d3dcap)))
	{
		return E_FAIL;
	}

	DWORD dwFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING|D3DCREATE_MULTITHREADED;

	if (d3dcap.DevCaps&D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		dwFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth = nSizeX;
	d3dpp.BackBufferHeight = nSizeY;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
//	d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = TRUE;
	
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = bWinMode;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, dwFlag, &d3dpp, &m_pDevice)))
	{
		MSGBOX_OK(L"Device Error");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		MSGBOX_OK(L"SpriteError");
		return E_FAIL;
	}

	D3DXFONT_DESC FontDesc;
	ZeroMemory(&FontDesc, sizeof(D3DXFONT_DESC));

	FontDesc.Height = 20;
	FontDesc.Width = 10;
	FontDesc.Weight = FW_HEAVY;
	FontDesc.CharSet = DEFAULT_CHARSET;
	lstrcpy(FontDesc.FaceName, L"DefalutFace");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &FontDesc, &m_pFont)))
	{
		MSGBOX_OK(L"Font Error");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		MSGBOX_OK(L"Line Error");
		return E_FAIL;
	}

	return S_OK;
}

void C_DirectX::Release()
{
	if (m_pLine)
	{
		m_pLine->Release();
		m_pLine = NULL;
	}
	if (m_pFont)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
	if (m_pSprite)
	{
		m_pSprite->Release();
		m_pSprite = NULL;
	}
	if (m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	if (m_pD3D9)
	{
		m_pD3D9->Release();
		m_pD3D9 = NULL;
	}
}

void C_DirectX::Begin_Render()
{
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(255, 0, 0, 255), 1.0f, 0);
	m_pDevice->BeginScene();
	
}

void C_DirectX::End_Render()
{
	
	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}

void C_DirectX::DrawFont(RECT rcFont, const TCHAR* pFont, DWORD dwFlag, DWORD dwColor)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pFont->DrawTextW(m_pSprite, pFont, lstrlen(pFont), &rcFont, dwFlag, dwColor);
	m_pSprite->End();
	
}

void C_DirectX::SetRenderState(_D3DRENDERSTATETYPE Type, DWORD dwFlag)
{
	m_pDevice->SetRenderState(Type, dwFlag);
}

void C_DirectX::SetTransformState(_D3DTRANSFORMSTATETYPE Type, const D3DXMATRIX* pMatrix)
{
	m_pDevice->SetTransform(Type, pMatrix);
}

LPDIRECT3DDEVICE9 C_DirectX::GetDevice()
{
	return m_pDevice;
}

LPD3DXSPRITE C_DirectX::GetSprite()
{
	return m_pSprite;
}

LPD3DXFONT C_DirectX::GetFont()
{
	return m_pFont;
}

LPD3DXLINE C_DirectX::GetLine()
{
	return m_pLine;
}

void C_DirectX::GetTransform(D3DTRANSFORMSTATETYPE Type, D3DXMATRIX* pMatrix)
{
	m_pDevice->GetTransform(Type, pMatrix);
}
