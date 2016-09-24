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
18Aug16 Added functions and variables to handle Sprites
21Aug16	Check for Sprite collisions
31Aug16 Added comments for doxygen documentation generation
************************************************************************/
#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <vector>
using namespace std;
#include "Sprite.h"

//-----------------------------------------------------------------
// Windows Function Declarations
//-----------------------------------------------------------------
/// The main loop that is required to start a windows application.  
/// @see Microsoft's MSDN page for further info: https://goo.gl/xF7CdY
int		WINAPI    WinMain(HINSTANCE, HINSTANCE, PSTR, int);

/// Used to processes messages sent to a window. 
/// @see Microsoft's MSDN page for further info: https://goo.gl/nnKqE3
LRESULT CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);


//-----------------------------------------------------------------
// Game Engine Function Declarations
//-----------------------------------------------------------------
/// Used to create a pointer to the GameEngine object and set GameEngine variables.  
/// @param hInstance A handle to an instance. This is the base address of the module in memory.   
bool GameInitialize(HINSTANCE);

/// Creates an offscreen display context for double buffering and loads initial sprites and bitmaps into memory.  
/// @param hWindow The handle to the window  
void GameStart(HWND);

/// Used to delete bitmaps from memory and aim pointers at NULL
void GameEnd();

/// Used to unpause the GameEngine (Resumes updates).  
/// @param hWnd The handle to the window  
void GameActivate(HWND);

/// Used to pause the GameEingine (Stops updates).  
/// @param hWnd The handle to the window
void GameDeactivate(HWND);

/// Used to call Bitmap and Sprite object's Draw functions.
/// @param hDC Handle to the device context
void GamePaint(HDC);

/// Used to check if the game is over, update sprites, copy offscreen device context to display, and calls GamePaint to paint next screen.
void GameCycle();

/// Handles keyboard input. If one of the keys is needed, it is passed to the GameEngine to update sprites or make selections.  
/// @param wParam A message
void HandleKeys(WPARAM);

/// Handles when keyboard input is no longer happening it is passed to the GameEngine  
/// @param wParam A message
void ReleaseKeys(WPARAM);

/// Tests two sprites to determine if they have collided and takes appropriate action.  
/// @param pSpriteHitter A pointer to the sprite that hit the other sprite
/// @param pSpriteHittee A pointer to the sprite that is getting hit by other sprite
bool SpriteCollision(Sprite*, Sprite*);

/// Used to kill a sprite, can play extra animation or sound.  
/// @param pSpriteDying A pointer to the sprite that is dying.  
void SpriteDying(Sprite*);

//-----------------------------------------------------------------
// GameEngine Class
//-----------------------------------------------------------------
/*! \brief The GameEngine class is used to encapsulate Window types, functions, and WinMain.
 *
 *  Creates a static pointer to itself.  Sets up the window class, the window title, icons, 
 *  and dimensions of the screen. Uses a loop to cycle through sprite updates and draw them.  
 *  Sets the timing of the game and keeps status of the game. Handles keyboard input.
 */
class GameEngine
{
protected:
	// Member Variables
	static GameEngine*  m_pGameEngine; ///< The pointer to the GameEngine object
	HINSTANCE           m_hInstance; ///< Stores the handle to the instance of the GameEngine object  
	HWND                m_hWindow; ///< Handle to the window
	TCHAR               m_szWindowClass[32]; ///< Used to store the name of the WindowClass that will register with Task Manager
	TCHAR               m_szTitle[32]; ///< Used to store the name of the title that will be displayed in the title bar of the window
	WORD                m_wIcon; ///< Used to hold the icon that will display on the task bar 
	WORD			 	m_wSmallIcon; ///< Used to hold the icon that will display on the title bar of the window
	int                 m_iWidth; ///< The width in pixels of the game size. NOT the window size.
	int  				m_iHeight; ///< The Height in pixels of the game size. NOT the window size.  
	int                 m_iFrameDelay; ///< Used to slow down the GameEngine so humans can see what is happening on screen
	bool                m_bSleep; ///< Used to hold the status of the GameEngine. To pause or unpause.
	vector<Sprite*>		m_vLoadingSprites; ///< A vector to hold all the sprites. Easier to cycle through a vector to determine Sprites status.
	vector<Sprite*>		m_vConstructSprites; ///< A vector to hold all the sprites. Easier to cycle through a vector to determine Sprites status.
	vector<Sprite*>		m_vDungeonSprites; ///< A vector to hold all the sprites. Easier to cycle through a vector to determine Sprites status.
	DEVMODE				m_devmode; ///< Data structure containing info about the display device. Used to change screen resolution.
	long				m_lResult; ///< Holds the results of the DEVMODE changes.  

	//Helper Method 
	/// Checks the Sprite object that is passed to it to determine if it has collided with another sprite or boundry
	/// @param pTestSprite A pointer of the Sprite to be tested
	bool				CheckSpriteCollision(Sprite*);

public:
	// Constructor(s)/Destructor
	/// Creates the game window and sets the window parameters. Changes the screen resolution to 800x600.
	/// @param hInstance A handle to an instance. This is the base address of the module in memory.
	/// @param szWindowClass The name of the Window class that is registered to Task Manager
	/// @param wIcon The name of the icon to use from resources file. Big icon that will show in task bar.
	/// @param wSmallIcon The name of the icon to use from the resources file. Little icon that will show in the title bar of the window. 
	/// @param iWidth The width of the game in pixels. NOT the window size.
	/// @param iHeight The height of the game in pixels. NOT the window size.
	GameEngine(HINSTANCE, LPTSTR, LPTSTR, WORD, WORD, int, int);

	/// Changes the screen resolution back to what it was originally.  
	virtual ~GameEngine();

	// General Methods
	/// Returns the pointer of the GameEngine.  
	static GameEngine*  GetEngine();

	/// Used to setup the window and put the focus on it.  Tests the results and if everything passes true that was loaded the game continues.  
	/// If something fails, the game will terminate with an error.   
	/// @param iCmdShow Sets how the window should be shown
	/// @see Microsoft's MSDN site for iCmdShow values: https://goo.gl/fIHb60
	bool                Initialize(int);

	/// Routes Windows messages to GameEngine member functions.  If message isn't used by GameEngine, it is passed back to Windows for handling.
	/// @param hWindow The handle to the window 
	/// @param msg The message that is being passed 
	/// @param wParam A parameter for which key is being pressed in keyboard messages
	/// @param lParam Not used. Will be passed back to Windows 
	LRESULT             HandleEvent(HWND, UINT, WPARAM, LPARAM);

	/// Pushes a Sprite object into the Sprite vector  
	/// @param A pointer to the Sprite that will be added to the vector
	/// @see m_vSprites
	void				AddLoadingSprite(Sprite*);

	/// Pushes a Sprite object into the Sprite vector  
	/// @param A pointer to the Sprite that will be added to the vector
	/// @see m_vSprites
	void				AddConstructSprite(Sprite*);

	/// Pushes a Sprite object into the Sprite vector  
	/// @param A pointer to the Sprite that will be added to the vector
	/// @see m_vSprites
	void				AddDungeonSprite(Sprite*);

	/// Transverses the Sprite vector calling each Sprite's Draw function on the loading screen  
	/// @param hDC Handle to the device context.  
	void				DrawLoadingSprites(HDC);

	/// Transverses the Sprite vector calling each Sprite's Draw function in the Construct level  
	/// @param hDC Handle to the device context.  
	void				DrawConstructSprites(HDC);

	/// Transverses the Sprite vector calling each Sprite's Draw function in the dungeon level.  
	/// @param hDC Handle to the device context.  
	void				DrawDungeonSprites(HDC);

	/// Expands the Sprite vector if necessary, updates the sprites positions, checks to see if a sprite was added or dying, and finally checks for collisions.
	void UpdateLoadingSprites();

	/// Expands the Sprite vector if necessary, updates the sprites positions, checks to see if a sprite was added or dying, and finally checks for collisions.
	void UpdateConstructSprites();

	/// Expands the Sprite vector if necessary, updates the sprites positions, checks to see if a sprite was added or dying, and finally checks for collisions.
	void UpdateDungeonSprites();

	/// Transverses the Sprite vector to delete Sprite objects from memory.  
	void				CleanupSprites();

	/// Transverses the Sprite vector to see if the given point is within any of the Sprites 
	/// @param x The X coordinate that will be checked
	/// @param y The Y coordinate that will be checked
	Sprite*				IsPointInSprite(int, int);

	// Accessor Methods
	/// Returns the handle of the instance
	HINSTANCE GetInstance() const; 

	/// Returns the handle of the window
	HWND      GetWindow() const; 

	/// Sets the handle of the window
	/// @param hWnd A handle to the window
	void      SetWindow(HWND); 

	/// returns the string of the game title
	LPTSTR    GetTitle(); 

	/// returns the icon that will be shown in the task bar
	WORD      GetIcon() const; 

	/// returns the little icon that will be shown in the title bar
	WORD      GetSmallIcon() const; 

	/// returns the width of the of the window
	int       GetWidth() const; 

	/// returns the height of the window
	int       GetHeight() const; 

	/// returns the an interger value used to set a frame delay to slow the game down
	int       GetFrameDelay() const; 

	/// Used to set how fast the game should update on the screen
	/// @param iFrameRate This is used to divide 1000ms
	void      SetFrameRate(int); 

	/// Returns true if the game is paused.  
	bool      GetSleep() const; 

	/// If the game is paused, set sleep to true.  
	/// @param bSleep True if the game is paused
	void      SetSleep(bool); 

	/// Sets the screen resolution to 800x600.
	void	  SetScreenResolution();
};