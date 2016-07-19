/************************************************************************
Program:		CapstoneProject
Author:			Randall D. Rowland Jr.
Class:			
Instructor:		Dan Randall
Date:			18 July 2016
Description:	This file creates the window in using the GameEngine class
				and loads the program's icon.
Input:			
Output:			A window with an icon and text in the title bar.

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
18Jul16	Added a bool var to put program in a test mode.
************************************************************************/
#include <Windows.h>
#include "GameEngine.h"
#include "Resource.h"

//Required global variables
bool isTest = true;
GameEngine *g_pGame;

BOOL GameInitialize(HINSTANCE hInstance)
{
	//Create the game engine
	g_pGame = new GameEngine(hInstance, TEXT("Capstone Project"), TEXT("Dungeon Warrior"), IDI_ICON1, IDI_ICON1);

	if (g_pGame == NULL)
		return FALSE;

	g_pGame->SetFrameRate(15);
	
	return TRUE;
}

void GameStart(HWND hWindow)
{
	if (isTest)
	{
		//Seed random number generator
		srand(GetTickCount());
	}
}

void GameEnd()
{
	//Deallocation of memory
	delete g_pGame;
	g_pGame = NULL;
}

void GameActivate(HWND hWindow)
{
	HDC		hDC;
	RECT	rect;

	
	GetClientRect(hWindow, &rect);
	hDC = GetDC(hWindow);

	if (isTest)
	{
		//Draw activation text on screen
		DrawText(hDC, TEXT("TEST WINDOW - ACTIVE NOW"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	
	ReleaseDC(hWindow, hDC);
}

void GameDeactivate(HWND hWindow)
{
	HDC		hDC;
	RECT	rect;

	GetClientRect(hWindow, &rect);
	hDC = GetDC(hWindow);

	if (isTest)
	{
		//Draw deactivation text on screen
		DrawText(hDC, TEXT("TEST WINDOW - NOT ACTIVE"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	
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

	
	hDC = GetDC(hWindow);
	if (isTest)
	{
		//This will draw your icon on the screen randomly.  This is a test module and can be removed at a later date
		DrawIcon(hDC, rand() % g_pGame->GetWidth(), rand() % g_pGame->GetHeight(), (HICON)(WORD)GetClassLong(hWindow, GCL_HICON));
	}

	ReleaseDC(hWindow, hDC);
}