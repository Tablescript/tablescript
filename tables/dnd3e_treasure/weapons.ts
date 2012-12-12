// weapons.ts
//

table weapon_minor d100 {
	1-85:	{type = weaponType();}
			(bonus_minor() + " " + type[0])
	86-100:	{
				type = weaponType();
				if(type[1] == 0) {
					special = meleeSpecial_minor();
				} else {
					special = rangedSpecial_minor(type[1]);
				}
			}
			(bonus_minor() + " " + type[0] + ", " + special)
}

table weapon_medium d100 {
	1-62:	{type = weaponType();}
			(bonus_medium() + " " + type[0])
	63-68:	(specificWeapon_medium())
	69-100:	{
				type = weaponType();
				if(type[1] == 0) {
					special = meleeSpecial_medium();
				} else {
					special = rangedSpecial_medium(type[1]);
				}
			}
			(bonus_medium() + " " + type[0] + ", " + special)
}

table weapon_major d100 {
	1-49:	{type = weaponType();}
			(bonus_major() + " " + type[0])
	50-63:	(specificWeapon_major())
	64-100:	{
				type = weaponType();
				if(type[1] == 0) {
					special = meleeSpecial_major();
				} else {
					special = rangedSpecial_major();
				}
			}
			(bonus_major() + " " + type[0] + ", " + special)
}

table bonus_minor {
	1-70:	("+1")
	71-85:	("+2")
}

table bonus_medium {
	1-10:	("+1")
	11-20:	("+2")
	21-58:	("+3")
	59-62:	("+4")
}

table bonus_major {
	1-20:	("+3")
	21-38:	("+4")
	39-49:	("+5")
}

table weaponType d100 {
	1-70:	([commonMeleeWeapon(), 0])
	71-80:	(uncommonWeapon())
	81-100:	(commonRangedWeapon())
}

table commonMeleeWeapon d100 {
	1-4:	("Dagger")
	5-14:	("Greataxe")
	15-24:	("Greatsword")
	25-28:	("Kama")
	29-41:	("Longsword")
	42-45:	("Light mace")
	46-50:	("Heavy mace")
	51-54:	("Nunchaku")
	55-57:	("Quarterstaff")
	58-61:	("Rapier")
	62-66:	("Scimitar")
	67-70:	("Shortspear")
	71-74:	("Siangham")
	75-84:	("Bastard sword")
	85-89:	("Short sword")
	90-100:	("Dwarven waraxe")
}

table uncommonWeapon d100 {
	1-3:	(["Axe, orc double", 0])
	4-7:	(["Battleaxe", 0])
	8-10:	(["Chain, spiked", 0])
	11-12:	(["Club", 0])
	13-16:	(["Hand crossbow", 1])
	17-19:	(["Repeating crossbow", 1])
	20-21:	(["Punching dagger", 0])
	22-23:	(["Falchion", 0])
	24-26:	(["Dire flail", 0])
	27-31:	(["Heavy flail", 0])
	32-35:	(["Light flail", 0])
	36-37:	(["Gauntlet", 0])
	38-39:	(["Spiked gauntlet", 0])
	40-41:	(["Glaive", 0])
	42-43:	(["Greatclub", 0])
	44-45:	(["Guisarme", 0])
	46-48:	(["Halberd", 0])
	49-51:	(["Halfspear", 0])
	52-54:	(["Gnome hooked hammer", 0])
	55-56:	(["Light hammer", 0])
	57-58:	(["Handaxe", 0])
	59-61:	(["Kukri", 0])
	62-63:	(["Heavy lance", 0])
	64-65:	(["Light lance", 0])
	66-67:	(["Longspear", 0])
	68-70:	(["Morningstar", 0])
	71-72:	(["Net", 2])
	73-74:	(["Heavy pick", 0])
	75-76:	(["Light pick", 0])
	77-78:	(["Ranseur", 0])
	79-80:	(["Sap", 0])
	81-82:	(["Scythe", 0])
	83-84:	(["Shuriken", 2])
	85-86:	(["Sickle", 0])
	87-89:	(["Two-bladed sword", 0])
	90-91:	(["Trident", 0])
	92-94:	(["Dwarven urgrosh", 0])
	95-97:	(["Warhammer", 0])
	98-100:	(["Whip", 0])
}

table commonRangedWeapon d100 {
	1-10:	([ammunition(), 1])
	11-15:	(["Throwing axe", 2])
	16-25:	(["Heavy crossbow", 1])
	26-35:	(["Light crossbow", 1])
	36-39:	(["Dart", 2])
	40-41:	(["Javelin", 2])
	42-46:	(["Shortbow", 1])
	47-51:	(["Composite shortbow", 1])
	52-56:	(["Mighty composite shortbow (+1 Str bonus)", 1])
	57-61:	(["Mighty composite shortbow (+2 Str bonus)", 1])
	62-65:	(["Sling", 1])
	66-75:	(["Longbow", 1])
	76-80:	(["Composite longbow", 1])
	81-85:	(["Mighty composite longbow (+1 Str bonus)", 1])
	86-90:	(["Mighty composite longbow (+2 Str bonus)", 1])
	91-95:	(["Mighty composite longbow (+3 Str bonus)", 1])
	96-100:	(["Mighty composite longbow (+4 Str bonus)", 1])
}

table ammunition d100 {
	1-50:	("Arrows (50)")
	51-80:	("Crossbow bolts (50)")
	81-100:	("Sling bullets (50)")
}

table specificWeapon_medium d100 {
	1-20:	("Sleep arrow")
	21-40:	("Screaming bolt")
	41-55:	("Javelin of lightning")
	56-65:	("Slaying arror (" + slayingTarget() + ")")
	66-70:	("Adamantine dagger")
	71-72:	("Trident of fish command")
	73-74:	("Dagger of venom")
	75-76:	("Adamantine battleaxe")
	77-79:	("Trident of warning")
	80-82:	("Assassin's dagger")
	83-85:	("Sword of subtlety")
	86-88:	("Mace of terror")
	89-91:	("Nine lives stealer")
	92-94:	("Oathbow")
	95-96:	("Sword of life stealing")
	97-98:	("Flame tongue")
	99-100:	("Life-drinker")
}

table specificWeapon_major d100 {
	1-4:	("Javelin of lightning")
	5-9:	("Slaying arror (" + slayingTarget() + ")")
	10-11:	("Trident of fish command")
	12-13:	("Greater slaying arrow (" + slayingTarget() + ")")
	14-17:	("Dagger of venom")
	18-20:	("Adamantine battleaxe")
	21-25:	("Trident of warning")
	26-30:	("Assassin's dagger")
	31-35:	("Sword of subtlety")
	36-40:	("Mace of terror")
	41-45:	("Nine lives stealer")
	46-50:	("Oathbow")
	51-55:	("Sword of life stealing")
	56-60:	("Flame tongue")
	61-66:	("Life-drinker")
	67-72:	("Frost brand")
	73-78:	("Rapier of puncturing")
	79-81:	("Sun blade")
	82-83:	("Sword of the planes")
	84-85:	("Sylvan scimitar")
	86-87:	("Dwarven thrower")
	88-90:	("Mace of smiting")
	91-96:	("Holy avenger")
	97-100:	("Luck blade")
}

table slayingTarget d100 {
	1-5:	("Aberrations")
	6-8:	("Animals")
	9-13:	("Beasts")
	14-20:	("Constructs")
	21-25:	("Dragons")
	26-30:	("Elementals")
	31-35:	("Fey")
	36-40:	("Giants")
	41-45:	("Magical beasts")
	46-50:	("Monstrous humanoid")
	51-53:	("Oozes")
	54-58:	("Chaotic outsiders")
	59-65:	("Evil outsiders")
	66-70:	("Good outsiders")
	71-75:	("Lawful outsiders")
	76-77:	("Plants")
	78-85:	("Shapechangers")
	86-92:	("Undead")
	93-94:	("Vermin")
	95-100:	("Humanoid")
}

table rangedSpecial_minor(type) d100 {
	1-20:	{
				if(type == 2) {
					result = "Returning";
				} else {
					result = rangedSpecial_minor(type);
				}
			}
			(result)
	21-40:	("Distance")
	41-60:	("Flaming")
	61-80:	("Shock")
	81-100:	("Frost")
}

table rangedSpecial_medium(type) d100 {
	1-15:	{
				if(type == 2) {
					result = "Returning";
				} else {
					result = rangedSpecial_medium(type);
				}
			}
			(result)
	16-30:	("Distance")
	31-35:	("Flaming")
	36-40:	("Shock")
	41-45:	("Frost")
	46-50:	("Flaming burst")
	51-55:	("Icy burst")
	56-60:	("Shocking burst")
	61-66:	("Bane")
	67-74:	("Holy")
	75-82:	("Unholy")
	83-90:	("Lawful")
	91-98:	("Chaotic")
	99-100:	(rangedSpecial_medium(type) + ", " + rangedSpecial_medium(type))
}

table rangedSpecial_major d100 {
	1-10:	("Flaming")
	11-20:	("Shock")
	21-30:	("Frost")
	31-40:	("Flaming burst")
	41-50:	("Icy burst")
	51-60:	("Shocking burst")
	61-65:	("Bane")
	66-70:	("Holy")
	71-75:	("Unholy")
	76-80:	("Lawful")
	81-85:	("Chaotic")
	86-90:	("Speed")
	91-97:	("Brilliant energy")
	99-100:	(rangedSpecial_major() + ", " + rangedSpecial_major())
}

table meleeSpecial_minor d100 {
	1-15:	("Defending")
	16-25:	("Flaming")
	26-35:	("Frost")
	36-45:	("Shock")
	46-55:	("Ghost touch")
	56-70:	("Keen")
	71-80:	("Mighty cleaving")
	81-89:	("Spell storing")
	90-99:	("Throwing")
	100:	(meleeSpecial() + ", " + meleeSpecial())
}

//table meleeSpecial_medium d100 {
//	1-15:	("Defending")
//	16-25:	("Flaming")
//	26-35:	("Frost")
//	36-45:	("Shock")
//	46-55:	("Ghost touch")
//	56-70:	("Keen")
//	71-80:	("Mighty cleaving")
//	81-89:	("Spell storing")
//	90-99:	("Throwing")
//	57-59:	("Bane")
//	60-62:	("Disruption")
//	63

for i in range(100) {
	print(weapon_minor());
}
