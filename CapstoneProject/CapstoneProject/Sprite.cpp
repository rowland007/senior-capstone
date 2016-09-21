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
5Sep16	Modified class to orient frames horizontally compared to vertically.
************************************************************************/
#include "Sprite.h"

//-----------------------------------------------------------------
// Sprite Constructor(s)/Destructor
//-----------------------------------------------------------------
Sprite::Sprite(Bitmap* pBitmap)
{
  // Initialize the member variables
  m_pBitmap = pBitmap;
  m_iNumFrames = 1;
  m_iCurFrame = m_iFrameDelay = m_iFrameTrigger = 0;
  SetRect(&m_rcPosition, 0, 0, pBitmap->GetWidth(), pBitmap->GetHeight());
  CalcCollisionRect();
  m_ptVelocity.x = m_ptVelocity.y = 0;
  m_iZorder = 0;
  SetRect(&m_rcBounds, 0, 0, 640, 480);
  m_baBoundsAction = BA_STOP;
  m_bHidden = false;
  m_bDying = false;
  m_bOneCycle = false;
}

Sprite::Sprite(Bitmap* pBitmap, RECT& rcBounds, BOUNDSACTION baBoundsAction)
{
  // Calculate a random position
  int iXPos = rand() % (rcBounds.right - rcBounds.left);
  int iYPos = rand() % (rcBounds.bottom - rcBounds.top);

  // Initialize the member variables
  m_pBitmap = pBitmap;
  m_iNumFrames = 1;
  m_iCurFrame = m_iFrameDelay = m_iFrameTrigger = 0;
  SetRect(&m_rcPosition, iXPos, iYPos, iXPos + pBitmap->GetWidth(), iYPos + pBitmap->GetHeight());
  CalcCollisionRect();
  m_ptVelocity.x = m_ptVelocity.y = 0;
  m_iZorder = 0;
  CopyRect(&m_rcBounds, &rcBounds);
  m_baBoundsAction = baBoundsAction;
  m_bHidden = false;
  m_bDying = false;
  m_bOneCycle = false;
}

Sprite::Sprite(Bitmap* pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder, RECT& rcBounds, BOUNDSACTION baBoundsAction)
{
  // Initialize the member variables
  m_pBitmap = pBitmap;
  m_iNumFrames = 1;
  m_iCurFrame = m_iFrameDelay = m_iFrameTrigger = 0;
  SetRect(&m_rcPosition, ptPosition.x, ptPosition.y, ptPosition.x + pBitmap->GetWidth(), ptPosition.y + pBitmap->GetHeight());
  CalcCollisionRect();
  m_ptVelocity = ptVelocity;
  m_iZorder = iZOrder;
  CopyRect(&m_rcBounds, &rcBounds);
  m_baBoundsAction = baBoundsAction;
  m_bHidden = false;
  m_bDying = false;
  m_bOneCycle = false;
}

Sprite::~Sprite()
{
}

//-----------------------------------------------------------------
// Sprite General Methods
//-----------------------------------------------------------------
SPRITEACTION Sprite::Update()
{
  // See if the sprite needs to be killed
  if (m_bDying)
    return SA_KILL;

  // Update the frame
  UpdateFrame();

  // Update the position
  POINT ptNewPosition, ptSpriteSize, ptBoundsSize;
  ptNewPosition.x = m_rcPosition.left + m_ptVelocity.x;
  ptNewPosition.y = m_rcPosition.top + m_ptVelocity.y;
  ptSpriteSize.x = m_rcPosition.right - m_rcPosition.left;
  ptSpriteSize.y = m_rcPosition.bottom - m_rcPosition.top;
  ptBoundsSize.x = m_rcBounds.right - m_rcBounds.left;
  ptBoundsSize.y = m_rcBounds.bottom - m_rcBounds.top;

  // Check the bounds
  // Wrap?
  if (m_baBoundsAction == BA_WRAP)
  {
    if ((ptNewPosition.x + ptSpriteSize.x) < m_rcBounds.left)
      ptNewPosition.x = m_rcBounds.right;
    else if (ptNewPosition.x > m_rcBounds.right)
      ptNewPosition.x = m_rcBounds.left - ptSpriteSize.x;
    if ((ptNewPosition.y + ptSpriteSize.y) < m_rcBounds.top)
      ptNewPosition.y = m_rcBounds.bottom;
    else if (ptNewPosition.y > m_rcBounds.bottom)
      ptNewPosition.y = m_rcBounds.top - ptSpriteSize.y;
  }
  // Bounce?
  else if (m_baBoundsAction == BA_BOUNCE)
  {
    bool bBounce = false;
    POINT ptNewVelocity = m_ptVelocity;
    if (ptNewPosition.x < m_rcBounds.left)
    {
      bBounce = true;
      ptNewPosition.x = m_rcBounds.left;
      ptNewVelocity.x = -ptNewVelocity.x;
    }
    else if ((ptNewPosition.x + ptSpriteSize.x) > m_rcBounds.right)
    {
      bBounce = true;
      ptNewPosition.x = m_rcBounds.right - ptSpriteSize.x;
      ptNewVelocity.x = -ptNewVelocity.x;
    }
    if (ptNewPosition.y < m_rcBounds.top)
    {
      bBounce = true;
      ptNewPosition.y = m_rcBounds.top;
      ptNewVelocity.y = -ptNewVelocity.y;
    }
    else if ((ptNewPosition.y + ptSpriteSize.y) > m_rcBounds.bottom)
    {
      bBounce = true;
      ptNewPosition.y = m_rcBounds.bottom - ptSpriteSize.y;
      ptNewVelocity.y = -ptNewVelocity.y;
    }
    if (bBounce)
      SetVelocity(ptNewVelocity);
  }
  // Die?
  else if (m_baBoundsAction == BA_DIE)
  {
    if ((ptNewPosition.x + ptSpriteSize.x) < m_rcBounds.left ||
      ptNewPosition.x > m_rcBounds.right ||
      (ptNewPosition.y + ptSpriteSize.y) < m_rcBounds.top ||
      ptNewPosition.y > m_rcBounds.bottom)
      return SA_KILL;
  }
  // Stop (default)
  else
  {
    if (ptNewPosition.x  < m_rcBounds.left ||
      ptNewPosition.x > (m_rcBounds.right - ptSpriteSize.x))
    {
      ptNewPosition.x = max(m_rcBounds.left, min(ptNewPosition.x,
        m_rcBounds.right - ptSpriteSize.x));
      SetVelocity(0, 0);
    }
    if (ptNewPosition.y  < m_rcBounds.top ||
      ptNewPosition.y > (m_rcBounds.bottom - ptSpriteSize.y))
    {
      ptNewPosition.y = max(m_rcBounds.top, min(ptNewPosition.y,
        m_rcBounds.bottom - ptSpriteSize.y));
      SetVelocity(0, 0);
    }
  }
  SetPosition(ptNewPosition);

  return SA_NONE;
}

void Sprite::Draw(HDC hDC)
{
  // Draw the sprite if it isn't hidden
  if (m_pBitmap != NULL && !m_bHidden)
  {
    // Draw the appropriate frame, if necessary
    if (m_iNumFrames == 1)
      m_pBitmap->Draw(hDC, m_rcPosition.left, m_rcPosition.top, true);
    else
      m_pBitmap->DrawPart(hDC, m_rcPosition.left, m_rcPosition.top, m_iCurFrame * GetWidth(), 0, GetWidth(), GetHeight(), true, RGB(255,0,255));
  }
}

bool Sprite::IsPointInside(int x, int y)
{
	POINT ptPoint;
	ptPoint.x = x;
	ptPoint.y = y;
	return PtInRect(&m_rcPosition, ptPoint);
}

bool Sprite::TestCollision(Sprite * pTestSprite)
{
	RECT& rcTest = pTestSprite->GetCollision();
	return m_rcCollision.left <= rcTest.right && rcTest.left <= m_rcCollision.right && m_rcCollision.top <= rcTest.bottom && rcTest.top <= m_rcCollision.bottom;
}

void Sprite::Kill()
{
	m_bDying = true;
}

Bitmap* Sprite::GetBitmap() const
{
	return m_pBitmap;
}

void Sprite::SetNumFrames(int iNumFrames, bool bOneCycle)
{
	// Set the number of frames and the one-cycle setting
	m_iNumFrames = iNumFrames;
	m_bOneCycle = bOneCycle;

	// Recalculate the position
	RECT rect = GetPosition();
	rect.left = rect.left + ((rect.right - rect.left) / iNumFrames);
	SetPosition(rect);
}

void Sprite::SetFrameDelay(int iFrameDelay)
{
	m_iFrameDelay = iFrameDelay;
}

void Sprite::SetBitmap(Bitmap *pBitmap)
{
	m_pBitmap = pBitmap;
}

RECT& Sprite::GetPosition()
{
	return m_rcPosition;
}

void Sprite::SetPosition(int x, int y)
{
	OffsetRect(&m_rcPosition, x - m_rcPosition.left, y - m_rcPosition.top);
	CalcCollisionRect();
}

void Sprite::SetPosition(POINT ptPosition)
{
	OffsetRect(&m_rcPosition, ptPosition.x - m_rcPosition.left,	ptPosition.y - m_rcPosition.top);
	CalcCollisionRect();
}

void Sprite::SetPosition(RECT & rcPosition)
{
	CopyRect(&m_rcPosition, &rcPosition);
	CalcCollisionRect();
}

void Sprite::OffsetPosition(int x, int y)
{
	OffsetRect(&m_rcPosition, x, y);
	CalcCollisionRect();
}

RECT& Sprite::GetCollision() 
{
	return m_rcCollision;
}

POINT Sprite::GetVelocity() 
{
	return m_ptVelocity;
}

void Sprite::SetVelocity(int x, int y)
{
	m_ptVelocity.x = x;
	m_ptVelocity.y = y;
}

void Sprite::SetVelocity(POINT ptVelocity)
{
	m_ptVelocity.x = ptVelocity.x;
	m_ptVelocity.y = ptVelocity.y;
}

bool Sprite::GetZorder() const
{
	return m_iZorder;
}

void Sprite::SetZorder(int iZOrder)
{
	m_iZorder = iZOrder;
}

void Sprite::SetBounds(RECT& rcBounds)
{
	CopyRect(&m_rcBounds, &rcBounds);
}

void Sprite::SetBoundsAction(BOUNDSACTION ba)
{
	m_baBoundsAction = ba;
}

bool Sprite::IsHidden() const
{
	return m_bHidden;
}

void Sprite::SetHidden(bool bHidden)
{
	m_bHidden = bHidden;
}

int Sprite::GetWidth() const
{
	return m_pBitmap->GetWidth() / m_iNumFrames;
}

int Sprite::GetHeight() const
{
	return m_pBitmap->GetHeight();
}

void Sprite::UpdateFrame()
{
	if ((m_iFrameDelay >= 0) && (--m_iFrameTrigger <= 0))
	{
		// Reset the frame trigger;
		m_iFrameTrigger = m_iFrameDelay;

		// Increment the frame
		if (++m_iCurFrame >= m_iNumFrames)
		{
			// If it's a one-cycle frame animation, kill the sprite
			if (m_bOneCycle)
				m_bDying = true;
			else
				m_iCurFrame = 0;
		}
	}
}

void Sprite::CalcCollisionRect()
{
	int iXShrink = (m_rcPosition.left - m_rcPosition.right) / 12;
	int iYShrink = (m_rcPosition.top - m_rcPosition.bottom) / 12;
	CopyRect(&m_rcCollision, &m_rcPosition);
	InflateRect(&m_rcCollision, iXShrink, iYShrink);
}
