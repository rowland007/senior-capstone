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

/*! \brief Takes a bitmap and turns it into a sprite with position, velocity, z-order, bounding rect, collision, and  visiblity.
 *
 *  This class depends on Bitmap to function. Does not extend Bitmap. There are three different types of constructors used to create 
 *  a sprite.  This class controls how the sprite moves, how the sprite will interact with its boundries.  It will either stop, wrap,
 *  bounce, or die at the boundry.  There are also three SPRITEACTIONs that set what the sprite is doing.
 */
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
    
    /// Returns true if the Sprite runs into its boundry rectangle.
    /// @param pTestSprite pointer to the sprite that needs to be tested
	bool TestCollision(Sprite*);
    
    /// Sets the sprite's member variable to dying.
	void Kill();
    
    /// Pointer to the Bitmap of the sprite
    /// @see Bitmap
	Bitmap *GetBitmap() const;
    
    /// Used to set how many frames to use for sprite animation.
    /// @param iNumFrames how many frames there are
    /// @param bOneCycle Used to determine if the animation should loop. Default is to loop.
	void SetNumFrames(int, bool bOneCycle = false);
    
    /// How long the sprite will stay on one frame before switching to the next frame.
	void SetFrameDelay(int);

	/// Used to change the Bitmap image that the sprite uses.
	/// @param pBitmap The pointer to the bitmap
	/// @see Bitmap
	void SetBitmap(Bitmap*);
    
    /// Returns the position of the sprite by using a rectangle around the frame of the bitmap
	RECT &GetPosition();
    
    /// Sets the position of the sprite on the screen using X and Y coordinates.
    /// @param X The X coordinate
    /// @param Y The Y coordinate
    void SetPosition(int, int);
	
    /// Sets the position of the sprite on the screen using the type POINT.
    /// @param ptPosition The position of the sprite using a POINT type.
    void SetPosition(POINT);
    
    /// Sets the position of the sprite on the screen using a rectangle
    /// @param rcPosition The positions of the rectangle
	void SetPosition(RECT&);

    /// Used to offset the position of a sprite by using X and Y pixels
    /// @param X Number of X pixels used to offset sprite horizontally
    /// @param Y Number of Y pixels used to offset sprite vertically     
	void OffsetPosition(int, int);
    
    /// Returns the smaller collision rectangle that is around the sprite
	RECT &GetCollision();
    
    /// Returns the velocity of the sprite in the terms of a POINT.
	POINT GetVelocity();
    
    /// Sets the velocity of the spirte by using X and Y pixels
    /// @param X The number of pixels you need the sprite to move horizontally every update
    /// @param Y The number of pixels you need the sprite to move vertically every update
	void SetVelocity(int, int);
    
    /// Sets the velocity of the sprite by using a POINT type
    /// @param ptVelocity 
	void SetVelocity(POINT);
    
    /// Returns if the sprite has a Z-order that is used in layering
	bool GetZorder() const;
    
    /// Sets the Z-order of the sprite in layered sprites
    /// @param iZOrder A number used to set the which layer you want the sprite on
	void SetZorder(int);
    
    /// Sets a rectangle that is used to allow the movement of the sprite within the rectangle
    /// @param rcBounds The rectangle that will be set around the sprite 
	void SetBounds(RECT&);
    
    /// Sets the bounds action of the sprite. Sprite will either stop, bounce back, or wrap to the other side of the screen.
    /// @param baBoundsAction The action you want to set to the sprite
    /// @see BOUNDSACTION
	void SetBoundsAction(BOUNDSACTION);
    
    /// Returns true if the spirte is hidden from the screen
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