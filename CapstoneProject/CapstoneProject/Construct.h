/************************************************************************
Program:		CapstoneProject
Author:			Randy Rowland
Class:			Construct.h
Instructor:		Dan Randall
Date:			24 August 2016
Description:	This file is used to load the Construct level of the game.
				It will load all the necessary bitmaps and sprites into
				memory so the GameEngine and Main.cpp will only have to 
				run game cycles and draw.
Input:			
Output:

Compilation instructions:
Usage:
Known bugs/missing features:

Modifications:
Date                Comment
----    ------------------------------------------------
31Aug16 Added comments for doxygen documentation generation
************************************************************************/
#pragma once
#include "Resource.h"
#include "Hero.h"

/*! \brief Used to load Bitmaps and Sprites into memory for this level
 *
 *  Loads Bitmaps that will make up the level design and NPCs.
 */

//TODO:
//Resources that are required
//Bitmap:
//      Floor:
//		{
//			for(y=0; y < (800-DialogBox.GetHeight() - Floor.GetHeight(); y+=Floor.GetHeight())
//				for(x=0; x < g_pGame.GetWidth(); x+=Floor.GetWidth())
//      			Floor->Draw(hDC,X, Y)
//		}
//      TextBox: DialogBox->Draw(hDC, 250, 800 - DialogBox.GetHeight())
//Sprites:
//      Hero
//      Left/Right/Top/Bottom/Corner Walls
//      Mentor 
//      Boomerang/Arrow/Sword
//      Text