#include "stdafx.h"

#include "3d.h"

LPDIRECT3D8 d3d;
LPDIRECT3DDEVICE8 d3ddev;

static IDirect3DVertexBuffer8 *v_buffer = nullptr;

HRESULT InitD3D(HWND hWnd)
{
	d3d = Direct3DCreate8(D3D_SDK_VERSION);
	if (d3d == nullptr)
		return -1;

	D3DDISPLAYMODE d3ddm;
	HRESULT hRes = d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = d3ddm.Format;

	HRESULT deviceResult = d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev
	);

	if (FAILED(deviceResult))
		return deviceResult;
	
	const GAMEVERTEX OurVertices[] =
	{
		{320.0f, 50.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255),},
		{520.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0),},
		{120.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0),},
	};
	if (FAILED(
		d3ddev->CreateVertexBuffer(sizeof(OurVertices), D3DUSAGE_WRITEONLY, GAMEFVF, D3DPOOL_MANAGED, &v_buffer
		)))
		return E_FAIL;

	BYTE* pVoid;
	if (FAILED(v_buffer->Lock(0, 0, &pVoid, 0)))
		return E_FAIL;
	memcpy(pVoid, OurVertices, sizeof(OurVertices));
	v_buffer->Unlock();

	return S_OK;
}

void RenderFrame()
{
	d3ddev->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

	d3ddev->BeginScene();

	{
		d3ddev->SetVertexShader(GAMEFVF);
		d3ddev->SetStreamSource(0, v_buffer, sizeof(GAMEVERTEX));
		d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
		d3ddev->SetStreamSource(0, nullptr, 0);
	}

	d3ddev->EndScene();

	d3ddev->Present(nullptr, nullptr, nullptr, nullptr);
}

void CleanD3D()
{
	v_buffer->Release();
	d3ddev->Release();
	d3d->Release();
}