/************************************************************************
Program:		CapstoneProject
Author:			Randy Rowland
Class:			Hero
Instructor:		Dan Randall
Date:			23 August 2016
Description:
Input:			HeroWalking is 192x24 with 8 frames. Each frame is 24x24.
				HeroSword is 384x27 with 12 frames. Each frame is 32x27.
				HeroBoomerang is 64x24 with 2 frames. Each frame is 32x24.
				HeroBow is 96x24 with 3 frames. Each frame is 32x24.
				HeroDamage is 56x24.
				HeroDying is 240x24 with 10 frames. Each frame is 24x24.
				SwordSwing is 864x40 with 12 frames. Each frame is 72x40.
				Boomerang is 64x16 with 4 frames. Each frame is 16x16.
				Arrow is 144x16 with 9 frames. Each frame is 16x16.
Output:

Compilation instructions:
Usage:
Known bugs/missing features:

Modifications:
Date                Comment
----    ------------------------------------------------
10Sep16	Made global pointers for all the bitmaps the hero class will use
11Sep16 Created a bunch of case statements used to change animation dependent on the direction and weapon.
12Sep16	GetWeapon() now returns address of a weapon sprite instead of being void
************************************************************************/
#include "Hero.h"
#include "Resource.h"

/// All the bitmaps that are used by the Hero



Hero::Hero(Bitmap* pBitmap, RECT& rcBounds,	BOUNDSACTION baBoundsAction = BA_STOP) : Sprite(pBitmap, rcBounds, baBoundsAction), m_iHealth(3), m_iHealthMeter(3)
{
}


Hero::~Hero()
{
}

void Hero::MoveLeft()
{
	// old implementation idea - has been moved
}

void Hero::MoveRight()
{
	// old implementation idea - has been moved
}

void Hero::MoveUp()
{
	// old implementation idea - has been moved
}

void Hero::MoveDown()
{
	// old implementation idea - has been moved
}

void Hero::SetWeapon(WEAPONTYPE wtWeapon)
{
	m_wtWeapon = wtWeapon;
}

WEAPONTYPE Hero::GetWeapon() const
{
	return WEAPONTYPE();
}

FACINGDIRECTION Hero::GetDirection() const
{
	return m_fdDirection;
}

void Hero::SetDirection(FACINGDIRECTION fdDirection)
{
	m_fdDirection = fdDirection;
}

void Hero::SetHealth(int iHealth)
{
	m_iHealth = iHealth;
}

int Hero::GetHealth() const
{
	return m_iHealth;
}

Sprite* Hero::UseWeapon()
{
	// old implementation idea - has been moved
	return NULL;
}

void Hero::IncreaseHealthMeter()
{
	m_iHealthMeter++;
}
