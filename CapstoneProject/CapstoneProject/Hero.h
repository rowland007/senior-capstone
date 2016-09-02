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
************************************************************************/
#pragma once
#include "Sprite.h"

/// WEAPONTYPE is used to keep track of which weapon the hero has
typedef WORD		WEAPONTYPE;
const WEAPONTYPE	WT_SWORD = 0,
					WT_BOOMERANG = 1,
					WT_BOW = 2;

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

	/// Changes the Sprite's velocity to move left on the screen
	void MoveLeft();

	/// Changes the Sprite's velocity to move right on the screen
	void MoveRight();

	/// Changes the Sprite's velocity to move up on the screen
	void MoveUp();

	/// Changes the Sprite's velocity to move down on the screen
	void MoveDown();

	/// Sets the weapon type that the hero will use in game play
	/// @param wtWeapon The weapon type to be stored
	/// @see WEAPONTYPE
	void SetWeapon(WEAPONTYPE);

	/// Returns which weapon the hero is currently holding
	/// @see WEAPONTYPE
	WEAPONTYPE GetWeapon() const;

	/// Sets the health of the hero
	/// @param iHealth The health you want the hero to have but can't be more than the m_iHealthMeter
	void SetHealth(int);

	/// Returns how much health the sprite has left before dying
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
};

