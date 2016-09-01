//! Uses a Bitmap to create a moveable Sprite.
/************************************************************************
Program:		CapstoneProject
Author:			Randy Rowland
Class:			Bitmap
Instructor:		Dan Randall
Date:			22 July 2016
Description:	Takes a bitmap and turns it into a sprite with position,
				velocity, z-order, bounding rect, collision, and  visiblity
Input:			Bitmap
Output:

Compilation instructions:
Usage:
Known bugs/missing features:

Modifications:
Date                Comment
----    ------------------------------------------------
22Jul16	Added const to getter functions. Removed implementation.
31Aug16 Added comments for doxygen documentation generation.
************************************************************************/
#pragma once
#include <Windows.h>
#include "Bitmap.h"

/// SPRITEACTION is the state of the sprite.
typedef WORD		SPRITEACTION;
const SPRITEACTION	SA_NONE			= 0x0000L, ///< This will be used for NPCs.
					SA_KILL			= 0x0001L, ///< When a sprite needs to be removed.
					SA_ADDSPRITE	= 0x0002L; ///< When a sprite needs to be created.

/// BOUNDSACTION is what happens when a sprite hits its boundry for game play.
typedef WORD		BOUNDSACTION;
const BOUNDSACTION	BA_STOP		= 0, ///< When a sprite hits the end of its boundry it will come to a stop.
					BA_WRAP		= 1, ///< When a sprite hits the end of its boundry it will wrap to the other side of the boundry.
					BA_BOUNCE	= 2, ///< When a sprite hits the end of its boundry it will bounce back off that end in the opposite direction.
					BA_DIE		= 3; ///< When the boundry is hit, this will kill the sprite.

class Sprite
{
public:
    /// Creates a generic sprite using the Bitmap constructor.
    /// @param pBitmap A pointer to the bitmap object
    /// @see Bitmap
	Sprite(Bitmap*);
    
    /// Creates a sprite using the Bitmap constructor but adds additional attributes.
    /// @param pBitmap A pointer to the bitmap object
    /// @param rcBounds A rectangle to contain the movements of the sprite within it
    /// @param baBoundsAction The action that will be taken when the sprite hits the outter edge of the rcBounds rectangle. Default is for the sprite to stop.
    /// @see Bitmap
	Sprite(Bitmap*, RECT&, BOUNDSACTION baBoundsAction = BA_STOP);
    
    /// Creates a sprite using the Bitmap constructor but adds additional attributes.
    /// @param pBitmap A pointer to the bitmap object
    /// @param ptPosition Sets a point of where the sprite will be positioned on the screen
    /// @param ptVelocity Sets the velocity of the sprite to move
    /// @param iZOrder Sets what layer the sprite needs to be if there will be over lapping of sprites
    /// @param rcBounds A rectangle to contain the movements of the sprite within it
    /// @param baBoundsAction The action that will be taken when the sprite hits the outter edge of the rcBounds rectangle. Default is for the sprite to stop.
    /// @see Bitmap
	Sprite(Bitmap*, POINT, POINT, int, RECT&, BOUNDSACTION baBoundsAction = BA_STOP);
    
    /// Empty destructor, nothing special here.
	virtual ~Sprite();
    
    /// Determines the current status of the sprite and takes action on what needs to be done next.
    /// If the sprite is dying, it will KILL the sprite.  Will check the BOUNDSACTION and update velocity, bounce it, or wrap it.
    /// @see SPRITEACTION
    /// @see BOUNDSACTION 
	virtual SPRITEACTION Update();
    
    /// A pointer to this sprite object.
	Sprite *AddSprite;
    
    /// Checks the hidden status and current frame, then draw appropriate image to the screen.
    /// @param hDC The handle to the display context of where to draw the image. 
	void Draw(HDC);
    
    /// Determines if a given point, in the terms of X and Y, are inside a specified area.
    /// @param x coordinate X
    /// @param y coordinate Y
	bool IsPointInside(int, int);
	bool TestCollision(Sprite*);
	void Kill();
	Bitmap *GetBitmap() const;
	void SetNumFrames(int, bool bOneCycle = false);
	void SetFrameDelay(int);
	RECT &GetPosition();
	void SetPosition(int, int);
	void SetPosition(POINT);
	void SetPosition(RECT&);
	void OffsetPosition(int, int);
	RECT &GetCollision();
	POINT GetVelocity();
	void SetVelocity(int, int);
	void SetVelocity(POINT);
	bool GetZorder() const;
	void SetZorder(int);
	void SetBounds(RECT&);
	void SetBoundsAction(BOUNDSACTION);
	bool IsHidden() const;
    
    /// Used to show or hide the sprite.
    /// @param bHidden If true, the sprite will not display on the screen
	void SetHidden(bool);
    
    /// Returns the width of the bitmap/sprite.
	int GetWidth() const;
    
    /// Returns the height of the bitmap/sprite.
	int GetHeight() const;
protected:
	Bitmap			*m_pBitmap; ///< Pointer to the bitmap used to create the sprite.
	int				m_iNumFrames; ///< How many frames are in the bitmap to create animation for the sprite.
	int				m_iCurFrame; ///< Used to specify the current frame of the bitmap when animation is used.
	int				m_iFrameDelay; ///< How long you the game needs to wait before changing to the next frame of animation.
	int				m_iFrameTrigger; ///< A counter that is compated to the delay that will trigger the next frame.
	int				m_iZorder; ///< Used if you have to layer bitmaps or spirtes on top of each other.
	POINT			m_ptVelocity; ///< Used in caluclations to move the sprite around the screen.
	RECT			m_rcPosition; ///< The rectangle around the bitmap that is the position of the sprite.
	RECT			m_rcCollision; ///< A slightly smaller rectangle used for in collision detection calculations.
	RECT			m_rcBounds;  ///< The rectangle that is usually larger than the sprite that will contain the movements of the sprite within this rectangle.
	BOUNDSACTION	m_baBoundsAction; ///< Holds the current BOUNDSACTION assigned to the sprite.
	bool			m_bHidden; ///< Used to show or hide the sprite on the screen.
	bool			m_bDying; ///< Used to indicate if the sprite is dying.
	bool			m_bOneCycle; ///< Used to state if the sprites animation will run once or loop.

    /// Used to change from the current frame of animation to the next frame.
	void UpdateFrame();
    
    /// Calculates the collision rectangle to be one-sixth smaller than the position rectangle using the X and Y dimensions of the sprite.
	virtual void CalcCollisionRect();
};