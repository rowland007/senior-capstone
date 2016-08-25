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
20Jul16 Added keyboard support with HandleKeys function.
22Jul16	Modified HandleKeys to a switch/case.
3Aug16	Set screen size in GameEngine constructor parameters
18Aug16	Added offscreen device for double buffering and sprite collision detection
23Aug16	Removed '#include "Bitmap.h"' - Was causing redefinition errors
24Aug16	Added Construct.h and Dungeon.h
************************************************************************/
#include <Windows.h>
#include <Wingdi.h>
#include "GameEngine.h"
#include "Resource.h"
#include "Sprite.h"
#include "Construct.h"
#include "Dungeon.h"

//Required global variables
const bool			isTest = true;
bool				isLoading;
HINSTANCE			g_hInstance;
GameEngine			*g_pGame;
bool	            g_bGameOver;
int					g_iGameOverDelay;
HDC					g_hOffscreenDC;
HBITMAP				g_hOffscreenBitmap;

//Load resources into memory
Bitmap* g_pLoadScreen;
Bitmap* g_pLoadScreenText;

bool GameInitialize(HINSTANCE hInstance)
{
	//Create the game engine
	g_pGame = new GameEngine(hInstance, TEXT("Capstone Project"), TEXT("Dungeon Warrior"), IDI_ICON1, IDI_ICON1, 800, 600);

	if (g_pGame == NULL)
		return false;

	g_pGame->SetFrameRate(15);
	g_hInstance = hInstance;
	
	return true;
}

void GameStart(HWND hWindow)
{
	  // Create the offscreen device context and bitmap
  	g_hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
  	g_hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow), g_pGame->GetWidth(), g_pGame->GetHeight());
  	SelectObject(g_hOffscreenDC, g_hOffscreenBitmap);

	isLoading = true;
	g_pLoadScreen = new Bitmap(GetDC(hWindow), IDB_BITMAP1, g_hInstance);
	g_pLoadScreenText = new Bitmap(GetDC(hWindow), IDB_BITMAP2, g_hInstance);
}

void GameEnd()
{
  	// Cleanup the offscreen device context and bitmap
  	DeleteObject(g_hOffscreenBitmap);
  	DeleteDC(g_hOffscreenDC); 

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
		g_pLoadScreenText->Draw(hDC, 75, 50, true);
		TextOut(hDC, 150, 500, TEXT("START"), 5);
		TextOut(hDC, 300, 500, TEXT("SETTINGS"), 8);
		TextOut(hDC, 450, 500, TEXT("QUIT"), 4);

	}
	else
	{
		//g_pGame->DrawSprites(hDC); or something like that here
	}
}

void GameCycle()
{
  	if (!g_bGameOver)
  	{
 
    	// Update the sprites
    	g_pGame->UpdateSprites();

    	// Obtain a device context for repainting the game
    	HWND  hWindow = g_pGame->GetWindow();
    	HDC   hDC = GetDC(hWindow);

    	// Paint the game to the offscreen device context
    	GamePaint(g_hOffscreenDC);

    	// Blit the offscreen bitmap to the game screen
    	BitBlt(hDC, 0, 0, g_pGame->GetWidth(), g_pGame->GetHeight(), g_hOffscreenDC, 0, 0, SRCCOPY);

    	// Cleanup
    	ReleaseDC(hWindow, hDC);
  	}
  	else
    	if (--g_iGameOverDelay == 0)
    	{
     	//Switch back to the LoadingScreen
      	isLoading = true;
      	//NewGame();
    	}
}

void HandleKeys(WPARAM wParam)
{
	//HandleKeys knows when a key is pressed but does not know if a key is being held.
	//Even if a key is being held, when a new key is pressed it will see that key press.
	//TODO: Implement if key is being held.
	HDC		hDC;
	HWND	hWindow = g_pGame->GetWindow();
	hDC = GetDC(hWindow);

	switch (wParam)
	{
	case VK_LEFT:
		if (isTest)
		{
			GamePaint(hDC);
			TextOut(hDC, 1100, 990, TEXT("LEFT KEY"), 9);
		}
		break;
	case VK_RIGHT:
		if (isTest)
		{
			GamePaint(hDC);
			TextOut(hDC, 1100, 990, TEXT("RIGHT KEY"), 10);
		}
		break;
	case VK_UP:
		if (isTest)
		{
			GamePaint(hDC);
			TextOut(hDC, 1100, 990, TEXT("UP KEY"), 6);
		}
		break;
	case VK_DOWN:
		if (isTest)
		{
			GamePaint(hDC);
			TextOut(hDC, 1100, 990, TEXT("DOWN KEY"), 9);
		}
		break;
	case VK_SPACE:
		if (isLoading)
		{
			isLoading = false;
		}
		if (isTest)
		{
			GamePaint(hDC);
			TextOut(hDC, 1100, 990, TEXT("BOOM-BOOM KEY"), 14);
		}
		break;
	case VK_RETURN:
		isLoading = false;
		break;
	default:
		GamePaint(hDC);
		break;
	}
	ReleaseDC(hWindow, hDC);
}
bool SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee)
{
  	// See if a player missile and an alien have collided
  	Bitmap* pHitter = pSpriteHitter->GetBitmap();
  	Bitmap* pHittee = pSpriteHittee->GetBitmap();

	/**********************The Following is an example of what happens here

  	if ((pHitter == g_pMissileBitmap && (pHittee == g_pBlobboBitmap || pHittee == g_pJellyBitmap || pHittee == g_pTimmyBitmap)) || 
	  			(pHittee == g_pMissileBitmap && (pHitter == g_pBlobboBitmap || pHitter == g_pJellyBitmap || pHitter == g_pTimmyBitmap)))
  	{
    	// Play the small explosion sound
    	PlaySound((LPCSTR)IDW_LGEXPLODE, g_hInstance, SND_ASYNC | SND_RESOURCE);

	    // Kill both sprites
	    pSpriteHitter->Kill();
	    pSpriteHittee->Kill();

    	// Create a large explosion sprite at the alien's position
    	RECT rcBounds = { 0, 0, 600, 450 };
    	RECT rcPos;
    	if (pHitter == g_pMissileBitmap)
      		rcPos = pSpriteHittee->GetPosition();
    	else
      		rcPos = pSpriteHitter->GetPosition();
    
		Sprite* pSprite = new Sprite(g_pLgExplosionBitmap, rcBounds);
    	pSprite->SetNumFrames(8, TRUE);
    	pSprite->SetPosition(rcPos.left, rcPos.top);
    	g_pGame->AddSprite(pSprite);
 	}

	// See if an alien missile has collided with the car
  	if ((pHitter == g_pCarBitmap && (pHittee == g_pBMissileBitmap || pHittee == g_pJMissileBitmap || pHittee == g_pTMissileBitmap)) ||
    		(pHittee == g_pCarBitmap && (pHitter == g_pBMissileBitmap || pHitter == g_pJMissileBitmap || pHitter == g_pTMissileBitmap)))
  	{
    	// Play the large explosion sound
    	PlaySound((LPCSTR)IDW_LGEXPLODE, g_hInstance, SND_ASYNC | SND_RESOURCE);

    	// Kill the missile sprite
    	if (pHitter == g_pCarBitmap)
      		pSpriteHittee->Kill();
    	else
      		pSpriteHitter->Kill();

    	// Create a large explosion sprite at the car's position
    	RECT rcBounds = { 0, 0, 600, 480 };
    	RECT rcPos;
    	if (pHitter == g_pCarBitmap)
      		rcPos = pSpriteHitter->GetPosition();
    	else
      		rcPos = pSpriteHittee->GetPosition();
    	
		Sprite* pSprite = new Sprite(g_pLgExplosionBitmap, rcBounds);
    	pSprite->SetNumFrames(8, TRUE);
    	pSprite->SetPosition(rcPos.left, rcPos.top);
    	g_pGame->AddSprite(pSprite);

    	// Move the car back to the start
    	g_pCarSprite->SetPosition(300, 405);

    	// See if the game is over
    	if (--g_iNumLives == 0)
    	{
      		// Play the game over sound
      		PlaySound((LPCSTR)IDW_GAMEOVER, g_hInstance, SND_ASYNC | SND_RESOURCE);
      		g_bGameOver = TRUE;
      		g_iGameOverDelay = 150;

    	}
  	}

	******************End of Example******************/

  	return false;
}

void SpriteDying(Sprite* pSpriteDying)
{
	/******************The Following is an example of what would happen here

  	// See if an alien missile sprite is dying
  	if (pSpriteDying->GetBitmap() == g_pBMissileBitmap || pSpriteDying->GetBitmap() == g_pJMissileBitmap || pSpriteDying->GetBitmap() == g_pTMissileBitmap)
  	{
    	// Play the small explosion sound
      	PlaySound((LPCSTR)IDW_SMEXPLODE, g_hInstance, SND_ASYNC | SND_RESOURCE | SND_NOSTOP);

    	// Create a small explosion sprite at the missile's position
    	RECT rcBounds = { 0, 0, 600, 450 };
    	RECT rcPos = pSpriteDying->GetPosition();
    	Sprite* pSprite = new Sprite(g_pSmExplosionBitmap, rcBounds);
    	pSprite->SetNumFrames(8, TRUE);
    	pSprite->SetPosition(rcPos.left, rcPos.top);
    	g_pGame->AddSprite(pSprite);
  	}

	*******************End of Example*****************************************/
}

//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------
void NewGame()
{
  	// Clear the sprites
  	g_pGame->CleanupSprites();

  	// Initialize the game variables
  	g_bGameOver = false;

  	if (isLoading)
  	{
    	// Add 
  	}
  	else
  	{
    	// Create 
    	// Play the background music
    	//g_pGame->PlayMIDISong(TEXT(""));
  	}
}