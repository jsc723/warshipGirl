// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


//  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <comdef.h>//��ʼ��һ��com��  
#include "GdiPlus.h"  
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")  
#include <mmsystem.h> //��������ͷ�ļ���   
#pragma comment(lib,"winmm.lib")//�������������ӿ�  
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


