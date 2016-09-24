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
4Sep16	Added several bitmaps/sprits to build Construct level.
20Sep16 Loading enemy sprites that were hidden into the vector was causing errors. Commented them out for now to continue on with game.
21Sep16 Draw hero's health indicators to screen
21Sep16 New debug modes: Page Up/Down will cycle through levels
************************************************************************/
#include <Windows.h>
#include <Wingdi.h>
#include <stdlib.h>
#include "GameEngine.h"
#include "Resource.h"
#include "Sprite.h"
#include "Hero.h"
#include "EnemyBoss.h"

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
RECT				g_rcEnemeyBounds;
static RECT			g_rcLeft;
static RECT			g_rcMiddle;
static RECT			g_rcRight;

///////////////////////////////
//Load Bitmaps into memory
///////////////////////////////
//Load Screen
Bitmap* g_pLoadScreen;
Bitmap* g_pLoadScreenText;
Bitmap* g_pLoadScreenSelectorBitmap;
Bitmap* g_pDialogBox; //used in load screen, construct, and dungeon.
//Construct
Bitmap* g_pConstructFloor;
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
Bitmap* g_pConstructMentorBitmap;
Bitmap* g_pConstructBowBitmap;
Bitmap* g_pConstructBoomerangBitmap;
Bitmap* g_pConstructSwordBitmap;
//Dungeon
Bitmap* g_pDungeonFloor;
Bitmap* g_pDungeonUpperWallBitmap;
Bitmap* g_pDungeonLowerWallBitmap;
Bitmap* g_pDungeonRightWallBitmap;
Bitmap* g_pDungeonLeftWallBitmap;
Bitmap* g_pDungeonTopRightBitmap;
Bitmap* g_pDungeonTopLeftBitmap;
Bitmap* g_pDungeonBottomRightBitmap;
Bitmap* g_pDungeonBottomLeftBitmap;
Bitmap* g_pDungeonUpperVinesBitmap;
Bitmap* g_pDungeonLowerVinesBitmap;
Bitmap* g_pDungeonRightVinesBitmap;
Bitmap* g_pDungeonLeftVinesBitmap;
Bitmap* g_pDungeonFirepitBitmap;
Bitmap* g_pDungeonGoldSkullBitmap;
Bitmap* g_pDungeonSkullBitmap;
Bitmap* g_pDungeonLtGreenSkullBitmap;
//Hero
Bitmap* g_pHeroBitmap;
Bitmap* g_pHeroHealthBitmap;
///Hero himself
Bitmap *g_pHeroWalkingLeftBitmap;
Bitmap *g_pHeroWalkingRightBitmap;
Bitmap *g_pHeroWalkingUpBitmap;
Bitmap *g_pHeroWalkingDownBitmap;
Bitmap *g_pHeroDamageLeftBitmap;
Bitmap *g_pHeroDamageRightBitmap;
Bitmap *g_pHeroDamageUpBitmap;
Bitmap *g_pHeroDamageDownBitmap;
Bitmap *g_pHeroDyingBitmap;
Bitmap *g_pHeroWinBitmap;
Bitmap *g_pHeroBoomerangLeftBitmap;
Bitmap *g_pHeroBoomerangRightBitmap;
Bitmap *g_pHeroBoomerangDownBitmap;
Bitmap *g_pHeroBoomerangUpBitmap;
Bitmap *g_pHeroBowLeftBitmap;
Bitmap *g_pHeroBowRightBitmap;
Bitmap *g_pHeroBowUpBitmap;
Bitmap *g_pHeroBowDownBitmap;
Bitmap *g_pHeroSwordLeftBitmap;
Bitmap *g_pHeroSwordRightBitmap;
Bitmap *g_pHeroSwordUpBitmap;
Bitmap *g_pHeroSwordDownBitmap;
///Weapons
Bitmap *g_pArrowLeftBitmap;
Bitmap *g_pArrowRightBitmap;
Bitmap *g_pArrowUpBitmap;
Bitmap *g_pArrowDownBitmap;
Bitmap *g_pBoomerangBitmap;
Bitmap *g_pSwordSwingLeftBitmap;
Bitmap *g_pSwordSwingRightBitmap;
Bitmap *g_pSwordSwingUpBitmap;
Bitmap *g_pSwordSwingDownBitmap;
//Enemies
Bitmap* g_pEnemyTenticalBitmap;


//////////////////////////////////////
//Load Sprites into memory
//////////////////////////////////////
//Load Screen
Sprite* g_pLoadScreenSelectorSprite;
//Construct
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
Sprite* g_pConstructMentorSprite;
Sprite* g_pConstructBowSprite;
Sprite* g_pConstructBoomerangSprite;
Sprite* g_pConstructSwordSprite;
//Dungeon
Sprite* g_pDungeonUpperWallSprite[52];
Sprite* g_pDungeonLowerWallSprite[52];
Sprite* g_pDungeonRightWallSprite[34];
Sprite* g_pDungeonLeftWallSprite[34];
Sprite* g_pDungeonTopRightSprite;
Sprite* g_pDungeonTopLeftSprite;
Sprite* g_pDungeonBottomRightSprite;
Sprite* g_pDungeonBottomLeftSprite;
Sprite* g_pDungeonUpperVinesSprite;
Sprite* g_pDungeonLowerVinesSprite;
Sprite* g_pDungeonRightVinesSprite;
Sprite* g_pDungeonLeftVinesSprite;
Sprite* g_pDungeonFirepitSprite;
Sprite* g_pDungeonGoldSkullSprite;
Sprite* g_pDungeonSkullSprite;
Sprite* g_pDungeonLtGreenSkullSprite;
//Hero
Hero* g_pHero;
//Enemies
EnemyBoss* g_pEnemyBigPigSprite;
EnemyBoss* g_pEnemyExplosionSprite[5]; //Use 5 so you can 5 of each enemy on the screen
EnemyBoss* g_pEnemyMonkeyDownSprite[5];
EnemyBoss* g_pEnemyMonkeyUpSprite[5];
EnemyBoss* g_pEnemyMonkeyLeftSprite[5];
EnemyBoss* g_pEnemyMonkeyRightSprite[5];
EnemyBoss* g_pEnemyTenticalSprite[5];
EnemyBoss* g_pEnemyTenticalDieSprite[5];

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
	// Seed the random number generator
	srand(GetTickCount());

	g_bGameOver = false;

	// Create the offscreen device context and bitmap
  	g_hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
  	g_hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow), g_pGame->GetWidth(), g_pGame->GetHeight());
  	SelectObject(g_hOffscreenDC, g_hOffscreenBitmap);

	//This sets the "level" to the loading screen
	isLoading = true;
	isConstruct = false;
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
	g_pConstructMentorBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP20, g_hInstance);
	g_pConstructBowBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP21, g_hInstance);
	g_pConstructBoomerangBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP22, g_hInstance);
	g_pConstructSwordBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP23, g_hInstance);
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
	g_pConstructMentorSprite = new Sprite(g_pConstructMentorBitmap, g_rcFullWindow);
	g_pConstructMentorSprite->SetFrameDelay(3);
	g_pConstructMentorSprite->SetNumFrames(2);
	g_pConstructMentorSprite->SetPosition(g_pGame->GetWidth() / 7, 60);
	g_pGame->AddConstructSprite(g_pConstructMentorSprite);
	g_pConstructBowSprite = new Sprite(g_pConstructBowBitmap, g_rcFullWindow);
	g_pConstructBowSprite->SetPosition((g_pGame->GetWidth() / 7) * 2, 80);
	g_pGame->AddConstructSprite(g_pConstructBowSprite);
	g_pConstructBoomerangSprite = new Sprite(g_pConstructBoomerangBitmap, g_rcFullWindow);
	g_pConstructBoomerangSprite->SetPosition((g_pGame->GetWidth() / 7) * 3, 80);
	g_pGame->AddConstructSprite(g_pConstructBoomerangSprite);
	g_pConstructSwordSprite = new Sprite(g_pConstructSwordBitmap, g_rcFullWindow);
	g_pConstructSwordSprite->SetPosition((g_pGame->GetWidth() / 7) * 4, 80);
	g_pGame->AddConstructSprite(g_pConstructSwordSprite);
	//Load the Bitmaps and Sprites for the Dungeon 
	g_pDungeonFloor = new Bitmap(GetDC(hWindow), IDB_BITMAP24, g_hInstance);
	g_pDungeonUpperWallBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP25, g_hInstance);
	g_pDungeonLowerWallBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP26, g_hInstance);
	g_pDungeonRightWallBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP27, g_hInstance);
	g_pDungeonLeftWallBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP28, g_hInstance);
	g_pDungeonTopRightBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP29, g_hInstance);
	g_pDungeonTopLeftBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP30, g_hInstance);
	g_pDungeonBottomRightBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP31, g_hInstance);
	g_pDungeonBottomLeftBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP32, g_hInstance);
	g_pDungeonUpperVinesBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP33, g_hInstance);
	g_pDungeonLowerVinesBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP34, g_hInstance);
	g_pDungeonRightVinesBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP35, g_hInstance);
	g_pDungeonLeftVinesBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP36, g_hInstance);
	g_pDungeonFirepitBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP37, g_hInstance);
	g_pDungeonGoldSkullBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP38, g_hInstance);
	g_pDungeonSkullBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP39, g_hInstance);
	g_pDungeonLtGreenSkullBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP40, g_hInstance);
	//Figure out how many wall sprites are needed and use a for loop to add them to the vector
	for (int x = 0, counter = 0; x < g_pGame->GetWidth(); x += g_pDungeonFloor->GetWidth(), ++counter)
	{
		g_pDungeonUpperWallSprite[counter] = new Sprite(g_pDungeonUpperWallBitmap, g_rcFullWindow);
		g_pDungeonLowerWallSprite[counter] = new Sprite(g_pDungeonLowerWallBitmap, g_rcFullWindow);
		g_pDungeonUpperWallSprite[counter]->SetPosition(x, 0);
		g_pDungeonLowerWallSprite[counter]->SetPosition(x, 575 - g_pDialogBox->GetHeight() - g_pDungeonLowerWallBitmap->GetHeight());
		g_pGame->AddDungeonSprite(g_pDungeonUpperWallSprite[counter]);
		g_pGame->AddDungeonSprite(g_pDungeonLowerWallSprite[counter]);
	}
	//To keep the dungeon size the same size as the construct, we will still check against the DialogBox even though the dialog box won't be used in the dungeon
	for (int y = 0, counter = 0; y < 575 - g_pDialogBox->GetHeight() - g_pDungeonRightWallBitmap->GetHeight(); y += g_pDungeonRightWallBitmap->GetHeight(), counter++)
	{
		g_pDungeonRightWallSprite[counter] = new Sprite(g_pDungeonRightWallBitmap, g_rcFullWindow);
		g_pDungeonLeftWallSprite[counter] = new Sprite(g_pDungeonLeftWallBitmap, g_rcFullWindow);
		g_pDungeonRightWallSprite[counter]->SetPosition(g_pGame->GetWidth() - g_pDungeonRightWallBitmap->GetWidth(), y);
		g_pDungeonLeftWallSprite[counter]->SetPosition(0, y);
		g_pGame->AddDungeonSprite(g_pDungeonRightWallSprite[counter]);
		g_pGame->AddDungeonSprite(g_pDungeonLeftWallSprite[counter]);
	}
	g_pDungeonTopRightSprite = new Sprite(g_pDungeonTopRightBitmap, g_rcFullWindow);
	g_pDungeonTopRightSprite->SetPosition(g_pGame->GetWidth() - g_pDungeonTopRightBitmap->GetWidth(), 0);
	g_pGame->AddDungeonSprite(g_pDungeonTopRightSprite);
	g_pDungeonTopLeftSprite = new Sprite(g_pDungeonTopLeftBitmap, g_rcFullWindow);
	g_pDungeonTopLeftSprite->SetPosition(0, 0);
	g_pGame->AddDungeonSprite(g_pDungeonTopLeftSprite);
	g_pDungeonBottomRightSprite = new Sprite(g_pDungeonBottomRightBitmap, g_rcFullWindow);
	g_pDungeonBottomRightSprite->SetPosition(g_pGame->GetWidth() - g_pDungeonBottomRightBitmap->GetWidth(), 575 - g_pDialogBox->GetHeight() - g_pDungeonBottomRightBitmap->GetWidth());
	g_pGame->AddDungeonSprite(g_pDungeonBottomRightSprite);
	g_pDungeonBottomLeftSprite = new Sprite(g_pDungeonBottomLeftBitmap, g_rcFullWindow);
	g_pDungeonBottomLeftSprite->SetPosition(0, 575 - g_pDialogBox->GetHeight() - g_pDungeonBottomLeftBitmap->GetWidth());
	g_pGame->AddDungeonSprite(g_pDungeonBottomLeftSprite);
	g_pDungeonRightVinesSprite = new Sprite(g_pDungeonRightVinesBitmap, g_rcFullWindow);
	g_pDungeonRightVinesSprite->SetPosition(g_pGame->GetWidth() - g_pDungeonRightVinesBitmap->GetWidth(), (g_pGame->GetHeight() / 2) - (g_pDungeonRightVinesBitmap->GetHeight() / 2));
	g_pGame->AddDungeonSprite(g_pDungeonRightVinesSprite);
	g_pDungeonLeftVinesSprite = new Sprite(g_pDungeonLeftVinesBitmap, g_rcFullWindow);
	g_pDungeonLeftVinesSprite->SetPosition(0, (g_pGame->GetHeight() / 2) - (g_pDungeonLeftVinesBitmap->GetHeight() / 2));
	g_pGame->AddDungeonSprite(g_pDungeonLeftVinesSprite);
	g_pDungeonUpperVinesSprite = new Sprite(g_pDungeonUpperVinesBitmap, g_rcFullWindow);
	g_pDungeonLowerVinesSprite = new Sprite(g_pDungeonLowerVinesBitmap, g_rcFullWindow);
	g_pDungeonLowerVinesSprite->SetPosition((g_pGame->GetWidth() / 4) * 3 - (g_pDungeonRightVinesBitmap->GetHeight() / 2), 575 - g_pDialogBox->GetHeight() - g_pDungeonLowerVinesBitmap->GetHeight());
	g_pGame->AddDungeonSprite(g_pDungeonLowerVinesSprite);
	g_pDungeonFirepitSprite = new Sprite(g_pDungeonFirepitBitmap, g_rcFullWindow);
	g_pDungeonFirepitSprite->SetFrameDelay(0);
	g_pDungeonFirepitSprite->SetNumFrames(3);
	g_pDungeonFirepitSprite->SetPosition(g_pGame->GetWidth() - (g_pDungeonRightWallBitmap->GetWidth() + (g_pDungeonFirepitBitmap->GetWidth()/3)), g_pDungeonUpperWallBitmap->GetHeight());
	g_pGame->AddDungeonSprite(g_pDungeonFirepitSprite);
	//Enemies
	//Set the enemy bounds rectanlge so they're only in the playable area
	SetRect(&g_rcEnemeyBounds, g_pDungeonLeftWallBitmap->GetWidth(), g_pDungeonUpperWallBitmap->GetHeight(), g_pGame->GetWidth() - g_pDungeonRightWallBitmap->GetWidth(), g_pGame->GetHeight() - (g_pDialogBox->GetHeight() + g_pDungeonLowerWallBitmap->GetHeight()));
	g_pEnemyTenticalBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP47, g_hInstance);
	g_pGame->AddDungeonSprite(g_pEnemyBigPigSprite);
	for (int x = 0; x < 5; x++)
	{
		g_pEnemyTenticalSprite[x] = new EnemyBoss(g_pEnemyTenticalBitmap, g_rcEnemeyBounds, BA_BOUNCE);
		g_pEnemyTenticalSprite[x]->SetNumFrames(3);
		g_pEnemyTenticalSprite[x]->SetFrameDelay(1);
		g_pEnemyTenticalSprite[x]->MoveRandomly(800, 640 - (16 + g_pDungeonLowerWallBitmap->GetHeight() + g_pDialogBox->GetHeight()));
		g_pGame->AddDungeonSprite(g_pEnemyTenticalSprite[x]);
	}
	//Hero
	//Initialize Hero bitmaps
	g_pHeroWalkingLeftBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP49, g_hInstance);
	g_pHeroWalkingRightBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP50, g_hInstance);
	g_pHeroWalkingUpBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP51, g_hInstance);
	g_pHeroWalkingDownBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP52, g_hInstance);
	g_pHeroDamageLeftBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP53, g_hInstance);
	g_pHeroDamageRightBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP54, g_hInstance);
	g_pHeroDamageUpBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP55, g_hInstance);
	g_pHeroDamageDownBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP56, g_hInstance);
	g_pHeroDyingBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP57, g_hInstance);
	g_pHeroWinBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP58, g_hInstance);
	g_pHeroBoomerangLeftBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP59, g_hInstance);
	g_pHeroBoomerangRightBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP60, g_hInstance);
	g_pHeroBoomerangDownBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP61, g_hInstance);
	g_pHeroBoomerangUpBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP79, g_hInstance);
	g_pHeroBowLeftBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP62, g_hInstance);
	g_pHeroBowRightBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP63, g_hInstance);
	g_pHeroBowUpBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP64, g_hInstance);
	g_pHeroBowDownBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP65, g_hInstance);
	g_pHeroSwordLeftBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP66, g_hInstance);
	g_pHeroSwordRightBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP67, g_hInstance);
	g_pHeroSwordUpBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP68, g_hInstance);
	g_pHeroSwordDownBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP69, g_hInstance);
	//Initiazlize Weapon bitmaps
	g_pArrowLeftBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP70, g_hInstance);
	g_pArrowRightBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP71, g_hInstance);
	g_pArrowUpBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP72, g_hInstance);
	g_pArrowDownBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP73, g_hInstance);
	g_pBoomerangBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP74, g_hInstance);
	g_pSwordSwingLeftBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP75, g_hInstance);
	g_pSwordSwingRightBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP76, g_hInstance);
	g_pSwordSwingUpBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP77, g_hInstance);
	g_pSwordSwingDownBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP78, g_hInstance);
	//Create Hero sprite
	g_pHeroBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP58, g_hInstance);
	g_pHero = new Hero(g_pHeroBitmap, g_rcEnemeyBounds, BA_STOP);
	g_pHero->SetPosition(g_pGame->GetWidth() / 2, g_pGame->GetHeight() / 2);
	g_pGame->AddConstructSprite(g_pHero);
	g_pHeroHealthBitmap = new Bitmap(GetDC(hWindow), IDB_BITMAP80, g_hInstance);
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
			TextOut(hDC, 260, (575 - g_pDialogBox->GetHeight()) + 10, TEXT("DEBUG MODE:"), 11);
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
		TextOut(hDC, 260, (575 - g_pDialogBox->GetHeight()) + 10, TEXT("WISEMAN: Welcome Dungeon Warrior,"), 33);
		TextOut(hDC, 260, (575 - g_pDialogBox->GetHeight()) + 28, TEXT("select your weapon that will defeat"), 35);
		TextOut(hDC, 260, (575 - g_pDialogBox->GetHeight()) + 46, TEXT("the monsters!"), 13);
		//Tile the floor with the floor bitmap
		for (int y = 0; y < (575 - g_pDialogBox->GetHeight()) - g_pConstructFloor->GetHeight(); y += g_pConstructFloor->GetHeight())
			for (int x = 0; x < g_pGame->GetWidth(); x += g_pConstructFloor->GetWidth())
				g_pConstructFloor->Draw(hDC, x, y);

		g_pGame->DrawConstructSprites(hDC);

		//Draw Hero's health over everything
		for (int x = g_pGame->GetWidth() - 12, counter = 0; counter < g_pHero->GetHealth(); counter++, x - 10)
			g_pHeroHealthBitmap->Draw(hDC, x, 10);

	}
	if (isDungeon)
	{
		g_pDialogBox->Draw(hDC, 250, 575 - g_pDialogBox->GetHeight());
		TextOut(hDC, 260, (575 - g_pDialogBox->GetHeight()) + 28, TEXT("Destory all the enemies!!"), 25);
		//Tile the floor with the floor bitmap
		for (int y = 0; y < (580 - g_pDialogBox->GetHeight()) - g_pDungeonFloor->GetHeight(); y += g_pDungeonFloor->GetHeight())
			for (int x = 0; x < g_pGame->GetWidth(); x += g_pDungeonFloor->GetWidth())
				g_pDungeonFloor->Draw(hDC, x, y);

		g_pGame->DrawDungeonSprites(hDC);

		//Draw Hero's health over everything
		for (int x = g_pGame->GetWidth() - 12, counter = 0; counter < g_pHero->GetHealth(); counter++, x - 10)
			g_pHeroHealthBitmap->Draw(hDC, x, 10);
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
	case VK_NEXT:
		if (isTest)
		{
			if (isLoading)
			{
				isConstruct = true;
				isDungeon = false;
				isLoading = false;
				break;
			}
			if (isConstruct)
			{
				isDungeon = true;
				isLoading = false;
				isConstruct = false;
				break;
			}
			if (isDungeon)
			{
				isLoading = true;
				isConstruct = false;
				isDungeon = false;
				break;
			}
		}
		break;
	case VK_PRIOR:
		if (isTest)
		{
			if (isLoading)
			{
				isDungeon = true;
				isConstruct = false;
				isLoading = false;
				break;
			}
			if (isConstruct)
			{
				isLoading = true;
				isDungeon = false;
				isConstruct = false;
				break;
			}
			if (isDungeon)
			{
				isConstruct = true;
				isLoading = false;
				isDungeon = false;
				break;
			}
		}
		break;
	case VK_END:
		if (isTest)
		{
			//Change screen resolution back to normal.
			ChangeDisplaySettings(NULL, 0);
			//Selector should be on QUIT. 
			PostQuitMessage(0);
		}
		break;
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
			Bitmap *pNewBitmap;
			int iNumFrames;

			switch (g_pHero->GetWeapon())
			{
			case WT_BOOMERANG:
				pNewBitmap = g_pHeroBoomerangLeftBitmap;
				iNumFrames = 2;
				break;
			case WT_BOW:
				pNewBitmap = g_pHeroBowLeftBitmap;
				iNumFrames = 2;
				break;
			case WT_SWORD:
				pNewBitmap = g_pHeroWalkingLeftBitmap;
				iNumFrames = 8;
				break;
			default:
				pNewBitmap = g_pHeroWalkingLeftBitmap;
				iNumFrames = 8;
			}
			g_pHero->SetDirection(FD_LEFT);
			g_pHero->SetBitmap(pNewBitmap);
			g_pHero->SetNumFrames(iNumFrames);
			g_pHero->SetVelocity(-8, 0);
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
			Bitmap *pNewBitmap;
			int iNumFrames;

			switch (g_pHero->GetWeapon())
			{
			case WT_BOOMERANG:
				pNewBitmap = g_pHeroBoomerangRightBitmap;
				iNumFrames = 2;
				break;
			case WT_BOW:
				pNewBitmap = g_pHeroBowRightBitmap;
				iNumFrames = 2;
				break;
			case WT_SWORD:
				pNewBitmap = g_pHeroWalkingRightBitmap;
				iNumFrames = 8;
				break;
			default:
				pNewBitmap = g_pHeroWalkingRightBitmap;
				iNumFrames = 8;
			}
			g_pHero->SetDirection(FD_RIGHT);
			g_pHero->SetBitmap(pNewBitmap);
			g_pHero->SetNumFrames(iNumFrames);
			g_pHero->SetVelocity(8, 0);
		}
		break;
	case VK_UP:
		if (isTest)
		{
			TextOut(hDC, 0, 0, TEXT("UP KEY"), 6);
		}
		if (isConstruct || isDungeon)
		{
			Bitmap *pNewBitmap;
			int iNumFrames;

			switch (g_pHero->GetWeapon())
			{
			case WT_BOOMERANG:
				pNewBitmap = g_pHeroBoomerangUpBitmap;
				iNumFrames = 2;
				break;
			case WT_BOW:
				pNewBitmap = g_pHeroBowUpBitmap;
				iNumFrames = 2;
				break;
			case WT_SWORD:
				pNewBitmap = g_pHeroWalkingUpBitmap;
				iNumFrames = 8;
				break;
			default:
				pNewBitmap = g_pHeroWalkingUpBitmap;
				iNumFrames = 8;
			}
			g_pHero->SetDirection(FD_UP);
			g_pHero->SetBitmap(pNewBitmap);
			g_pHero->SetNumFrames(iNumFrames);
			g_pHero->SetVelocity(0, -8);
		}
		break;
	case VK_DOWN:
		if (isTest)
		{
			TextOut(hDC, 0, 0, TEXT("DOWN KEY"), 8);
		}
		if (isConstruct || isDungeon)
		{
			Bitmap *pNewBitmap;
			int iNumFrames;

			switch (g_pHero->GetWeapon())
			{
			case WT_BOOMERANG:
				pNewBitmap = g_pHeroBoomerangDownBitmap;
				iNumFrames = 2;
				break;
			case WT_BOW:
				pNewBitmap = g_pHeroBowDownBitmap;
				iNumFrames = 2;
				break;
			case WT_SWORD:
				pNewBitmap = g_pHeroWalkingDownBitmap;
				iNumFrames = 8;
				break;
			default:
				pNewBitmap = g_pHeroWalkingDownBitmap;
				iNumFrames = 8;
			}
			g_pHero->SetDirection(FD_DOWN);
			g_pHero->SetBitmap(pNewBitmap);
			g_pHero->SetNumFrames(iNumFrames);
			g_pHero->SetVelocity(0, 8);
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
					//In normal game play the hero sprite will be added by the level
					//In debug mode the sprite will never get added so will be by debug
					g_pGame->AddDungeonSprite(g_pHero);
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
			switch (g_pHero->GetWeapon())
			{
			case WT_SWORD:
			{
				//Get direction hero is facing
				//Set new bitmap and frames for that direction
				//have animation run only once
				//after animation completes, go back to last bitmap
				Sprite *pSwordSwingSprite = NULL;
				switch (g_pHero->GetDirection())
				{
				case FD_LEFT:
					g_pHero->SetBitmap(g_pHeroSwordLeftBitmap);
					g_pHero->SetNumFrames(12);
					g_pHero->SetVelocity(0, 0);
					pSwordSwingSprite = new Sprite(g_pSwordSwingLeftBitmap);
					pSwordSwingSprite->SetNumFrames(12, true);
					pSwordSwingSprite->SetPosition(g_pHero->GetPosition());
					g_pGame->AddDungeonSprite(pSwordSwingSprite);
					break;
				case FD_RIGHT:
					g_pHero->SetBitmap(g_pHeroSwordRightBitmap);
					g_pHero->SetNumFrames(12);
					g_pHero->SetVelocity(0, 0);
					pSwordSwingSprite = new Sprite(g_pSwordSwingRightBitmap);
					pSwordSwingSprite->SetNumFrames(12, true);
					pSwordSwingSprite->SetPosition(g_pHero->GetPosition());
					g_pGame->AddDungeonSprite(pSwordSwingSprite);
					break;
				case FD_UP:
					g_pHero->SetBitmap(g_pHeroSwordUpBitmap);
					g_pHero->SetNumFrames(12);
					g_pHero->SetVelocity(0, 0);
					pSwordSwingSprite = new Sprite(g_pSwordSwingUpBitmap);
					pSwordSwingSprite->SetNumFrames(12, true);
					pSwordSwingSprite->SetPosition(g_pHero->GetPosition());
					g_pGame->AddDungeonSprite(pSwordSwingSprite);
					break;
				case FD_DOWN:
					g_pHero->SetBitmap(g_pHeroSwordDownBitmap);
					g_pHero->SetNumFrames(12);
					g_pHero->SetVelocity(0, 0);
					pSwordSwingSprite = new Sprite(g_pSwordSwingDownBitmap);
					pSwordSwingSprite->SetNumFrames(12, true);
					pSwordSwingSprite->SetPosition(g_pHero->GetPosition());
					g_pGame->AddDungeonSprite(pSwordSwingSprite);
					break;
				default:
					break;
				}
				break;
			}
			case WT_BOOMERANG:
			{
				// Need to setup a bounding area around the hero that moves with hero
				Sprite *pBoomerangSprite = new Sprite(g_pBoomerangBitmap);
				pBoomerangSprite->SetNumFrames(4);
				//pBoomerangSprite->SetBounds(RECT&); ///< figure out the rect around the hero
				switch (g_pHero->GetDirection())
				{
				case FD_LEFT:
					pBoomerangSprite->SetPosition(g_pHero->GetPosition());
					pBoomerangSprite->SetVelocity(-12, 0);
					pBoomerangSprite->SetBoundsAction(BA_BOUNCE);
					g_pGame->AddDungeonSprite(pBoomerangSprite);
					break;
				case FD_RIGHT:
					pBoomerangSprite->SetPosition(g_pHero->GetPosition());
					pBoomerangSprite->SetVelocity(12, 0);
					pBoomerangSprite->SetBoundsAction(BA_BOUNCE);
					g_pGame->AddDungeonSprite(pBoomerangSprite);
					break;
				case FD_UP:
					pBoomerangSprite->SetPosition(g_pHero->GetPosition());
					pBoomerangSprite->SetVelocity(0, -12);
					pBoomerangSprite->SetBoundsAction(BA_BOUNCE);
					g_pGame->AddDungeonSprite(pBoomerangSprite);
					break;
				case FD_DOWN:
					pBoomerangSprite->SetPosition(g_pHero->GetPosition());
					pBoomerangSprite->SetVelocity(0, 12);
					pBoomerangSprite->SetBoundsAction(BA_BOUNCE);
					g_pGame->AddDungeonSprite(pBoomerangSprite);
					break;
				default:
					break;
				}
				break;
			}
			case WT_BOW:
			{
				Sprite* pArrowSprite = NULL;
				switch (g_pHero->GetDirection())
				{
				case FD_LEFT:
					pArrowSprite = new Sprite(g_pArrowLeftBitmap);
					pArrowSprite->SetNumFrames(9);
					pArrowSprite->SetBoundsAction(BA_DIE);
					pArrowSprite->SetPosition(g_pHero->GetPosition());
					pArrowSprite->SetVelocity(-16, 0);
					g_pGame->AddDungeonSprite(pArrowSprite);
					break;
				case FD_RIGHT:
					pArrowSprite = new Sprite(g_pArrowRightBitmap);
					pArrowSprite->SetNumFrames(9);
					pArrowSprite->SetBoundsAction(BA_DIE);
					pArrowSprite->SetPosition(g_pHero->GetPosition());
					pArrowSprite->SetVelocity(16, 0);
					g_pGame->AddDungeonSprite(pArrowSprite);
					break;
				case FD_UP:
					pArrowSprite = new Sprite(g_pArrowUpBitmap);
					pArrowSprite->SetNumFrames(9);
					pArrowSprite->SetBoundsAction(BA_DIE);
					pArrowSprite->SetPosition(g_pHero->GetPosition());
					pArrowSprite->SetVelocity(0, -16);
					g_pGame->AddDungeonSprite(pArrowSprite);
					break;
				case FD_DOWN:
					pArrowSprite = new Sprite(g_pArrowDownBitmap);
					pArrowSprite->SetNumFrames(9);
					pArrowSprite->SetBoundsAction(BA_DIE);
					pArrowSprite->SetPosition(g_pHero->GetPosition());
					pArrowSprite->SetVelocity(0, 16);
					g_pGame->AddDungeonSprite(pArrowSprite);
					break;
				default:
					break;
				}
				break;
			}
			default:
				break;
			}
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
		}
		break;
	default:
		break;
	}
	ReleaseDC(hWindow, hDC);
}

void ReleaseKeys(WPARAM wParam)
{
	HDC		hDC;
	HWND	hWindow = g_pGame->GetWindow();
	hDC = GetDC(hWindow);

	if (isDungeon || isConstruct)
	{
		switch (wParam)
		{
		case VK_UP:
			g_pHero->SetVelocity(0, 0);
			break;
		case VK_DOWN:
			g_pHero->SetVelocity(0, 0);
			break;
		case VK_RIGHT:
			g_pHero->SetVelocity(0, 0);
			break;
		case VK_LEFT:
			g_pHero->SetVelocity(0, 0);
			break;
		default:
			break;
		}
	}
	ReleaseDC(hWindow, hDC);
}

bool SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee)
{
	Bitmap* pHitter = pSpriteHitter->GetBitmap();
	Bitmap* pHittee = pSpriteHittee->GetBitmap();

	//Check to see if hero collides with weapons in construct
	if (isConstruct)
	{
		//Each collison with a weapon will set that weapon for the hero and then add the pointer of the sprite to
		//the dungeon's sprite vector for update.  Then swap the level.
		if (pHitter == g_pHero->GetBitmap() && pHittee == g_pConstructBoomerangBitmap)
		{
			g_pHero->SetWeapon(WT_BOOMERANG);
			g_pGame->AddDungeonSprite(g_pHero);
			isDungeon = true;
			isConstruct = false;
		}
		if (pHitter == g_pHero->GetBitmap() && pHittee == g_pConstructBowBitmap)
		{
			g_pHero->SetWeapon(WT_BOW);
			g_pGame->AddDungeonSprite(g_pHero);
			isDungeon = true;
			isConstruct = false;
		}
		if (pHitter == g_pHero->GetBitmap() && pHittee == g_pConstructSwordBitmap)
		{
			g_pHero->SetWeapon(WT_SWORD);
			g_pGame->AddDungeonSprite(g_pHero);
			isDungeon = true;
			isConstruct = false;
		}
	}

	if (isDungeon)
	{
		//Check to see if an enemy has ran into the hero
		if (pHitter == g_pEnemyTenticalBitmap && pHittee == g_pHero->GetBitmap())
		{
			//Bounce the enemy off of hero
			pSpriteHitter->SetVelocity(-pSpriteHitter->GetVelocity().x, -pSpriteHitter->GetVelocity().y);
			//if hero's health is more than 1 subtract 1 but if hero's health is 1 then kill the sprite.
			g_pHero->GetHealth() > 1 ? g_pHero->SetHealth(g_pHero->GetHealth() - 1) : pSpriteHittee->Kill(), g_bGameOver = true;
			return true;
		}

		//@TODO:
		/**************** Needs work
		//Check to see if the boomerang has hit an enemy
		if (pHitter == g_pBoomerangBitmap && pHittee == g_pEnemyTenticalBitmap)
		{
			pSpriteHitter->Kill();
			//If enemey's health is more than 1 subtract 1 from it but kill it if it is at 1
			if (pSpriteHittee->GetHealth() > 1)
			{
				pSpriteHitee->SetHealth(pSpriteHitee->GetHealth() - 1);
			}
			else
			{
				pSpriteHitee->Kill();
				//If you kill the enemy play explosion
				Sprite* pSprite = new Sprite(g_pEnemyExplosionBitmap, g_rcEnemeyBounds);
				pSprite->SetNumFrames(9, true);
				pSprite->SetPosition(pSpriteHittee->GetPosition());
				g_pGame->AddDungeonSprite(pSprite);
			}
		}
		//Check to see if an arrow has hit an enemy
		if ((pHitter == g_pArrowLeftBitmap || pHitter == g_pArrowRightBitmap || pHitter == g_pArrowDownBitmap || pHitter == g_pArrowUpBitmap) && pHittee == g_pEnemyTenticalBitmap)
		{
			//Kill the arrow so it doesn't continue on through the enemy
			pSpriteHitter->Kill();

			//If enemey's health is more than 1 subtract 1 from it but kill it if it is at 1
			if (pSpriteHittee->GetHealth() > 1)
			{
				pSpriteHitee->SetHealth(pSpriteHitee->GetHealth() - 1);
			}
			else
			{
				pSpriteHitee->Kill();
				//If you kill the enemy play explosion
				Sprite* pSprite = new Sprite(g_pEnemyExplosionBitmap, g_rcEnemeyBounds);
				pSprite->SetNumFrames(9, true);
				pSprite->SetPosition(pSpriteHittee->GetPosition());
				g_pGame->AddDungeonSprite(pSprite);
			}
		}
		//Check to see if the sword hits the enemy
		if ((pHitter == g_pSwordSwingLeftBitmap || pHitter == g_pSwordSwingRightBitmap || pHitter == g_pSwordSwingDownBitmap || pHitter == g_pSwordSwingUpBitmap) && pHittee == g_pEnemyTenticalBitmap)
		{
			//If enemey's health is more than 1 subtract 1 from it but kill it if it is at 1
			if (pSpriteHittee->GetHealth() > 1)
			{
				pSpriteHitee->SetHealth(pSpriteHitee->GetHealth() - 1);
			}
			else
			{
				pSpriteHitee->Kill();
				//If you kill the enemy play explosion
				Sprite* pSprite = new Sprite(g_pEnemyExplosionBitmap, g_rcEnemeyBounds);
				pSprite->SetNumFrames(9, true);
				pSprite->SetPosition(pSpriteHittee->GetPosition());
				g_pGame->AddDungeonSprite(pSprite);
			}
		}*********************************/
	}	
  	return false;
}

void SpriteDying(Sprite* pSpriteDying)
{
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
    	
  	}
}