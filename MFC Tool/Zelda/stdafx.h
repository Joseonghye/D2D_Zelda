// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

#include <string>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#include "d3d9.h"
#include "d3dx9.h"
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "Include.h"

#include "TextureMgr.h"
#include "GameObjectMgr.h"
#include "GraphicDevice.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ScrollMgr.h"

#define TEXTUREMGR		CTextureMgr::GetInstance()
#define GAMEOBJECTMGR	CGameObjectMgr::GetInstance()
#define GRAPHICDEVICE	CGraphicDevice::GetInstance()
#define SCENEMGR		CSceneMgr::GetInstance()
#define KEYMGR			CKeyMgr::GetInstance()
#define TIMEMGR			CTimeMgr::GetInstance()
#define SCROLLMGR		CScrollMgr::GetInstance()