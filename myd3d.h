#pragma once
#include <Windows.h>
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")  
#pragma comment(lib,"C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dx9.lib")


//Direct3D objects  
LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;

void d3dClear(UINT color);
void d3dRelease();