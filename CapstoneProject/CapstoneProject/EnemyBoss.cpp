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
************************************************************************/
#include "EnemyBoss.h"



EnemyBoss::EnemyBoss(Bitmap* pBitmap, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP) : Sprite(pBitmap, rcBounds, baBoundsAction), m_iHealth(15)
{
}


EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::SetHealth(int health)
{
	m_iHealth = health;
}

int EnemyBoss::GetHealth() const
{
	return 0;
}

void EnemyBoss::MoveRandomly()
{
}

void EnemyBoss::MoveChase()
{
}

void EnemyBoss::MoveRunAway()
{
}
