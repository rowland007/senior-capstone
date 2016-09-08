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


void EnemyBoss::MoveChase()
{
}

void EnemyBoss::MoveRunAway()
{
}
