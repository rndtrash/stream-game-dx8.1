#pragma once

#include <windows.h>
#include <d3d8.h>

#define GAMEFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

struct GAMEVERTEX
{
    FLOAT x, y, z, rhw;	// from the D3DFVF_XYZRHW flag
    DWORD color;		// from the D3DFVF_DIFFUSE flag
};

extern LPDIRECT3D8 d3d;								// the pointer to our Direct3D interface
extern LPDIRECT3DDEVICE8 d3ddev;						// the pointer to the device class

HRESULT	InitD3D(HWND hWnd);
void	RenderFrame();
void	CleanD3D();