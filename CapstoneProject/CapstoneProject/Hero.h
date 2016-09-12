/************************************************************************
Program:		CapstoneProject
Author:			Randy Rowland
Class:			Hero
Instructor:		Dan Randall
Date:			23 August 2016
Description:	
Input:			
Output:

Compilation instructions:
Usage:
Known bugs/missing features:

Modifications:
Date                Comment
----    ------------------------------------------------
31Aug16 Added comments for doxygen documentation generation
11Sep16 Added the FACINGDIRECTION typedef and GetDirection()
11Sep16 Moved the GetWeapon() function from a public method to a private method
************************************************************************/
#pragma once
#include "Sprite.h"

/// WEAPONTYPE is used to keep track of which weapon the hero has
typedef WORD		WEAPONTYPE;
const WEAPONTYPE	WT_SWORD		= 0,
					WT_BOOMERANG	= 1,
					WT_BOW			= 2;

/// FACINGDIRECTION is used to know which direction the hero is facing so the correct animation plays.
typedef WORD			FACINGDIRECTION;
const FACINGDIRECTION	FD_LEFT		= 0,
						FD_RIGHT	= 1,
						FD_UP		= 2,
						FD_DOWN		= 3;

/*! \brief Extends the Sprite class to give the hero extra variables and methods special to it.
 *
 *  This class extends the Sprite class to give the hero health, weapon choice and movements.
 */
class Hero : public Sprite
{
public:
	/// Creates an enemy sprite using the Bitmap/Sprite constructor
	/// @param pBitmap A pointer to the bitmap image
	/// @param rcBounds A rectangle to contain the movements of the sprite within it
	/// @param baBoundsAction The action that will be taken when the sprite hits the outter edge of the rcBounds rectangle
	/// @see Sprite
	Hero(Bitmap*, RECT&, BOUNDSACTION);

	/// Empty
	~Hero();

	/// Changes the Sprite's velocity to move left on the screen and associated bitmap
	void MoveLeft();

	/// Changes the Sprite's velocity to move right on the screen and associated bitmap
	void MoveRight();

	/// Changes the Sprite's velocity to move up on the screen and associated bitmap
	void MoveUp();

	/// Changes the Sprite's velocity to move down on the screen and associated bitmap
 	void MoveDown();

	/// Sets the weapon type that the hero will use in game play
	/// @param wtWeapon The weapon type to be stored
	/// @see WEAPONTYPE
	void SetWeapon(WEAPONTYPE);



	/// Sets the health of the hero
	/// @param iHealth The health you want the hero to have but can't be more than the m_iHealthMeter
	void SetHealth(int);

	/// Returns how much health the sprite has left before dying
	/// @return m_iHealth as an integer
	int GetHealth() const;

	/// Will change the sprites animation to show weapon usage and will also show it has the hitter in collision detection.  
	/// This will make sure that the hero sprite doesn't lose health or die while weapon is in use.  
	void UseWeapon();

	/// Used to increase the health meter and refill the Sprite to full health.  
	void IncreaseHealthMeter();

private:
	int m_iHealth; ///< The health of the Hero sprite.  Will allow it to collide more before dying
	int m_iHealthMeter; ///< The health meter will show the player how much health the Hero sprite has
	WEAPONTYPE m_wtWeapon; ///< Used to store which weapon the Hero sprite has 
	FACINGDIRECTION m_fdDirection; ///< Used to store which direction the Hero is facing

	/// Returns which weapon the hero is currently holding
	/// @return m_wtWeapon as a WORD
	/// @see WEAPONTYPE
	WEAPONTYPE GetWeapon() const;

	/// Returns the direction in which the hero is facing
	/// @return m_fdDirection as a WORD
	/// @see FACINGDIRECTION
	FACINGDIRECTION GetDirection() const;
};

