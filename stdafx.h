// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


//  在此处引用程序需要的其他头文件
#include <comdef.h>//初始化一下com口  
#include "GdiPlus.h"  
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")  
#include <mmsystem.h> //导入声音头文件库   
#pragma comment(lib,"winmm.lib")//导入声音的链接库  
#include <d3d9.h>
#include <C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3dx9tex.h>
#pragma comment(lib,"d3d9.lib")  
#pragma comment(lib,"C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dx9.lib")
#include "DataBase.h"
#include "Scene.h"
#include "SceneDock.h"
#include "SceneTroop.h"
#include "SceneBuildShip.h"
#include "SceneRepair.h"
#include "SceneRepairSelect.h"
#include "SceneShipList.h"
#include "Component.h"
#include "Label.h"
#include "LabelInt.h"
#include "LabelStr.h"
#include "MyTimer.h"
#include "d3dHdc.h"


