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
#include "Bitmap.h"

//Required global variables
const bool isTest = false;
bool isLoading;
HINSTANCE g_hInstance;
GameEngine *g_pGame;
Bitmap* g_pLoadScreen;
Bitmap* g_pLoadScreenText;

BOOL GameInitialize(HINSTANCE hInstance)
{
	//Create the game engine
	g_pGame = new GameEngine(hInstance, TEXT("Capstone Project"), TEXT("Dungeon Warrior"), IDI_ICON1, IDI_ICON1);

	if (g_pGame == NULL)
		return FALSE;

	g_pGame->SetFrameRate(15);
	g_hInstance = hInstance;
	
	return TRUE;
}

void GameStart(HWND hWindow)
{
	HDC hDC = GetDC(hWindow);
	isLoading = true;
	g_pLoadScreen = new Bitmap(hDC, IDB_BITMAP1, g_hInstance);
	g_pLoadScreenText = new Bitmap(hDC, IDB_BITMAP2, g_hInstance);
}

void GameEnd()
{
	//Deallocation of memory
	delete g_pLoadScreenText;
	g_pLoadScreenText = NULL;
	delete g_pLoadScreen;
	g_pLoadScreen = NULL;
	delete g_pGame;
	g_pGame = NULL;
}

void GameActivate(HWND hWindow)
{
	HDC		hDC;
	RECT	rect;

	
	GetClientRect(hWindow, &rect);
	hDC = GetDC(hWindow);
	
	ReleaseDC(hWindow, hDC);
}

void GameDeactivate(HWND hWindow)
{
	HDC		hDC;
	RECT	rect;

	GetClientRect(hWindow, &rect);
	hDC = GetDC(hWindow);
	
	ReleaseDC(hWindow, hDC);
}

void GamePaint(HDC hDC)
{
	if (isLoading)
	{
		g_pLoadScreen->Draw(hDC, 0, 0);
		g_pLoadScreenText->Draw(hDC, 120, 315, TRUE);
	}
	else
	{
		//g_pGame->DrawSprites(hDC); or something like that here
	}
}

void GameCycle()
{
	HDC		hDC;
	HWND	hWindow = g_pGame->GetWindow();

	
	hDC = GetDC(hWindow);

	ReleaseDC(hWindow, hDC);
}