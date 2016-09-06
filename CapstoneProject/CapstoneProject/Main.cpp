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
25Aug16 Added Start/Settings/Quit text and SelectorSprite
************************************************************************/
#include <Windows.h>
#include <Wingdi.h>
#include "GameEngine.h"
#include "Resource.h"
#include "Sprite.h"
#include "Construct.h"
#include "Dungeon.h"

//Required global variables
bool				isTest = false;
bool				isSettings = false;
bool				isConstruct;
bool				isDungeon;
bool				isLoading;
HINSTANCE			g_hInstance;
GameEngine			*g_pGame;
bool	            g_bGameOver;
int					g_iGameOverDelay;
HDC					g_hOffscreenDC;
HBITMAP				g_hOffscreenBitmap;
RECT				g_rcFullWindow;
static RECT			g_rcLeft;
static RECT			g_rcMiddle;
static RECT			g_rcRight;

//Load Bitmaps into memory
Bitmap* g_pLoadScreen;
Bitmap* g_pLoadScreenText;
Bitmap* g_pLoadScreenSelectorBitmap;
Bitmap* g_pDialogBox;
Bitmap* g_pConstructFloor;
Bitmap* g_pDungeonFloor;
Bitmap* g_pHeroBitmap;
Bitmap* g_pConstructUpperWallBitmap;
Bitmap* g_pConstructLowerWallBitmap;
Bitmap* g_pConstructRightWallBitmap;
Bitmap* g_pConstructLeftWallBitmap;
Bitmap* g_pConstructTopRightBitmap;
Bitmap* g_pConstructTopLeftBitmap;
Bitmap* g_pConstructBottomRightBitmap;
Bitmap* g_pConstructBottomLeftBitmap;
Bitmap* g_pConstructShelvesBitmap;
Bitmap* g_pConstructRightWindowBitmap;
Bitmap* g_pConstructLeftWindowBitmap;
Bitmap* g_pConstructTopWindowBitmap;
Bitmap* g_pConstructBottomWindowBitmap;
Bitmap* g_pConstructFireplaceBitmap;


//Load Sprites into memory
Sprite* g_pLoadScreenSelectorSprite;
Sprite* g_pConstructUpperWallSprite[52];
Sprite* g_pConstructLowerWallSprite[52];
Sprite* g_pConstructRightWallSprite[34];
Sprite* g_pConstructLeftWallSprite[34];
Sprite* g_pConstructTopRightSprite;
Sprite* g_pConstructTopLeftSprite;
Sprite* g_pConstructBottomRightSprite;
Sprite* g_pConstructBottomLeftSprite;
Sprite* g_pConstructShelvesSprite;
Sprite* g_pConstructRightWindowSprite;
Sprite* g_pConstructLeftWindowSprite;
Sprite* g_pConstructTopWindowSprite;
Sprite* g_pConstructBottomWindowSprite;
Sprite* g_pConstructFireplaceSprite;
Hero* g_pHero;  

bool GameInitialize(HINSTANCE hInstance)
{
	//Create the game engine
	g_pGame = new GameEngine(hInstance, TEXT("Capstone Project"), TEXT("Dungeon Warrior"), IDI_ICON1, IDI_ICON1, 800, 600);

	if (g_pGame == NULL)
		return false;

	g_pGame->SetFrameRate(5);
	g_hInstance = hInstance;
	
	return true;
}

void GameStart(HWND hWindow)
{
	g_bGameOver = false;

	// Create the offscreen device context and bitmap
  	g_hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
  	g_hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow), g_pGame->GetWidth(), g_pGame->GetHeight());
  	SelectObject(g_hOffscreenDC, g_hOffscreenBitmap);

	//This sets the "level" to the loading screen
	isLoading = false;
	isConstruct = true;
	isDungeon = false;

	//Create 3 little rectangles to be used for the sprite that is the menu item selector
	//Will be used to determine which rectangle the sprite is within  
	SetRect(&g_rcLeft, 255, 540, 275, 580);
	SetRect(&g_rcMiddle, 330, 540, 350, 580);
	SetRect(&g_rcRight, 430, 540, 450, 580);
	//Set the window as a rectangle
	SetRect(&g_rcFullWindow, 0, 0, g_pGame->GetWidth(), g_pGame->GetHeight());

	//Load the Bitmaps and Sprites for the loading screen
	g_pLoadScreen = new Bitmap(GetDC(hWindow), IDB_BITMAP1, g_hInstance);
	g_pLoadScreenText = new Bitmap(GetDC(hWindow), IDB_BITMAP2, g_hInstance);
	g_pLoadScreenSelectorBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP3, g_hInstance);
	g_pDialogBox = new Bitmap(GetDC(hWindow), IDB_BITMAP4, g_hInstance);
	RECT rcLoadBounds = { 250, 540, 450, 580 }; ///< This bounds is only used for the SelectorSprite and keeps it within the dialog box.
	g_pLoadScreenSelectorSprite = new Sprite(g_pLoadScreenSelectorBitmap, rcLoadBounds);
	g_pLoadScreenSelectorSprite->SetPosition(255, 550);
	g_pLoadScreenSelectorSprite->SetNumFrames(1);
	g_pGame->AddLoadingSprite(g_pLoadScreenSelectorSprite);

	//Load the Bitmaps and Sprites for the Construct
	g_pConstructFloor = new Bitmap(GetDC(hWindow), IDB_BITMAP5, g_hInstance);
	g_pConstructUpperWallBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP6, g_hInstance);
	g_pConstructLowerWallBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP7, g_hInstance);
	g_pConstructRightWallBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP8, g_hInstance);
	g_pConstructLeftWallBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP9, g_hInstance);
	g_pConstructTopRightBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP10, g_hInstance);
	g_pConstructTopLeftBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP11, g_hInstance);
	g_pConstructBottomRightBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP12, g_hInstance);
	g_pConstructBottomLeftBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP13, g_hInstance);
	g_pConstructShelvesBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP14, g_hInstance);
	g_pConstructRightWindowBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP15, g_hInstance);
	g_pConstructLeftWindowBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP16, g_hInstance);
	g_pConstructTopWindowBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP17, g_hInstance);
	g_pConstructBottomWindowBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP18, g_hInstance);
	g_pConstructFireplaceBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP19, g_hInstance);
	//Figure out how many wall sprites are needed and use a for loop to add them to the vector
	for (int x = 0, counter = 0; x < g_pGame->GetWidth(); x += g_pConstructFloor->GetWidth(), ++counter)
	{
		g_pConstructUpperWallSprite[counter] = new Sprite(g_pConstructUpperWallBitmap, g_rcFullWindow);
		g_pConstructLowerWallSprite[counter] = new Sprite(g_pConstructLowerWallBitmap, g_rcFullWindow);
		g_pConstructUpperWallSprite[counter]->SetPosition(x, 0);
		g_pConstructLowerWallSprite[counter]->SetPosition(x, 575 - g_pDialogBox->GetHeight() - g_pConstructLowerWallBitmap->GetHeight());
		g_pGame->AddConstructSprite(g_pConstructUpperWallSprite[counter]);
		g_pGame->AddConstructSprite(g_pConstructLowerWallSprite[counter]);
	}
	for (int y = 0, counter = 0; y < 575 - g_pDialogBox->GetHeight() - g_pConstructRightWallBitmap->GetHeight(); y += g_pConstructRightWallBitmap->GetHeight(), counter++)
	{
		g_pConstructRightWallSprite[counter] = new Sprite(g_pConstructRightWallBitmap, g_rcFullWindow);
		g_pConstructLeftWallSprite[counter] = new Sprite(g_pConstructLeftWallBitmap, g_rcFullWindow);
		g_pConstructRightWallSprite[counter]->SetPosition(g_pGame->GetWidth() - g_pConstructRightWallBitmap->GetWidth(), y);
		g_pConstructLeftWallSprite[counter]->SetPosition(0, y);
		g_pGame->AddConstructSprite(g_pConstructRightWallSprite[counter]);
		g_pGame->AddConstructSprite(g_pConstructLeftWallSprite[counter]);
	}
	g_pConstructTopRightSprite = new Sprite(g_pConstructTopRightBitmap, g_rcFullWindow);
	g_pConstructTopRightSprite->SetPosition(g_pGame->GetWidth() - g_pConstructTopRightBitmap->GetWidth(), 0);
	g_pGame->AddConstructSprite(g_pConstructTopRightSprite);
	g_pConstructTopLeftSprite = new Sprite(g_pConstructTopLeftBitmap, g_rcFullWindow);
	g_pConstructTopLeftSprite->SetPosition(0, 0);
	g_pGame->AddConstructSprite(g_pConstructTopLeftSprite);
	g_pConstructBottomRightSprite = new Sprite(g_pConstructBottomRightBitmap, g_rcFullWindow);
	g_pConstructBottomRightSprite->SetPosition(g_pGame->GetWidth() - g_pConstructBottomRightBitmap->GetWidth(), 575 - g_pDialogBox->GetHeight() - g_pConstructBottomRightBitmap->GetWidth());
	g_pGame->AddConstructSprite(g_pConstructBottomRightSprite);
	g_pConstructBottomLeftSprite = new Sprite(g_pConstructBottomLeftBitmap, g_rcFullWindow);
	g_pConstructBottomLeftSprite->SetPosition(0, 575 - g_pDialogBox->GetHeight() - g_pConstructBottomLeftBitmap->GetWidth());
	g_pGame->AddConstructSprite(g_pConstructBottomLeftSprite);
	g_pConstructShelvesSprite = new Sprite(g_pConstructShelvesBitmap, g_rcFullWindow);
	g_pConstructShelvesSprite->SetPosition((g_pGame->GetWidth()/3), 0);
	g_pGame->AddConstructSprite(g_pConstructShelvesSprite);
	g_pConstructRightWindowSprite = new Sprite(g_pConstructRightWindowBitmap, g_rcFullWindow);
	g_pConstructRightWindowSprite->SetPosition(g_pGame->GetWidth() - g_pConstructRightWindowBitmap->GetWidth(), (g_pGame->GetHeight() / 2) - (g_pConstructRightWindowBitmap->GetHeight() / 2));
	g_pGame->AddConstructSprite(g_pConstructRightWindowSprite);
	g_pConstructLeftWindowSprite = new Sprite(g_pConstructLeftWindowBitmap, g_rcFullWindow);
	g_pConstructLeftWindowSprite->SetPosition(0, (g_pGame->GetHeight() / 2) - (g_pConstructLeftWindowBitmap->GetHeight() / 2));
	g_pGame->AddConstructSprite(g_pConstructLeftWindowSprite);
	g_pConstructTopWindowSprite = new Sprite(g_pConstructTopWindowBitmap, g_rcFullWindow);
	g_pConstructBottomWindowSprite = new Sprite(g_pConstructBottomWindowBitmap, g_rcFullWindow);
	g_pConstructBottomWindowSprite->SetPosition((g_pGame->GetWidth() / 4)*3 - (g_pConstructRightWindowBitmap->GetHeight() / 2), 575 - g_pDialogBox->GetHeight() - g_pConstructBottomWindowBitmap->GetHeight());
	g_pGame->AddConstructSprite(g_pConstructBottomWindowSprite);


	g_pConstructFireplaceSprite = new Sprite(g_pConstructFireplaceBitmap, g_rcFullWindow);
	g_pConstructFireplaceSprite->SetPosition((g_pGame->GetWidth() / 3)*2, 0);
	g_pGame->AddConstructSprite(g_pConstructFireplaceSprite);

	//Load the Bitmaps and Sprites for the Dungeon 
	//g_pDungeonFloor = new Bitmap(GetDC(hWindow), ,g_hInstance);
}

void GameEnd()
{
  	// Cleanup the offscreen device context and bitmap
  	DeleteObject(g_hOffscreenBitmap);
  	DeleteDC(g_hOffscreenDC); 

	//Deallocation of memory
  	g_pGame->CleanupSprites();
	delete g_pLoadScreenSelectorBitmap;
	g_pLoadScreenSelectorBitmap = NULL;
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
		g_pDialogBox->Draw(hDC, 250, 575 - g_pDialogBox->GetHeight());
		if (isSettings)
		{
			TextOut(hDC, 275, 550, TEXT("ENABLED"), 7);
			TextOut(hDC, 350, 550, TEXT("DISABLED"), 8);
			TextOut (hDC, 450, 550, TEXT("BACK"), 4);
		}
		else
		{
			TextOut(hDC, 275, 550, TEXT("START"), 5);
			TextOut(hDC, 350, 550, TEXT("SETTINGS"), 8);
			TextOut(hDC, 450, 550, TEXT("QUIT"), 4);
		}
		g_pGame->DrawLoadingSprites(hDC);

	}
	if (isConstruct)
	{
		g_pDialogBox->Draw(hDC, 250, 575 - g_pDialogBox->GetHeight());
		//Tile the floor with the floor bitmap
		for (int y = 0; y < (575 - g_pDialogBox->GetHeight()) - g_pConstructFloor->GetHeight(); y += g_pConstructFloor->GetHeight())
			for (int x = 0; x < g_pGame->GetWidth(); x += g_pConstructFloor->GetWidth())
				g_pConstructFloor->Draw(hDC, x, y);

		g_pGame->DrawConstructSprites(hDC);

	}
	if (isDungeon)
	{
		//Tile the floor with the floor bitmap
		//for (int y = 0; y < (580 - g_pDialogBox->GetHeight()) - g_pDungeonFloor->GetHeight(); y += g_pDungeonFloor->GetHeight())
			//for (int x = 0; x < g_pGame->GetWidth(); x += g_pDungeonFloor->GetWidth())
				//g_pDungeonFloor->Draw(hDC, x, y);
	}
}

void GameCycle()
{
  	if (!g_bGameOver)
  	{
		// Update the sprites
		if(isLoading)			
    		g_pGame->UpdateLoadingSprites();
		if(isConstruct)
			g_pGame->UpdateConstructSprites();
		if(isDungeon)
			g_pGame->UpdateDungeonSprites();

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
	RECT& selRC = g_pLoadScreenSelectorSprite->GetPosition();

	switch (wParam)
	{
	case VK_LEFT:
		if (isTest)
		{
			TextOut(hDC, 0, 0, TEXT("LEFT KEY"), 8);
		}
		if (isLoading)
		{
			if (selRC.left > g_rcLeft.left && selRC.left < g_rcRight.left)
			{
				//Check to see if the Selector is on the middle selection
				//Then move to the left side.
				g_pLoadScreenSelectorSprite->SetPosition(255, 550);
				break;
			}
			if (selRC.left > g_rcMiddle.left)
			{
				//Check to see if the Selector is on the right selection
				//Then move to the middle selection.
				g_pLoadScreenSelectorSprite->SetPosition(330, 550);
				break;
			}
			if (selRC.left < g_rcMiddle.left)
			{
				//Check to see if the selector is on the left side.
				//Then wrap around to the right selection.
				g_pLoadScreenSelectorSprite->SetPosition(430, 550);
				break;
			}
		}
		if (isConstruct || isDungeon)
		{
			g_pHero->MoveLeft();
		}
		break;
	case VK_RIGHT:
		if (isTest)
		{
			TextOut(hDC, 0, 0, TEXT("RIGHT KEY"), 9);
		}
		if (isLoading)
		{
			if (selRC.left < g_rcRight.left && selRC.left > g_rcLeft.left)
			{
				//Check to see if the Selector is on the middle selection
				//Then move to the right side.
				g_pLoadScreenSelectorSprite->SetPosition(430, 550);
				break;
			}
			if (selRC.left > g_rcMiddle.left)
			{
				//Check to see if the Selector is on the right selection
				//Then move to the left selection.
				g_pLoadScreenSelectorSprite->SetPosition(255, 550);
				break;
			}
			if (selRC.left < g_rcMiddle.left)
			{
				//Check to see if the selector is on the left side.
				//Then wrap around to the middle selection.
				g_pLoadScreenSelectorSprite->SetPosition(330, 550);
				break;
			}
		}
		if (isConstruct || isDungeon)
		{
			g_pHero->MoveRight();
		}
		break;
	case VK_UP:
		if (isTest)
		{
			TextOut(hDC, 0, 0, TEXT("UP KEY"), 6);
		}
		if (isConstruct || isDungeon)
		{
			g_pHero->MoveUp();
		}
		break;
	case VK_DOWN:
		if (isTest)
		{
			TextOut(hDC, 0, 0, TEXT("DOWN KEY"), 8);
		}
		if (isConstruct || isDungeon)
		{
			g_pHero->MoveDown();
		}
		break;
	case VK_SPACE:
		if (isLoading)
		{
			if (isSettings)
			{
				if (selRC.left == g_rcLeft.left)
				{
					//This will enable Test mode.  
					isTest = true;
				}
				if (selRC.left == g_rcMiddle.left)
				{
					//This will disable Test mode.  
					isTest = false;
				}
				if (selRC.left == g_rcRight.left)
				{
					//Stop the settings menu and return to main menu
					isSettings = false;
					//Reposition selector to beginning of menu 
					g_pLoadScreenSelectorSprite->SetPosition(255, 550);
				}
			}
			else
			{
				if (selRC.left == g_rcLeft.left)
				{
					//The selector should be on START here. Make sure Settings are off and transition from Loading to Construct.  
					isConstruct = true;
					isLoading = false;
				}
				if (selRC.left == g_rcMiddle.left)
				{
					//The selector should be on settings here. Enable the settings menu.  
					isSettings = true;
					//Reposition selector to beginning of menu 
					g_pLoadScreenSelectorSprite->SetPosition(255, 550);

				}
				if (selRC.left == g_rcRight.left)
				{
					//Change screen resolution back to normal.
					ChangeDisplaySettings(NULL, 0);				
					//Selector should be on QUIT. 
					PostQuitMessage(0);
				}

			}
		}
		if (isTest)
		{
			TextOut(hDC, 0, 0, TEXT("BOOM-BOOM KEY"), 14);
		}
		if (isDungeon)
		{
			g_pHero->UseWeapon();
		}
		if (isConstruct)
		{
			//Get Hero's location, if touching a weapon, this will select weapon
			isLoading = true; ///< Remove later...just to get back to quit
			isConstruct = false;
		}
		break;
	case VK_RETURN:
		if (isLoading)
		{
			if (isSettings)
			{
				if (selRC.left == g_rcLeft.left)
				{
					//This will enable Test mode.  
					isTest = true;
				}
				if (selRC.left == g_rcMiddle.left)
				{
					//This will disable Test mode.  
					isTest = false;
				}
				if (selRC.left == g_rcRight.left)
				{
					//Stop the settings menu and return to main menu
					isSettings = false;
					//Reposition selector to beginning of menu 
					g_pLoadScreenSelectorSprite->SetPosition(255, 550);
				}
			}
			else
			{
				if (selRC.left == g_rcLeft.left)
				{
					//The selector should be on START here. Make sure Settings are off and transition from Loading to Construct.  
					isConstruct = true;
					isLoading = false;
				}
				if (selRC.left == g_rcMiddle.left)
				{
					//The selector should be on settings here. Enable the settings menu.  
					isSettings = true;
					//Reposition selector to beginning of menu 
					g_pLoadScreenSelectorSprite->SetPosition(255, 550);

				}
				if (selRC.left == g_rcRight.left)
				{
					//Change screen resolution back to normal.
					ChangeDisplaySettings(NULL, 0);				
					//Selector should be on QUIT. 
					PostQuitMessage(0);
				}

			}
		}
		if (isConstruct)
		{
			//Get Hero's location, if touching a weapon, this will select weapon
			isLoading = true; ///< Remove later...just to get back to quit
			isConstruct = false;
		}
		break;
	default:
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
	}
  	else
  	{
    	// Create 
    	// Play the background music
    	//g_pGame->PlayMIDISong(TEXT(""));
  	}
}