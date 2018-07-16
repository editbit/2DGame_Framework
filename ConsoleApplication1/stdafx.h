//============================================================= //	##  Eng
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "msimg32.lib")

#include <SDKDDKVer.h>


#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ 런타임 헤더 파일입니다.
#include <iostream>
// 자주사용하는 STL
#include <string>
#include <vector>
#include <map>
#include <WinSock2.h>
#include <Ws2tcpip.h>

using namespace std;

//=============================================================
//	## 싱글톤을 추가한다 ##
//=============================================================
#define KEYMANAGER KeyManager::getSingleton()
#define RND RandomFunction::getSingleton()
#define MYSOCKET NetworkManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()

//=============================================================
//	## 디파인문 ## (윈도우창 초기화)
//=============================================================
#define WINNAME (LPTSTR)(TEXT(" 김상균 - Titan Souls "))
#define WINSTARTX	200
#define WINSTARTY	5
#define WINSIZEX		1000
#define WINSIZEY		800
#define WINSTYLE		WS_CAPTION | WS_SYSMENU



//=============================================================
//	## 상수 ##
//=============================================================
#define PI 3.141592f

enum RECT_TYPE
{
	ATTACK_RECT, HITBOX_RECT, BODY_RECT
};

enum { APPEAR = 1, FIGHT_DELAY, FIGHT = 4, DEAD_DELAY = 7 };

enum DIRECTION
{
	RIGHT, UP, LEFT, DOWN, RIGHT_DOWN, LEFT_DOWN, LEFT_UP, RIGHT_UP, NONE
};

enum STATE
{
	IDLE, WALK, RUN, ROLL, ATTACK, COLLECT, DEAD = 6, COLLECT_SOUL = 7, STOP = 10,
};


//=============================================================
//	## 내가 만든 헤더파일을 이곳에 추가한다 ##
//=============================================================
#include "commonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "Image.h"
#include "ImageManager.h"
#include "GameNode.h"
#include "SceneManager.h"
#include "NetworkManager.h"

//=============================================================
//	## 매크로함수 ## (클래스에서 동적할당된 부분 해제)
//=============================================================
#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//=============================================================
//	## 전역변수 ##
//=============================================================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;

