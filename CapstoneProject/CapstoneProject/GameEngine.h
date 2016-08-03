/************************************************************************
Program:		CapstoneProject
Author:			Randall Rowland
Class:			GameEngine
Instructor:		Dan Randall
Date:			5 July 2016
Description:	GameEngine hides all the Windows specific code so you can
				focus on the game code.  Code is based from the book:
				"Beginning Game Programming" by Michael Morrison.
				No need to reinvent the wheel.
Input:
Output:

Compilation instructions:
Usage:
Known bugs/missing features:

Modifications:
Date                Comment
----    ------------------------------------------------
18Jul16	Added this comment block.
20Jul16 Added HandleKeys function for keyboard support.
2Aug16	Changed BOOL to bool, TRUE to true, and FALSE to false.
3Aug16	Moved implementation of general and accessor methods to GameEngine.cpp
************************************************************************/
#pragma once
#include <windows.h>

//-----------------------------------------------------------------
// Windows Function Declarations
//-----------------------------------------------------------------
int		WINAPI    WinMain(HINSTANCE, HINSTANCE, PSTR, int);
LRESULT CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);
//-----------------------------------------------------------------
// Game Engine Function Declarations
//-----------------------------------------------------------------
bool GameInitialize(HINSTANCE);
void GameStart(HWND);
void GameEnd();
void GameActivate(HWND);
void GameDeactivate(HWND);
void GamePaint(HDC);
void GameCycle();
void HandleKeys(WPARAM);

//-----------------------------------------------------------------
// GameEngine Class
//-----------------------------------------------------------------
class GameEngine
{
protected:
	// Member Variables
	static GameEngine*  m_pGameEngine;
	HINSTANCE           m_hInstance;
	HWND                m_hWindow;
	TCHAR               m_szWindowClass[32];
	TCHAR               m_szTitle[32];
	WORD                m_wIcon, m_wSmallIcon;
	int                 m_iWidth, m_iHeight;
	int                 m_iFrameDelay;
	bool                m_bSleep;

public:
	// Constructor(s)/Destructor
	GameEngine(HINSTANCE, LPTSTR, LPTSTR, WORD, WORD, int, int);
	virtual ~GameEngine();

	// General Methods
	static GameEngine*  GetEngine();
	bool                Initialize(int);
	LRESULT             HandleEvent(HWND, UINT, WPARAM, LPARAM);

	// Accessor Methods
	HINSTANCE GetInstance() const;
	HWND      GetWindow() const;
	void      SetWindow(HWND);
	LPTSTR    GetTitle();
	WORD      GetIcon() const;
	WORD      GetSmallIcon() const;
	int       GetWidth() const;
	int       GetHeight() const;
	int       GetFrameDelay() const;
	void      SetFrameRate(int);
	bool      GetSleep() const;
	void      SetSleep(bool );
};