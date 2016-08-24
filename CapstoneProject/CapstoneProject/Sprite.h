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
************************************************************************/
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
	Sprite(Bitmap*);
	Sprite(Bitmap*, RECT&, BOUNDSACTION baBoundsAction = BA_STOP);
	Sprite(Bitmap*, POINT, POINT, int, RECT&, BOUNDSACTION baBoundsAction = BA_STOP);
	virtual ~Sprite();
	virtual SPRITEACTION Update();
	Sprite *AddSprite;
	void Draw(HDC);
	bool IsPointInside(int, int);
	bool TestCollision(Sprite*);
	void Kill();
	Bitmap *GetBitmap() const;
	void SetNumFrames(int, bool bOneCycle = false);
	void SetFrameDelay(int);
	RECT &GetPosition();
	void SetPosition(int, int);
	void SetPosition(POINT);
	void SetPosition(RECT&);
	void OffsetPosition(int, int);
	RECT &GetCollision();
	POINT GetVelocity();
	void SetVelocity(int, int);
	void SetVelocity(POINT);
	bool GetZorder() const;
	void SetZorder(int);
	void SetBounds(RECT&);
	void SetBoundsAction(BOUNDSACTION);
	bool IsHidden() const;
	void SetHidden(bool);
	int GetWidth() const;
	int GetHeight() const;
protected:
	Bitmap			*m_pBitmap;
	int				m_iNumFrames;
	int				m_iCurFrame;
	int				m_iFrameDelay;
	int				m_iFrameTrigger;
	int				m_iZorder;
	POINT			m_ptVelocity;
	RECT			m_rcPosition;
	RECT			m_rcCollision;
	RECT			m_rcBounds;
	BOUNDSACTION	m_baBoundsAction;
	bool			m_bHidden;
	bool			m_bDying;
	bool			m_bOneCycle;

	void UpdateFrame();
	virtual void CalcCollisionRect();
};