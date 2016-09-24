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
16Sep16	Completed the MoveRunAway function.
************************************************************************/
#include "EnemyBoss.h"
#include <stdlib.h>

EnemyBoss::EnemyBoss(Bitmap* pBitmap, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP) : Sprite(pBitmap, rcBounds, baBoundsAction), m_iHealth(15)
{
}


EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::SetHealth(int iHealth)
{
	m_iHealth = iHealth;
}

int EnemyBoss::GetHealth() const
{
	return m_iHealth;
}

void EnemyBoss::MoveRandomly(int x, int y)
{
	this->SetPosition(rand() % x, rand() % y);
	this->SetVelocity((rand() % 5) - 2, (rand() % 5) + 3);
}


void EnemyBoss::MoveChase(Sprite *pSpriteToChase)
{
	
}

void EnemyBoss::MoveRunAway(Sprite *pAvoidSprite)
{

	// Obtain the enemy's position
	RECT rcEnemy, rcHero;
	rcEnemy = this->GetPosition();

	int iXCollision = 500, iYCollision = 400, iXYCollision = 900;
	
	// Get the hero's position
	rcHero = pAvoidSprite->GetPosition();

	// Calculate the minimum XY collision distance
	int iXCollisionDist = (rcEnemy.left + (rcEnemy.right - rcEnemy.left) / 2) -	(rcHero.left + (rcHero.right - rcHero.left) / 2);
	int iYCollisionDist = (rcEnemy.top + (rcEnemy.bottom - rcEnemy.top) / 2) - (rcHero.top + (rcHero.bottom - rcHero.top) / 2);
	if ((abs(iXCollisionDist) < abs(iXCollision)) || (abs(iYCollisionDist) < abs(iYCollision)))
		if ((abs(iXCollisionDist) + abs(iYCollisionDist)) < iXYCollision)
		{
			iXYCollision = abs(iXCollision) + abs(iYCollision);
			iXCollision = iXCollisionDist;
			iYCollision = iYCollisionDist;
		}

	// Move to dodge the hero, if necessary
	POINT ptVelocity;
	ptVelocity = this->GetVelocity();
	if (abs(iXCollision) < 60)
	{
		// Adjust the X velocity
		if (iXCollision < 0)
			ptVelocity.x = max(ptVelocity.x - 1, -8);
		else
			ptVelocity.x = min(ptVelocity.x + 1, 8);
	}
	if (abs(iYCollision) < 60)
	{
		// Adjust the Y velocity
		if (iYCollision < 0)
			ptVelocity.y = max(ptVelocity.y - 1, -8);
		else
			ptVelocity.y = min(ptVelocity.y + 1, 8);
	}

	// Update the enemy to the new position
	this->SetVelocity(ptVelocity);
}
