
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
#pragma once
#include "Sprite.h"

class EnemyBoss : public Sprite
{
public:
	EnemyBoss();
	~EnemyBoss();
	void SetHealth(int);
	int GetHealth() const;
	void MoveRandomly();
	void MoveChase();
	void MoveRunAway();

private:
	int m_iHealth;
};

