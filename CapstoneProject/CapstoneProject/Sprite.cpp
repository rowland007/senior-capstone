/************************************************************************
Program:		CapstoneProject
Author:			Randy Rowland
Class:			Sprite
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
************************************************************************
#include "Sprite.h"
#include "GameEngine.h"

Sprite::Sprite(Bitmap *pBitmap, int iGameSizeWidth, int iGameSizeHeight)
{
	RECT rect;
	m_pBitmap = pBitmap;
	m_iNumFrames = 1;
	m_iCurFrame = m_iFrameDelay = m_iFrameTrigger = 0;
	SetRect(&m_rcPosition, 0, 0, pBitmap->GetWidth(), pBitmap->GetHeight());
	CalcCollisionRect();
	m_ptVeloctiy.x = m_ptVeloctiy.y = 0;
	m_iZorder = 0;
	SetRect(&m_rcBounds, 0, 0, iGameSizeWidth, iGameSizeHeight);
	m_baBoundsAction = BA_STOP;
	m_bHidden = FALSE;
	m_bDying = FALSE;
	m_bOneCycle = FALSE;
}

Sprite::Sprite(Bitmap *pBitmap, RECT &rcBounds, BOUNDSACTION baBoundsAction)
{
	m_pBitmap = pBitmap;
	m_iNumFrames = 1;
	m_iCurFrame = m_iFrameDelay = m_iFrameTrigger = 0;
	SetRect(&m_rcPosition, (rcBounds.right / 2), (rcBounds.bottom / 2), (rcBounds.right / 2) + pBitmap->GetWidth(), (rcBounds.bottom / 2) + pBitmap->GetHeight());
	//TODO: Finish Init vars
}

Sprite::~Sprite()
{
}*/
