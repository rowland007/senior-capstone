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
************************************************************************/
#include "Hero.h"

/// All the bitmaps that are used by the Hero
///Hero himself
Bitmap *g_pHeroWalkingLeftBitmap;
Bitmap *g_pHeroWalkingRightBitmap;
Bitmap *g_pHeroWalkingUpBitmap;
Bitmap *g_pHeroWalkingDownBitmap;
Bitmap *g_pHeroDamageLeftBitmap;
Bitmap *g_pHeroDamageRightBitmap;
Bitmap *g_pHeroDamageUpBitmap;
Bitmap *g_pHeroDamageDownBitmap;
Bitmap *g_pHeroDyingBitmap;
Bitmap *g_pHeroWinBitmap;
Bitmap *g_pHeroBoomerangLeftBitmap;
Bitmap *g_pHeroBoomerangRightBitmap;
Bitmap *g_pHeroBoomerangDownBitmap;
Bitmap *g_pHeroBoomerangUpBitmap;
Bitmap *g_pHeroBowLeftBitmap;
Bitmap *g_pHeroBowRightBitmap;
Bitmap *g_pHeroBowUpBitmap;
Bitmap *g_pHeroBowDownBitmap;
Bitmap *g_pHeroSwordLeftBitmap;
Bitmap *g_pHeroSwordRightBitmap;
Bitmap *g_pHeroSwordUpBitmap;
Bitmap *g_pHeroSwordDownBitmap;

///Weapons
Bitmap *g_pArrowLeftBitmap;
Bitmap *g_pArrowRightBitmap;
Bitmap *g_pArrowUpBitmap;
Bitmap *g_pArrowDownBitmap;
Bitmap *g_pBoomerangBitmap;
Bitmap *g_pSwordSwingLeftBitmap;
Bitmap *g_pSwordSwingRightBitmap;
Bitmap *g_pSwordSwingUpBitmap;
Bitmap *g_pSwordSwingDownBitmap;


Hero::Hero(Bitmap* pBitmap, RECT& rcBounds,	BOUNDSACTION baBoundsAction = BA_STOP) : Sprite(pBitmap, rcBounds, baBoundsAction), m_iHealth(3), m_iHealthMeter(3)
{
}


Hero::~Hero()
{
}

void Hero::MoveLeft()
{
	Bitmap *pNewBitmap;
	int iNumFrames;

	switch (GetWeapon())
	{
	case WT_BOOMERANG:
		pNewBitmap = g_pHeroBoomerangLeftBitmap;
		iNumFrames = 2;
		break;
	case WT_BOW:
		pNewBitmap = g_pHeroBowLeftBitmap;
		iNumFrames = 2;
		break;
	case WT_SWORD:
		pNewBitmap = g_pHeroWalkingLeftBitmap;
		iNumFrames = 8;
		break;
	default:
		pNewBitmap = g_pHeroWalkingLeftBitmap;
		iNumFrames = 8;
	}
	m_fdDirection = FD_LEFT;
	this->SetBitmap(pNewBitmap);
	this->SetNumFrames(iNumFrames);
	this->SetVelocity(-16, 0);
}

void Hero::MoveRight()
{
	Bitmap *pNewBitmap;
	int iNumFrames;

	switch (GetWeapon())
	{
	case WT_BOOMERANG:
		pNewBitmap = g_pHeroBoomerangRightBitmap;
		iNumFrames = 2;
		break;
	case WT_BOW:
		pNewBitmap = g_pHeroBowRightBitmap;
		iNumFrames = 2;
		break;
	case WT_SWORD:
		pNewBitmap = g_pHeroWalkingRightBitmap;
		iNumFrames = 8;
		break;
	default:
		pNewBitmap = g_pHeroWalkingRightBitmap;
		iNumFrames = 8;
	}
	m_fdDirection = FD_RIGHT;
	this->SetBitmap(pNewBitmap);
	this->SetNumFrames(iNumFrames);
	this->SetVelocity(16, 0);
}

void Hero::MoveUp()
{
	Bitmap *pNewBitmap;
	int iNumFrames;

	switch (GetWeapon())
	{
	case WT_BOOMERANG:
		pNewBitmap = g_pHeroBoomerangUpBitmap;
		iNumFrames = 2;
		break;
	case WT_BOW:
		pNewBitmap = g_pHeroBowUpBitmap;
		iNumFrames = 2;
		break;
	case WT_SWORD:
		pNewBitmap = g_pHeroWalkingUpBitmap;
		iNumFrames = 8;
		break;
	default:
		pNewBitmap = g_pHeroWalkingUpBitmap;
		iNumFrames = 8;
	}
	m_fdDirection = FD_UP;
	this->SetBitmap(pNewBitmap);
	this->SetNumFrames(iNumFrames);
	this->SetVelocity(0, -24);
}

void Hero::MoveDown()
{
	Bitmap *pNewBitmap;
	int iNumFrames;

	switch (GetWeapon())
	{
	case WT_BOOMERANG:
		pNewBitmap = g_pHeroBoomerangDownBitmap;
		iNumFrames = 2;
		break;
	case WT_BOW:
		pNewBitmap = g_pHeroBowDownBitmap;
		iNumFrames = 2;
		break;
	case WT_SWORD:
		pNewBitmap = g_pHeroWalkingDownBitmap;
		iNumFrames = 8;
		break;
	default:
		pNewBitmap = g_pHeroWalkingDownBitmap;
		iNumFrames = 8;
	}
	m_fdDirection = FD_DOWN;
	this->SetBitmap(pNewBitmap);
	this->SetNumFrames(iNumFrames);
	this->SetVelocity(0, 24);
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

	switch (m_wtWeapon)
	{
	case WT_SWORD:
	{
		//Get direction hero is facing
		//Set new bitmap and frames for that direction
		//have animation run only once
		//after animation completes, go back to last bitmap
		Sprite *pSwordSwingSprite = NULL;
		switch (GetDirection())
		{
		case FD_LEFT:
			this->SetBitmap(g_pHeroSwordLeftBitmap);
			this->SetNumFrames(12);
			this->SetVelocity(0, 0);
			pSwordSwingSprite = new Sprite(g_pSwordSwingLeftBitmap);
			pSwordSwingSprite->SetNumFrames(12);
			pSwordSwingSprite->SetPosition(m_rcPosition);
			return pSwordSwingSprite;
			break;
		case FD_RIGHT:
			this->SetBitmap(g_pHeroSwordRightBitmap);
			this->SetNumFrames(12);
			this->SetVelocity(0, 0);
			pSwordSwingSprite = new Sprite(g_pSwordSwingRightBitmap);
			pSwordSwingSprite->SetNumFrames(12);
			pSwordSwingSprite->SetPosition(m_rcPosition);
			return pSwordSwingSprite;
			break;
		case FD_UP:
			this->SetBitmap(g_pHeroSwordUpBitmap);
			this->SetNumFrames(12);
			this->SetVelocity(0, 0);
			pSwordSwingSprite = new Sprite(g_pSwordSwingUpBitmap);
			pSwordSwingSprite->SetNumFrames(12);
			pSwordSwingSprite->SetPosition(m_rcPosition);
			return pSwordSwingSprite;
			break;
		case FD_DOWN:
			this->SetBitmap(g_pHeroSwordDownBitmap);
			this->SetNumFrames(12);
			this->SetVelocity(0, 0);
			pSwordSwingSprite = new Sprite(g_pSwordSwingDownBitmap);
			pSwordSwingSprite->SetNumFrames(12);
			pSwordSwingSprite->SetPosition(m_rcPosition);
			return pSwordSwingSprite;
			break;
		default:
			break;
		}
		break;
	}
	case WT_BOOMERANG:
	{
		// Need to setup a bounding area around the hero that moves with hero
		Sprite *pBoomerangSprite = new Sprite(g_pBoomerangBitmap);
		pBoomerangSprite->SetNumFrames(4);
		//pBoomerangSprite->SetBounds(RECT&); ///< figure out the rect around the hero
		switch (GetDirection())
		{
		case FD_LEFT:
			pBoomerangSprite->SetPosition(m_rcPosition);
			pBoomerangSprite->SetVelocity(-12, 0);
			pBoomerangSprite->SetBoundsAction(BA_BOUNCE);
			return pBoomerangSprite;
			break;
		case FD_RIGHT:
			pBoomerangSprite->SetPosition(m_rcPosition);
			pBoomerangSprite->SetVelocity(12, 0);
			pBoomerangSprite->SetBoundsAction(BA_BOUNCE);
			return pBoomerangSprite;
			break;
		case FD_UP:
			pBoomerangSprite->SetPosition(m_rcPosition);
			pBoomerangSprite->SetVelocity(0, -12);
			pBoomerangSprite->SetBoundsAction(BA_BOUNCE);
			return pBoomerangSprite;
			break;
		case FD_DOWN:
			pBoomerangSprite->SetPosition(m_rcPosition);
			pBoomerangSprite->SetVelocity(0, 12);
			pBoomerangSprite->SetBoundsAction(BA_BOUNCE);
			return pBoomerangSprite;
			break;
		default:
			break;
		}
		break;
	}
	case WT_BOW:
	{
		Sprite* pArrowSprite = NULL;
		switch (GetDirection())
		{
		case FD_LEFT:
			pArrowSprite = new Sprite(g_pArrowLeftBitmap);
			pArrowSprite->SetNumFrames(9);
			pArrowSprite->SetBoundsAction(BA_DIE);
			pArrowSprite->SetPosition(m_rcPosition);
			pArrowSprite->SetVelocity(-16, 0);
			return pArrowSprite;
			break;
		case FD_RIGHT:
			pArrowSprite = new Sprite(g_pArrowRightBitmap);
			pArrowSprite->SetNumFrames(9);
			pArrowSprite->SetBoundsAction(BA_DIE);
			pArrowSprite->SetPosition(m_rcPosition);
			pArrowSprite->SetVelocity(16, 0);
			return pArrowSprite;
			break;
		case FD_UP:
			pArrowSprite = new Sprite(g_pArrowUpBitmap);
			pArrowSprite->SetNumFrames(9);
			pArrowSprite->SetBoundsAction(BA_DIE);
			pArrowSprite->SetPosition(m_rcPosition);
			pArrowSprite->SetVelocity(0, -16);
			return pArrowSprite;
			break;
		case FD_DOWN:
			pArrowSprite = new Sprite(g_pArrowDownBitmap);
			pArrowSprite->SetNumFrames(9);
			pArrowSprite->SetBoundsAction(BA_DIE);
			pArrowSprite->SetPosition(m_rcPosition);
			pArrowSprite->SetVelocity(0, 16);
			return pArrowSprite;
			break;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
}

void Hero::IncreaseHealthMeter()
{
	m_iHealthMeter++;
}
