/*
File: HUD.h
Author: Benjamin Smith
Purpose: 
	HUD implements a overlay view over the main game screen that 
	displays information about the player's health, weapon equipped,
	ammunition, and minimap. As the player moves, gets hit, and uses ammunition,
	the values shall be adjusted accordingly giving the controller feedback
	on their character. 
*/

#pragma once
#ifndef HUD_H
#define HUD_H

#include "GameObject.h"

#include "Game.h"
#include "Map.h"

class HUD {

	protected:
		display(); // Display function that implements the overlaid graphics on main window.
	private:
		GLfloat m_width, m_length;

		// Displays minimap
		HUD::display();


	public:
		HUD(); // Default constructor. 
			   // ~HUD(); // Don't implement: using singleton.
		
		update();
};

#endif // !HUD_H

