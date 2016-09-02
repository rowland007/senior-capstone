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

************************************************************************/
#include "Hero.h"



Hero::Hero(Bitmap* pBitmap, RECT& rcBounds,	BOUNDSACTION baBoundsAction = BA_STOP) : Sprite(pBitmap, rcBounds, baBoundsAction), m_iHealth(3), m_iHealthMeter(3)
{
}


Hero::~Hero()
{
}

void Hero::MoveLeft()
{
}

void Hero::MoveRight()
{
}

void Hero::MoveUp()
{
}

void Hero::MoveDown()
{
}

void Hero::SetWeapon(WEAPONTYPE wtWeapon)
{
	m_wtWeapon = wtWeapon;
}

WEAPONTYPE Hero::GetWeapon() const
{
	return WEAPONTYPE();
}

void Hero::SetHealth(int iHealth)
{
	m_iHealth = iHealth;
}

int Hero::GetHealth() const
{
	return m_iHealth;
}

void Hero::UseWeapon()
{
}

void Hero::IncreaseHealthMeter()
{
	m_iHealthMeter++;
}
