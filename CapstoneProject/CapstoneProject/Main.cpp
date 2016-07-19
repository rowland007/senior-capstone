/************************************************************************
Program: CapstoneProject
Author: Randall D. Rowland Jr.
Class:
Instructor: Dan Randall
Date: 
Description:
Input:
Output:
Compilation instructions:
Usage:
Known bugs/missing features:

This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0
International Public License. To view a copy of this license, visit
https://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative
Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.

Modifications:
Date                Comment
----    ------------------------------------------------

************************************************************************/
#include <Windows.h>
#include "GameEngine.h"
#include "Resource.h"

GameEngine* g_pGame;

BOOL GameInitialize(HINSTANCE hInstance)
{
	//Create the game engine
	g_pGame = new GameEngine(hInstance, TEXT("Dungeon Warrior"), TEXT("Dungeon Warrior"), IDI_ICON1, IDI_ICON1);

	if (g_pGame == NULL)
		return FALSE;

	g_pGame->SetFrameRate(15);
	
	return TRUE;
}

void GameStart(HWND hWindow)
{
	//Seed random number generator
	srand(GetTickCount());
}

void GameEnd()
{
	//clean the system
	delete g_pGame;
}

void GameActivate(HWND hWindow)
{
	HDC		hDC;
	RECT	rect;

	//Draw activation text on screen
	GetClientRect(hWindow, &rect);
	hDC = GetDC(hWindow);

	DrawText(hDC, TEXT("TEST WINDOW - ACTIVE"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	ReleaseDC(hWindow, hDC);
}

void GameDeactivate(HWND hWindow)
{
	HDC		hDC;
	RECT	rect;

	//Draw deactivation text on screen
	GetClientRect(hWindow, &rect);
	hDC = GetDC(hWindow);

	DrawText(hDC, TEXT("TEST WINDOW - NOT ACTIVE"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	ReleaseDC(hWindow, hDC);
}

void GamePaint(HDC hDC)
{
	//empty
}

void GameCycle()
{
	HDC		hDC;
	HWND	hWindow = g_pGame->GetWindow();

	//Draw the screen
	hDC = GetDC(hWindow);

	//This will draw your icon on the screen randomly.  This is a test module and can be removed at a later date
	DrawIcon(hDC, rand() % g_pGame->GetWidth(), rand() % g_pGame->GetHeight(), (HICON)(WORD)GetClassLong(hWindow, GCL_HICON));

	//clean up
	ReleaseDC(hWindow, hDC);
}