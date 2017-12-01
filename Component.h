#pragma once
#include "Scene.h"
#include "Label.h"
class Scene;
class d3dTexture;
class Component
{
public:
	struct ChangingSceneBehaivor {
		bool show;
		int dx, dy;
		int dw, dh;
	};
	static const int LP_SHADE = -1234;
	Component();
	Component(wstring imgName, int x, int y, LPARAM lParam);
	Component(wstring imgName, int x, int y, float r, LPARAM lParam);
	Component(wstring imgName, int x, int y, int cx, int cy, LPARAM lParam);
	virtual ~Component();
	void InstallOnClick(void(*onclick)(Component *self,int x,int y, WPARAM wParam)) { OnClick = onclick; }
	void SetChangingSceneBehaivor(int dx, int dy);
	void SetChangingSceneBehaivor(int dx, int dy, int dw, int dh);
	virtual void AddToScene(Scene * scene, int id);
	virtual void AddLabel(Label *label);
	virtual void StartPaint();
	virtual void EndPaint();
	void OnPaint();
	virtual void OnPaintMoving(double r);
	void OnPaint(int dx, int dy);
	void OnPaint(int dx, int dy, int w, int h);
	virtual void OnPaint(int dx, int dy, int w, int h, int a, D3DCOLOR diffuse);
	Scene *scene;
	int angle;
	D3DCOLOR diffuse;
	Bitmap *img;
	d3dTexture *imgTexture;
	wstring imgFileName;
	int x, y, cx ,cy;
	LPARAM lParam;
	vector<Label *> labels;
	ChangingSceneBehaivor changeBhv;
	
	void(*OnClick)(Component *self, int x, int y, WPARAM wParam);
protected:
	void InitHelp(int x,int y,int cx,int cy,LPARAM lp);
};

