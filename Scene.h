#pragma once
#include <vector>
#include "Component.h"
#include "ComponentMsgBox.h"
#include "ITimerResponsable.h"
#include "d3dHdc.h"
#include <gdiplus.h>
using namespace std;
//*
class Scene;
class SceneDock;
class SceneShipList;
class SceneTroop;
class SceneBuildShip;
class SceneRepair;
class SceneRepairSelect;
class DataBase;
class MyTimer;
extern Scene *sceneNow,*sceneLast;
extern SceneDock *sceneDock;
extern SceneTroop *sceneTroops[4];
extern SceneBuildShip *sceneBuildShip;
extern SceneRepair *sceneRepair;
extern SceneRepairSelect *sceneRepairSelect;
extern MyTimer *timer;
extern DataBase *db;
extern HWND hWnd;
extern LPD3DXFONT fontDebugInfo, fontShipInfo, fontMsg;
//*/
const int W = 1024, H = 576;
void d3dDrawText(LPD3DXFONT font, LPCWSTR text, int x, int y, int cx, int cy,
	DWORD format, int a, int r, int g, int b);
MSG RunUntilTrue(bool *condition);
MSG RunUntilFalse(bool *condition);
class Scene : public ITimerResponsable, public IDispatchable
{
public:
	typedef enum State
	{
		Normal, MovingIn, MovingOut, NUL
	}State;
	typedef struct MB_STATE
	{
		bool clicked;
		bool ok;
	}MB_STATE;
public:
	Scene(std::wstring bgName);
	virtual ~Scene();
	virtual void StartPaint();
	virtual void DrawMovingComponents(bool movingIn);
	virtual void OnPaint();
	virtual void EndPaint();
	virtual void OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual void OnLButtonUp(WPARAM wParam, LPARAM lParam) {}
	virtual void OnMouseMove(WPARAM wParam, LPARAM lParam) {}
	virtual void OnTimer(int id);
	virtual void MoveIn(bool moveInEffect = true);
	virtual void MoveToOtherScene(Scene *other, bool moveOutEffect = true, bool moveInEffect = true);
	virtual void ShowText(std::wstring text, int time_ms);
	virtual void DrawNormalComponents();
	void InitOnClick();
	virtual void AddComponent(Component *com) override;
	void AddResourceBar(int dx = 0);
	void AddReturnBtn();
	virtual void SetComponent(Component *com, int i) override;
	virtual int GetDispatch(int x, int y) override { return onClickDecide[x][y]; }
	virtual void SetDispatch(int x, int y, int index) override { onClickDecide[x][y] = index; }
	void DelComponent(int i);
	void DelComponent(Component *com);
	void AddShade();
	void DelShade();
	bool SceneMessageBox(LPWSTR title, LPWSTR msg, int option, POINT pt = { (W - 530) / 2,(H - 314) / 2 });

	
protected:
	int onClickDecide[W][H];
	int timerIdShowText;
	int IN_FM;
	Bitmap *bg;
	d3dTexture *bgTexture;
	Scene *next;
	vector<Component *> components;
	std::wstring text, bgFileName;

	State state;
	int frame;
	int shadeCount;
};

void ComRightOptOnClick(Component *self, int x, int y, WPARAM wParam);

