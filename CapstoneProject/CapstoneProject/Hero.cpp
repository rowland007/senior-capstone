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
#include "Hero.h"



Hero::Hero() : m_iHealth(3), m_iHealthMeter(3)
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

void Hero::SetWeapon(WEAPONTYPE weapon)
{
	m_wtWeapon = weapon;
}

WEAPONTYPE Hero::GetWeapon() const
{
	return WEAPONTYPE();
}

void Hero::SetHealth(int health)
{
	m_iHealth = health;
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
