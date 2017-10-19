#include "stdafx.h"
#include "d3dHdc.h"

d3dHdc::d3dHdc()
{
	m_hdc = 0;
	m_Surface = 0;
	if (!d3ddev) return;
	if (d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_Surface) != D3D_OK) return;
	m_Surface->GetDC(&m_hdc);
}
d3dHdc::~d3dHdc()
{
}
void d3dHdc::Release()
{
	if (!m_Surface || !m_hdc) return;
	m_Surface->ReleaseDC(m_hdc);
	m_Surface->Release();
	m_hdc = NULL;
	m_Surface = NULL;
}
void d3dTexture::BltFast(int x, int y)
{
	BltFast(x, y, m_Width, m_Height);
}
void d3dTexture::BltFast(int x, int y, int cx, int cy, int a, D3DCOLOR diffuse)
{
	BltFast(x, y, cx, cy, a, diffuse,
		0.0f, 0.0f, 1.0f, 1.0f);
}
void d3dTexture::BltFast(int x, int y, int cx, int cy, int a, D3DCOLOR diffuse, 
	float srcU, float srcV, float srcCU, float srcCV)
{
	int left = x, right = x + cx, top = y, bottom = y + cy;
	D3DTLVERTEX v[4]; //顶点的结构
	ZeroMemory(v, sizeof(v));
	if (a == 0.0f) {
		v[0].x = v[3].x = (float)left;
		v[1].x = v[2].x = (float)right;
		v[0].y = v[1].y = (float)top;
		v[2].y = v[3].y = (float)bottom;
	} else {
		float ox, oy;
		float in, s, c;
		in = a *3.1415926f / 180.0f;
		ox = (float)(right + left) / 2;
		oy = (float)(bottom + top) / 2;
		left -= (int)ox;
		top -= (int)oy;
		right -= (int)ox;
		bottom -= (int)oy;
		s = sinf(in);
		c = cosf(in);
		v[0].x = c * left + s*top + ox;
		v[0].y = -s * left + c*top + oy;
		v[1].x = c*right + s*top + ox;
		v[1].y = -s*right + c*top + oy;
		v[2].x = c*right + s*bottom + ox;
		v[2].y = -s*right + c*bottom + oy;
		v[3].x = c*left + s*bottom + ox;
		v[3].y = -s*left + c*bottom + oy;
	}
	for (int i = 0; i < 4; i++) {
		v[i].rhw = v[i].z = 0.5f;
		v[i].diffuse = diffuse;
	}
	v[0].tu = srcU; v[0].tv = srcV;
	v[1].tu = v[2].tu = srcU + srcCU;
	v[2].tv = v[3].tv = srcV + srcCV;

	d3ddev->SetTexture(0, m_Texture);
	d3ddev->SetFVF(D3DFVF_TLVERTEX);
	d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	d3ddev->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2,
		(LPVOID)v, sizeof(D3DTLVERTEX));
	
}


d3dTexture::d3dTexture(LPCTSTR file,Bitmap *bitmap)
{
	D3DXIMAGE_INFO in;
	ZeroMemory(&in, sizeof(in));
	//Release();
	D3DXCreateTextureFromFileEx(d3ddev, file,
		D3DX_DEFAULT, D3DX_DEFAULT,
		0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		0, &in, NULL, &m_Texture);
	m_Width = in.Width;
	m_Height = in.Height;
}


void d3dClear(UINT color)
{
	d3ddev->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0);
}

void d3dReadyPaintBG()
{
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	d3ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	d3ddev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void d3dReadyPaintCom()
{
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	d3ddev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	d3ddev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	d3ddev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	d3ddev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	d3ddev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	d3ddev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
}

void d3dSetClip(int x, int y, int cx, int cy)
{
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + cx;
	rect.bottom = y + cy;
	d3ddev->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	d3ddev->SetScissorRect(&rect);
}

void d3dCancelClip()
{
	d3ddev->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
}

void d3dDrawText(LPD3DXFONT font, LPCWSTR text, int x,int y ,int cx, int cy
	, DWORD format, int a, int r, int g, int b)
{
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + cx;
	rect.bottom = y + cy;
	font->DrawTextW(NULL, text, -1, &rect, format, D3DCOLOR_ARGB(a, r, g, b));
}
