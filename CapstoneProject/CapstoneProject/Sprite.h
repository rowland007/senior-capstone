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
************************************************************************
#pragma once
#include <Windows.h>
#include "Bitmap.h"

//Custom Data Types
typedef WORD		SPRITEACTION;
const SPRITEACTION	SA_NONE			= 0x0000L,
					SA_KILL			= 0x0001L,
					SA_ADDSPRITE	= 0x0002L;

typedef WORD		BOUNDSACTION;
const BOUNDSACTION	BA_STOP		= 0,
					BA_WRAP		= 1,
					BA_BOUNCE	= 2,
					BA_DIE		= 3;

class Sprite
{
public:
	Sprite(Bitmap *pBitmap, int iGameSizeWidth, int iGameSizeHeight);
	Sprite(Bitmap *pBitmap, RECT &rcBounds, BOUNDSACTION baBoundsAction = BA_STOP);
	Sprite(Bitmap *pBitmap, POINT ptPosition, POINT ptVelocity, int iZorder, RECT &rcBounds, BOUNDSACTION = BA_STOP);
	virtual ~Sprite();
	virtual SPRITEACTION Update();
	Sprite *AddSprite;
	void Draw(HDC hDC);
	BOOL IsPointInside(int x, int y);
	BOOL TestCollision(Sprite *pTestSprite);
	void Kill();
	Bitmap *GetBitmap() const;
	void SetNumFrames(int iNumFrames, BOOL bOneCycle = FALSE);
	void SetFrameDelay(int iFrameDelay);
	RECT &GetPosition() const;
	void SetPosition(int x, int y);
	void SetPosition(POINT ptPosition);
	void setPosition(RECT &rcPosition);
	void OffsetPosition(int x, int y);
	RECT &GetCollision() const;
	POINT GetVelocity() const;
	void SetVelocity(int x, int y);
	void SetVelocity(POINT ptVelocity);
	BOOL GetZorder() const;
	void SetZorder(int iZorder);
	void SetBounds(RECT &rcBounds);
	void SetBoundsAction(BOUNDSACTION ba);
	BOOL IsHidden() const;
	void SetHidden(BOOL bHidden);
	int GetWidth() const;
	int GetHeight() const;
protected:
	Bitmap			*m_pBitmap;
	int				m_iNumFrames;
	int				m_iCurFrame;
	int				m_iFrameDelay;
	int				m_iFrameTrigger;
	int				m_iZorder;
	POINT			m_ptVeloctiy;
	RECT			m_rcPosition;
	RECT			m_rcCollision;
	RECT			m_rcBounds;
	BOUNDSACTION	m_baBoundsAction;
	BOOL			m_bHidden;
	BOOL			m_bDying;
	BOOL			m_bOneCycle;

	void UpdateFrame();
	virtual void CalcCollisionRect();
};*/