/*
File: WeaponHUD.h
Author: Benjamin Smith
Purpose: 
	Display the name of the weapon and it's appropriate
	ammunition levels
*/
#pragma once
#ifndef WEAPONHUD_H
#define WEAPONHUD_H

#include "Weapon.h"

class HUD;

class WeaponHUD {

	protected:

	private:
		int m_ammo;
		string m_weaponName;
		// Displays weapon selected
		display(m_weaponName); // Overrides HUD display
		// Displays ammunition left
		display(m_ammo); // Overrides HUD display

	public:
		WeaponHUD(); // Constructor 
		//~WeaponHUD(); // Destructor not required: singleton
};
#endif // !WEAPONHUD_H
