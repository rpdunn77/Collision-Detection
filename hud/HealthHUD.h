/*
File: HealthHUD.h
Author: Benjamin Smith
Purpose:
	Display the health levels of the PC and decrease/increase 
	accordingly.
*/
#pragma once
#ifndef HEALTHHUD_H
#define HEALTHHUD_H

#include "pc.h"

class HUD; 

class HealthHUD {
	
	protected: 
	
	private:
		int m_health;
		// Displays the health of the character
		HealthHUD::display(m_health); // Overrides HUD display

	public:
		HealthHUD(); // Constructor
		// ~HealthHUD(); // Destructor not required: singleton
};

#endif // !HEALTHHUD_H
