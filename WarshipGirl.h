#pragma once
/*
TODO:
1.��������
2.����ս��
*/
#include "resource.h"


#define MAX_LOADSTRING 100
#define DT 10
// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������
HWND hWnd;
HDC hdc, mdc, bufdc;
HBITMAP buf;
int tPre, tNow;


//Direct3D objects  
LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPD3DXFONT fontDebugInfo,fontShipInfo,fontMsg;

bool gameover = false;

//macro to detect key presses  
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)  


ULONG_PTR m_gdiplusToken;
MyTimer *timer;
DataBase *db;
Scene *sceneNow,*sceneLast;
SceneDock *sceneDock;
SceneTroop *sceneTroops[4];
SceneBuildShip *sceneBuildShip;
SceneRepair *sceneRepair;
SceneRepairSelect *sceneRepairSelect;
SceneShipList *sceneShipList;

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void MyPaint(HDC hdc);
void Game_Run(HWND hwnd);
void Game_End(HWND hwnd);
MSG RunUntilTrue(bool *condition);
MSG RunUntilFalse(bool *condition);


