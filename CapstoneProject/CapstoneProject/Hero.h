/************************************************************************
Program:		CapstoneProject
Author:			Randy Rowland
Class:			Hero
Instructor:		Dan Randall
Date:			23 August 2016
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

typedef WORD		WEAPONTYPE;
const WEAPONTYPE	WT_SWORD = 0,
					WT_BOOMERANG = 1,
					WT_BOW = 2;

class Hero : public Sprite
{
public:
	Hero();
	~Hero();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void SetWeapon(WEAPONTYPE);
	WEAPONTYPE GetWeapon() const;
	void SetHealth(int);
	int GetHealth() const;
	void UseWeapon();
	void IncreaseHealthMeter();

private:
	int m_iHealth;
	int m_iHealthMeter;
	WEAPONTYPE m_wtWeapon;
};

