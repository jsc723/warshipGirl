#pragma once
extern LPDIRECT3DDEVICE9 d3ddev;
class d3dHdc
{
private:
	HDC m_hdc;
	LPDIRECT3DSURFACE9 m_Surface;
public:
	void Release();
	inline operator HDC() { return m_hdc; }
public:
	d3dHdc();
	~d3dHdc();
};

const DWORD D3DFVF_TLVERTEX = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE |
	D3DFVF_SPECULAR | D3DFVF_TEX1);
typedef struct _D3DTLVERTEX
{
	float x, y, z, rhw;
	D3DCOLOR diffuse, specular;
	float tu, tv;
} D3DTLVERTEX;

class d3dTexture
{
public:
	int m_Width, m_Height;
	LPDIRECT3DTEXTURE9 m_Texture;
public:
	void BltFast(int x, int y);
	void BltFast(int x, int y, int cx, int cy, int a = 0, D3DCOLOR diffuse = -1);
	void BltFast(int x, int y, int cx, int cy, int a, D3DCOLOR diffuse,
		float srcU, float srcV, float srcCU, float srcCV);
public:
	//void Release() {  }
	inline operator LPDIRECT3DTEXTURE9() { return m_Texture; }
public:
	d3dTexture(LPCTSTR file, Bitmap *bitmap);
	~d3dTexture() {
		if (m_Texture) {
			m_Texture->Release();
			m_Texture = NULL;
		}
	};
};
void d3dClear(UINT color);
void d3dReadyPaintBG();
void d3dReadyPaintCom();
void d3dSetClip(int x, int y, int cx, int cy);
void d3dCancelClip();
void d3dDrawText(LPD3DXFONT font, LPCWSTR text, int x, int y, int cx, int cy,
	DWORD format, int a, int r, int g, int b);