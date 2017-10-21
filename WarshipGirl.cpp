// WarshipGirl.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "WarshipGirl.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow){
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WORSHIPGIRL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WORSHIPGIRL));

	MSG msg = RunUntilTrue(&gameover);
	Game_End(hWnd);
    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WORSHIPGIRL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
    wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm = NULL;

    return RegisterClassExW(&wcex);
}
//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   GdiplusStartupInput gdiplusStartupInput;
   GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

   hWnd = CreateWindowW(szWindowClass, szTitle,
	   WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX ,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   
   if (!hWnd)
   {
      return FALSE;
   }
   HWND desktop = GetDesktopWindow();
   HDC desktopDC = GetDC(desktop);
   int DW = GetDeviceCaps(desktopDC, HORZRES);
   int DH = GetDeviceCaps(desktopDC, VERTRES);

   MoveWindow(hWnd, (DW - W) / 2, (DH - H) / 2, W + 15, H + 40, TRUE);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   hdc = GetDC(hWnd);
   mdc = CreateCompatibleDC(hdc);
   bufdc = CreateCompatibleDC(hdc);
   buf = CreateCompatibleBitmap(hdc,W,H);

   //initialize Direct3D  
   d3d = Direct3DCreate9(D3D_SDK_VERSION);
   if (d3d == NULL)
   {
	   MessageBox(hWnd, L"Error initializing Direct3D", L"Error", MB_OK);
	   return 0;
   }


   D3DDISPLAYMODE d3ddm;
   if (d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm) != D3D_OK)
	   return 0;
   // set Direct3D presentation parameters
   D3DPRESENT_PARAMETERS d3dpp;
   ZeroMemory(&d3dpp, sizeof(d3dpp));
   d3dpp.Windowed = TRUE;
   d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
   d3dpp.BackBufferFormat = d3ddm.Format;
   d3dpp.BackBufferWidth = W;
   d3dpp.BackBufferHeight = H;
   d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
   d3dpp.EnableAutoDepthStencil = TRUE;
   d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
   d3dpp.hDeviceWindow = hWnd;

   //create Direct3D device  
   d3d->CreateDevice(
	   D3DADAPTER_DEFAULT,
	   D3DDEVTYPE_HAL,
	   hWnd,
	   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
	   &d3dpp,
	   &d3ddev);

   if (d3ddev == NULL)
   {
	   MessageBox(hWnd, L"Error creating Direct3D device", L"Error", MB_OK);
	   return 0;
   }
   D3DXCreateFont(d3ddev, 40, 13, 3, 1, FALSE, DEFAULT_CHARSET, 0, 0, 0, L"微软雅黑", &fontDebugInfo);
   D3DXCreateFont(d3ddev, 20, 7, 1, 1, FALSE, DEFAULT_CHARSET, 0, 0, 0, L"微软雅黑", &fontShipInfo);
   D3DXCreateFont(d3ddev, 30, 11, 2, 1, FALSE, DEFAULT_CHARSET, 0, 0, 0, L"微软雅黑", &fontMsg);

   timer = new MyTimer();
   db = new DataBase();

   sceneDock = new SceneDock(L"港区白天.jpg");
   sceneDock->MoveIn();
   for(int i = 0;i<4;i++)
		sceneTroops[i] = new SceneTroop(L"ship_bg.png",&(db->troops[i]));
   sceneBuildShip = new SceneBuildShip();
   sceneRepair = new SceneRepair();
   sceneRepairSelect = new SceneRepairSelect();
   sceneShipList = new SceneShipList();

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_LBUTTONDOWN:
		sceneNow->OnLButtonDown(wParam,lParam);
		break;
	case WM_LBUTTONUP:
		sceneNow->OnLButtonUp(wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		//int x = LOWORD(lParam);
		//int y = HIWORD(lParam);
		sceneNow->OnMouseMove(wParam, lParam);
		break;
	case WM_TIMER:
		sceneNow->OnTimer(wParam);
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            //PAINTSTRUCT ps;
            //HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            //EndPaint(hWnd, &ps);
        }
        break;
    case WM_CLOSE:
		gameover = sceneNow->SceneMessageBox(L"退出游戏", L"提督真的要回去了吗@_@", 0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
/************************************************************************/
/*  重绘界面的函数  */
/************************************************************************/
void MyPaint(HDC hdc)
{
	//timer->CheckTimers(tNow);
	//sceneNow->OnPaint(hdc);
	//tPre = GetTickCount();
}
/**
** Game update function
**/
void Game_Run(HWND hwnd)
{
	timer->CheckTimers();
	//make sure the Direct3D device is valid  
	if (!d3ddev) return;

	//clear the backbuffer
	d3dClear(D3DCOLOR_XRGB(0,0,255));

	//start rendering  
	if (d3ddev->BeginScene())
	{
		sceneNow->OnPaint();
		//stop rendering  
		d3ddev->EndScene();

		//copy back buffer on the screen  
		d3ddev->Present(NULL, NULL, NULL, NULL);
		//tPre = GetTickCount();
	}

}
void Game_End(HWND hwnd)
{
	DeleteDC(mdc);
	DeleteDC(bufdc);
	ReleaseDC(hWnd, hdc);
	PostQuitMessage(0);
	delete timer;
	delete db;
	delete sceneDock;
	GdiplusShutdown(m_gdiplusToken);
	//free memory  
	if (d3ddev) d3ddev->Release();
	if (d3d) d3d->Release();
}
MSG RunUntilTrue(bool *condition)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (!*condition && !gameover)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Game_Run(hWnd);
	}
	return msg;
}
MSG RunUntilFalse(bool *condition)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (*condition && !gameover)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Game_Run(hWnd);
	}
	return msg;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

