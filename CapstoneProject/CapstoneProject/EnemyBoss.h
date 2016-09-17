
/************************************************************************
Program:		CapstoneProject
Author:			Randall Rowland
Class:			EnemyBoss
Instructor:		Dan Randall
Date:			18 July 2016
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
16Sep16 Added params to MoveRandomly and MoveRunAway methods 
************************************************************************/
#pragma once
#include "Sprite.h"
#include "Hero.h"

/*! \brief Extends the Sprite class to give enemies extra variables and methods special to them.
 *
 *  This class extends the Sprite class to give enemies health and movements.
 */
class EnemyBoss : public Sprite
{
public:
	/// Creates an enemy sprite using the Bitmap/Sprite constructor
	/// @param pBitmap A pointer to the bitmap image
	/// @param rcBounds A rectangle to contain the movements of the sprite within it
	/// @param baBoundsAction The action that will be taken when the sprite hits the outter edge of the rcBounds rectangle
	/// @see Sprite
	EnemyBoss(Bitmap*, RECT&, BOUNDSACTION);

	/// Empty
	~EnemyBoss();

	/// Sets the health of the enemy so it can take multiple collisions before dying
	/// @param iHealth The health in which you want the enemy to have
	void SetHealth(int);

	/// Gets the how much health is left of the enemy
	int GetHealth() const;

	/// Will have the sprite move randomly on the screen
	/// @param
	/// @param
	void MoveRandomly(int, int);

	/// Will have the sprite chase the Hero sprite
	void MoveChase();

	/// Will have the sprite avoid the Hero sprite 
	/// @param
	void MoveRunAway(Hero*);

private:
	int m_iHealth; ///< Stores the health of the enemy sprite
};

