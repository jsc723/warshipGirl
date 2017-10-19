#include "stdafx.h"
#include "Component.h"

void DefaultComponentOnClick(Component *self, int x ,int y, WPARAM wParam)
{
	wchar_t message[30];
	wsprintf(message, L"(%d,%d) clicked!",x,y);
	self->scene->ShowText(message, 1000);
}
Component::Component()
{
	imgFileName = L"";
	this->img = NULL;
	InitHelp(0,0,0,0,0);
}
Component::Component(wstring imgName, int x, int y, LPARAM lParam)
{
	imgFileName = imgName;
	this->img = db->getBitmap(imgName);
	InitHelp(x,y, img->GetWidth(),img->GetHeight(),lParam);
}

Component::Component(wstring imgName, int x, int y, float r, LPARAM lParam) 
{
	imgFileName = imgName;
	this->img = db->getBitmap(imgName);
	InitHelp(x, y, (int)(img->GetWidth() * r), (int)(img->GetHeight() * r), lParam);
}

Component::Component(wstring imgName, int x, int y, int cx, int cy, LPARAM lParam)
{
	imgFileName = imgName;
	this->img = db->getBitmap(imgName);
	InitHelp(x,y,cx,cy,lParam);
}

void Component::InitHelp(int x, int y, int cx, int cy, LPARAM lp)
{
	this->x = x;
	this->y = y;
	this->cx = cx;
	this->cy = cy;
	this->lParam = lp;
	scene = NULL;
	imgTexture = NULL;
	angle = 0;
	diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	ZeroMemory(&changeBhv, sizeof(changeBhv));
	InstallOnClick(DefaultComponentOnClick);
}


Component::~Component()
{
	EndPaint();
	for (size_t i = 0; i < labels.size(); i++) {
		delete labels[i];
	}
}

void Component::SetChangingSceneBehaivor(int dx, int dy)
{
	SetChangingSceneBehaivor(dx, dy, 0, 0);
}

void Component::SetChangingSceneBehaivor(int dx, int dy, int dw, int dh)
{
	changeBhv.show = true;
	changeBhv.dx = dx;
	changeBhv.dy = dy;
	changeBhv.dw = dw;
	changeBhv.dh = dh;
}

void Component::AddToScene(Scene * scene, int id)
{
	this->scene = scene;
	if (img == NULL)
		return;
	int w = img->GetWidth(), h = img->GetHeight();
	for (int i = x; i < x + cx; i++) {
		for (int j = y; j < y + cy; j++) {
			if (i >= 0 && i < W && j >= 0 && j < H) {
				Color clr;
				img->GetPixel((i - x) * w / cx, (j - y) * h / cy, &clr);
				if (clr.GetA() > 0) //如果不透明，则视作按钮部分，可以接受消息
					scene->onClickDecide[i][j] = id;
			}
		}
	}
}

void Component::AddLabel(Label * label)
{
	labels.push_back(label);
}

void Component::StartPaint()
{
	if (imgTexture) return;
	imgTexture = new d3dTexture(db->pathList[imgFileName.c_str()].c_str(),
		db->getBitmap(imgFileName));
}

void Component::EndPaint()
{
	if (imgTexture) {
		delete imgTexture;
		imgTexture = NULL;
	}
}

void Component::OnPaintMoving(double r) 
{
	if(changeBhv.show)
		OnPaint((int)(changeBhv.dx * r), 
				(int)(changeBhv.dy * r),
				cx + (int)(changeBhv.dw * r), 
				cy + (int)(changeBhv.dh * r));
}

void Component::OnPaint()
{
	OnPaint(0, 0, cx, cy, angle, diffuse);
}

void Component::OnPaint(int dx, int dy)
{
	OnPaint(dx, dy, cx, cy, angle, diffuse);
}


void Component::OnPaint(int dx, int dy, int w, int h)
{
	OnPaint(dx, dy, w, h, angle, diffuse);
}
void Component::OnPaint(int dx, int dy, int w, int h, int a, D3DCOLOR diffuse)
{
	if (imgTexture == NULL) return;
	imgTexture->BltFast(x + dx, y + dy, w, h, a, diffuse);
	for (size_t i = 0; i < labels.size(); i++) {
		labels[i]->OnPaint(dx, dy);
	}
}

