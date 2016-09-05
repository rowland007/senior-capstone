/************************************************************************
Program:		CapstoneProject
Author:			Michael Morrison
Class:			GameEngine
Instructor:		Dan Randall
Date:			5 July 2016
Description:	GameEngine hides all the Windows specific code so you can
				focus on the game code.  Code is used from the book: 
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
20Jul16	Engine now has the game window open maximized. Added keyboard support.
2Aug16	Changed BOOL to bool, TRUE to true, and FALSE to false.
3Aug16	Moved implementation of general and accessor methods from GameEngine.h
18Aug16	Added functions and variables to handle Sprites
21Aug16	Check for sprite collisions
24Aug16	Added screen resolution mod to set resolution to 800x600
25Aug16 Temp disabled screen resolution mod for debugging - no issue with mod
************************************************************************/
#include "GameEngine.h"

//-----------------------------------------------------------------
// Static Variable Initialization
//-----------------------------------------------------------------
GameEngine *GameEngine::m_pGameEngine = NULL;

//-----------------------------------------------------------------
// Windows Functions
//-----------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	MSG         msg;
	static int  iTickTrigger = 0;
	int         iTickCount;

	if (GameInitialize(hInstance))
	{
		// Initialize the game engine
		if (!GameEngine::GetEngine()->Initialize(iCmdShow))
			return false;

		// Enter the main message loop
		while (true)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				// Process the message
				if (msg.message == WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// Make sure the game engine isn't sleeping
				if (!GameEngine::GetEngine()->GetSleep())
				{
					// Check the tick count to see if a game cycle has elapsed
					iTickCount = GetTickCount();
					if (iTickCount > iTickTrigger)
					{
						iTickTrigger = iTickCount + GameEngine::GetEngine()->GetFrameDelay();
						GameCycle();
					}
				}
			}
		}
		return (int)msg.wParam;
	}

	// End the game
	GameEnd();

	return true;
}

LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Route all Windows messages to the game engine
	return GameEngine::GetEngine()->HandleEvent(hWindow, msg, wParam, lParam);
}

bool GameEngine::CheckSpriteCollision(Sprite * pTestSprite)
{
	// See if the sprite has collided with any other sprites
	vector<Sprite*>::iterator siSprite;
	for (siSprite = m_vDungeonSprites.begin(); siSprite != m_vDungeonSprites.end(); siSprite++)
	{
		// Make sure not to check for collision with itself
		if (pTestSprite == (*siSprite))
			continue;

		// Test the collision
		if (pTestSprite->TestCollision(*siSprite))
			// Collision detected
			return SpriteCollision((*siSprite), pTestSprite);
	}
	for (siSprite = m_vConstructSprites.begin(); siSprite != m_vConstructSprites.end(); siSprite++)
	{
		// Make sure not to check for collision with itself
		if (pTestSprite == (*siSprite))
			continue;

		// Test the collision
		if (pTestSprite->TestCollision(*siSprite))
			// Collision detected
			return SpriteCollision((*siSprite), pTestSprite);
	}
	for (siSprite = m_vLoadingSprites.begin(); siSprite != m_vLoadingSprites.end(); siSprite++)
	{
		// Make sure not to check for collision with itself
		if (pTestSprite == (*siSprite))
			continue;

		// Test the collision
		if (pTestSprite->TestCollision(*siSprite))
			// Collision detected
			return SpriteCollision((*siSprite), pTestSprite);
	}

	// No collision
	return FALSE;
}

//-----------------------------------------------------------------
// GameEngine Constructor(s)/Destructor
//-----------------------------------------------------------------
GameEngine::GameEngine(HINSTANCE hInstance, LPTSTR szWindowClass, LPTSTR szTitle, WORD wIcon, WORD wSmallIcon, int iWidth = 800, int iHeight = 640)
{
	// Set the member variables for the game engine
	m_pGameEngine = this;
	m_hInstance = hInstance;
	m_hWindow = NULL;
	if (lstrlen(szWindowClass) > 0)
		lstrcpy(m_szWindowClass, szWindowClass);
	if (lstrlen(szTitle) > 0)
		lstrcpy(m_szTitle, szTitle);
	m_wIcon = wIcon;
	m_wSmallIcon = wSmallIcon;
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_iFrameDelay = 50;   // 20 FPS default
	m_bSleep = true;
	SetScreenResolution();
}

GameEngine::~GameEngine()
{
	ChangeDisplaySettings(NULL, 0);
}

GameEngine* GameEngine::GetEngine()
{
	return m_pGameEngine;
}
//-----------------------------------------------------------------
// Game Engine General Methods
//-----------------------------------------------------------------
bool GameEngine::Initialize(int iCmdShow)
{
	WNDCLASSEX    wndclass;

	// Create the window class for the main window
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = m_hInstance;
	wndclass.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(GetIcon()));
	wndclass.hIconSm = LoadIcon(m_hInstance, MAKEINTRESOURCE(GetSmallIcon()));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = m_szWindowClass;

	// Register the window class
	if (!RegisterClassEx(&wndclass))
		return false;

	// Calculate the window size and position based upon the game size
	int iWindowWidth = m_iWidth + GetSystemMetrics(SM_CXFIXEDFRAME) * 2,
		iWindowHeight = m_iHeight + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 +
		GetSystemMetrics(SM_CYCAPTION);
	if (wndclass.lpszMenuName != NULL)
		iWindowHeight += GetSystemMetrics(SM_CYMENU);
	int iXWindowPos = (GetSystemMetrics(SM_CXSCREEN) - iWindowWidth) / 2,
		iYWindowPos = (GetSystemMetrics(SM_CYSCREEN) - iWindowHeight) / 2;

	// Create the window
	m_hWindow = CreateWindow(m_szWindowClass, m_szTitle, WS_MAXIMIZE, iXWindowPos, iYWindowPos, iWindowWidth,
		iWindowHeight, NULL, NULL, m_hInstance, NULL);
	if (!m_hWindow)
		return false;

	// Show and update the window
	ShowWindow(m_hWindow, SW_SHOWMAXIMIZED);
	UpdateWindow(m_hWindow);

	return true;
}

LRESULT GameEngine::HandleEvent(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Route Windows messages to game engine member functions
	switch (msg)
	{
	case WM_CREATE:
		// Set the game window and start the game
		SetWindow(hWindow);
		GameStart(hWindow);
		return 0;

	case WM_SETFOCUS:
		// Activate the game and update the Sleep status
		GameActivate(hWindow);
		SetSleep(false);
		return 0;

	case WM_KILLFOCUS:
		// Deactivate the game and update the Sleep status
		GameDeactivate(hWindow);
		SetSleep(true);
		return 0;

	case WM_PAINT:
		HDC         hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWindow, &ps);

		// Paint the game
		GamePaint(hDC);

		EndPaint(hWindow, &ps);
		return 0;

	case WM_DESTROY:
		// End the game and exit the application
		GameEnd();
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		HandleKeys(wParam);
		return 0;
	}
	return DefWindowProc(hWindow, msg, wParam, lParam);
}

HINSTANCE GameEngine::GetInstance() const
{
	return m_hInstance;
}

HWND GameEngine::GetWindow() const 
{ 
	return m_hWindow; 
}

void GameEngine::SetWindow(HWND hWindow) 
{ 
	m_hWindow = hWindow; 
}

LPTSTR GameEngine::GetTitle() 
{ 
	return m_szTitle; 
}

WORD GameEngine::GetIcon() const 
{ 
	return m_wIcon; 
}

WORD GameEngine::GetSmallIcon() const 
{ 
	return m_wSmallIcon; 
}

int GameEngine::GetWidth() const 
{ 
	return m_iWidth; 
}

int GameEngine::GetHeight() const 
{ 
	return m_iHeight; 
}

int GameEngine::GetFrameDelay() const 
{ 
	return m_iFrameDelay; 
}

void GameEngine::SetFrameRate(int iFrameRate) 
{
	m_iFrameDelay = 1000 / iFrameRate;
}

bool GameEngine::GetSleep() const 
{ 
	return m_bSleep; 
}

void GameEngine::SetSleep(bool bSleep) 
{ 
	m_bSleep = bSleep; 
}
void GameEngine::SetScreenResolution()
{
	m_devmode.dmPelsWidth = 800;
	m_devmode.dmPelsHeight = 600;
	m_devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	m_devmode.dmSize = sizeof(DEVMODE);

	m_lResult = ChangeDisplaySettings(&m_devmode, 0);
}

void GameEngine::AddLoadingSprite(Sprite* pSprite)
{
  // Add a sprite to the sprite vector
  if (pSprite != NULL)
  {
    // See if there are sprites already in the sprite vector
    if (m_vLoadingSprites.size() > 0)
    {
      // Find a spot in the sprite vector to insert the sprite by its z-order
      vector<Sprite*>::iterator siSprite;
      for (siSprite = m_vLoadingSprites.begin(); siSprite != m_vLoadingSprites.end(); siSprite++)
        if (pSprite->GetZorder() < (*siSprite)->GetZorder())
        {
          // Insert the sprite into the sprite vector
          m_vLoadingSprites.insert(siSprite, pSprite);
          return;
        }
    }

    // The sprite's z-order is highest, so add it to the end of the vector
    m_vLoadingSprites.push_back(pSprite);
  }
}

void GameEngine::AddConstructSprite(Sprite* pSprite)
{
	// Add a sprite to the sprite vector
	if (pSprite != NULL)
	{
		// See if there are sprites already in the sprite vector
		if (m_vConstructSprites.size() > 0)
		{
			// Find a spot in the sprite vector to insert the sprite by its z-order
			vector<Sprite*>::iterator siSprite;
			for (siSprite = m_vConstructSprites.begin(); siSprite != m_vConstructSprites.end(); siSprite++)
				if (pSprite->GetZorder() < (*siSprite)->GetZorder())
				{
					// Insert the sprite into the sprite vector
					m_vConstructSprites.insert(siSprite, pSprite);
					return;
				}
		}

		// The sprite's z-order is highest, so add it to the end of the vector
		m_vConstructSprites.push_back(pSprite);
	}
}

void GameEngine::AddDungeonSprite(Sprite* pSprite)
{
	// Add a sprite to the sprite vector
	if (pSprite != NULL)
	{
		// See if there are sprites already in the sprite vector
		if (m_vDungeonSprites.size() > 0)
		{
			// Find a spot in the sprite vector to insert the sprite by its z-order
			vector<Sprite*>::iterator siSprite;
			for (siSprite = m_vDungeonSprites.begin(); siSprite != m_vDungeonSprites.end(); siSprite++)
				if (pSprite->GetZorder() < (*siSprite)->GetZorder())
				{
					// Insert the sprite into the sprite vector
					m_vDungeonSprites.insert(siSprite, pSprite);
					return;
				}
		}

		// The sprite's z-order is highest, so add it to the end of the vector
		m_vDungeonSprites.push_back(pSprite);
	}
}

void GameEngine::DrawLoadingSprites(HDC hDC)
{
  // Draw the sprites in the sprite vector
  vector<Sprite*>::iterator siSprite;
  for (siSprite = m_vLoadingSprites.begin(); siSprite != m_vLoadingSprites.end(); siSprite++)
    (*siSprite)->Draw(hDC);
}

void GameEngine::DrawConstructSprites(HDC hDC)
{
	// Draw the sprites in the sprite vector
	vector<Sprite*>::iterator siSprite;
	for (siSprite = m_vConstructSprites.begin(); siSprite != m_vConstructSprites.end(); siSprite++)
		(*siSprite)->Draw(hDC);
}

void GameEngine::DrawDungeonSprites(HDC hDC)
{
	// Draw the sprites in the sprite vector
	vector<Sprite*>::iterator siSprite;
	for (siSprite = m_vDungeonSprites.begin(); siSprite != m_vDungeonSprites.end(); siSprite++)
		(*siSprite)->Draw(hDC);
}

void GameEngine::UpdateLoadingSprites()
{
  // Expand the capacity of the sprite vector, if necessary
  if (m_vLoadingSprites.size() >= (m_vLoadingSprites.capacity() / 2))
    m_vLoadingSprites.reserve(m_vLoadingSprites.capacity() * 2);

  // Update the sprites in the sprite vector
  RECT          rcOldSpritePos;
  SPRITEACTION  saSpriteAction;
  vector<Sprite*>::iterator siSprite;
  for (siSprite = m_vLoadingSprites.begin(); siSprite != m_vLoadingSprites.end(); siSprite++)
  {
    // Save the old sprite position in case we need to restore it
    rcOldSpritePos = (*siSprite)->GetPosition();

    // Update the sprite
    saSpriteAction = (*siSprite)->Update();

    // Handle the SA_ADDSPRITE sprite action
    if (saSpriteAction & SA_ADDSPRITE)
      // Allow the sprite to add its sprite
      //AddSprite((*siSprite)->AddSprite());

    // Handle the SA_KILL sprite action
    if (saSpriteAction & SA_KILL)
    {
      // Notify the game that the sprite is dying
      SpriteDying(*siSprite);

      // Kill the sprite
      delete (*siSprite);
      m_vLoadingSprites.erase(siSprite);
      siSprite--;
      continue;
    }

    // See if the sprite collided with any others
    if (CheckSpriteCollision(*siSprite))
      // Restore the old sprite position
      (*siSprite)->SetPosition(rcOldSpritePos);
  }
}

void GameEngine::UpdateConstructSprites()
{
	// Expand the capacity of the sprite vector, if necessary
	if (m_vConstructSprites.size() >= (m_vConstructSprites.capacity() / 2))
		m_vConstructSprites.reserve(m_vConstructSprites.capacity() * 2);

	// Update the sprites in the sprite vector
	RECT          rcOldSpritePos;
	SPRITEACTION  saSpriteAction;
	vector<Sprite*>::iterator siSprite;
	for (siSprite = m_vConstructSprites.begin(); siSprite != m_vConstructSprites.end(); siSprite++)
	{
		// Save the old sprite position in case we need to restore it
		rcOldSpritePos = (*siSprite)->GetPosition();

		// Update the sprite
		saSpriteAction = (*siSprite)->Update();

		// Handle the SA_ADDSPRITE sprite action
		if (saSpriteAction & SA_ADDSPRITE)
			// Allow the sprite to add its sprite
			//AddSprite((*siSprite)->AddSprite());

			// Handle the SA_KILL sprite action
			if (saSpriteAction & SA_KILL)
			{
				// Notify the game that the sprite is dying
				SpriteDying(*siSprite);

				// Kill the sprite
				delete (*siSprite);
				m_vConstructSprites.erase(siSprite);
				siSprite--;
				continue;
			}

		// See if the sprite collided with any others
		if (CheckSpriteCollision(*siSprite))
			// Restore the old sprite position
			(*siSprite)->SetPosition(rcOldSpritePos);
	}
}

void GameEngine::UpdateDungeonSprites()
{
	// Expand the capacity of the sprite vector, if necessary
	if (m_vDungeonSprites.size() >= (m_vDungeonSprites.capacity() / 2))
		m_vDungeonSprites.reserve(m_vDungeonSprites.capacity() * 2);

	// Update the sprites in the sprite vector
	RECT          rcOldSpritePos;
	SPRITEACTION  saSpriteAction;
	vector<Sprite*>::iterator siSprite;
	for (siSprite = m_vDungeonSprites.begin(); siSprite != m_vDungeonSprites.end(); siSprite++)
	{
		// Save the old sprite position in case we need to restore it
		rcOldSpritePos = (*siSprite)->GetPosition();

		// Update the sprite
		saSpriteAction = (*siSprite)->Update();

		// Handle the SA_ADDSPRITE sprite action
		if (saSpriteAction & SA_ADDSPRITE)
			// Allow the sprite to add its sprite
			//AddSprite((*siSprite)->AddSprite());

			// Handle the SA_KILL sprite action
			if (saSpriteAction & SA_KILL)
			{
				// Notify the game that the sprite is dying
				SpriteDying(*siSprite);

				// Kill the sprite
				delete (*siSprite);
				m_vDungeonSprites.erase(siSprite);
				siSprite--;
				continue;
			}

		// See if the sprite collided with any others
		if (CheckSpriteCollision(*siSprite))
			// Restore the old sprite position
			(*siSprite)->SetPosition(rcOldSpritePos);
	}
}
void GameEngine::CleanupSprites()
{
  // Delete and remove the sprites in the sprite vector
  vector<Sprite*>::iterator siSprite;
  for (siSprite = m_vLoadingSprites.begin(); siSprite != m_vLoadingSprites.end(); siSprite++)
  {
    delete (*siSprite);
    m_vLoadingSprites.erase(siSprite);
    siSprite--;
  }
  for (siSprite = m_vConstructSprites.begin(); siSprite != m_vConstructSprites.end(); siSprite++)
  {
	  delete (*siSprite);
	  m_vConstructSprites.erase(siSprite);
	  siSprite--;
  }
  for (siSprite = m_vDungeonSprites.begin(); siSprite != m_vDungeonSprites.end(); siSprite++)
  {
	  delete (*siSprite);
	  m_vDungeonSprites.erase(siSprite);
	  siSprite--;
  }
}

Sprite* GameEngine::IsPointInSprite(int x, int y)
{
  // See if the point is in a sprite in the sprite vector
  vector<Sprite*>::reverse_iterator siSprite;
  for (siSprite = m_vDungeonSprites.rbegin(); siSprite != m_vDungeonSprites.rend(); siSprite++)
    if (!(*siSprite)->IsHidden() && (*siSprite)->IsPointInside(x, y))
      return (*siSprite);

  for (siSprite = m_vConstructSprites.rbegin(); siSprite != m_vConstructSprites.rend(); siSprite++)
	  if (!(*siSprite)->IsHidden() && (*siSprite)->IsPointInside(x, y))
		  return (*siSprite);

  for (siSprite = m_vLoadingSprites.rbegin(); siSprite != m_vLoadingSprites.rend(); siSprite++)
	  if (!(*siSprite)->IsHidden() && (*siSprite)->IsPointInside(x, y))
		  return (*siSprite);

  // The point is not in a sprite
  return NULL;
}