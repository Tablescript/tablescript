// armour_and_shields.ts
//

table armourAndShields_minor {
	1-65:	(shields_minor())
	66-87:	(armour_minor())
}

table armourAndShields_medium {
	1-33:	(shields_medium())
	34-63:	(armour_medium())
}

table armourAndShields_major {
	1-33:	(shields_major())
	34-63:	(armour_major())
}

// Shields
//
table shields_minor {
	1-60:	("+1 " + shieldType())
	61-65:	("+2 " + shieldType())
	66-78:	(shields_minor() + ", " + shieldSpecialAbilities_minor())
}

table shields_medium {
	1-5:	("+1 " + shieldType())
	6-15:	("+2 " + shieldType())
	16-25:	("+3 " + shieldType())
	26-30:	("+4 " + shieldType())
	31-33:	(specificShield_medium())
	34-70:	(shields_medium() + ", " + shieldSpecialAbilities_medium())
}

table shields_major {
	1-8:	("+3 " + shieldType())
	9-19:	("+4 " + shieldType())
	20-30:	("+5 " + shieldType())
	31-33:	(specificShield_major())
	34-70:	(shields_major() + ", " + shieldSpecialAbilities_major())
}

table shieldType d100 {
	1-10:	("Buckler")
	11-15:	("Shield, small, wooden")
	16-20:	("Shield, small, steel")
	21-30:	("Shield, large, wooden")
	31-95:	("Shield, large, steel")
	96-100:	("Shield, tower")
}

table shieldSpecialAbilities_minor d100 {
	1-30:	("Bashing")
	31-50:	("Blinding")
	51-60:	("Fortification, light")
	61-99:	("Arrow deflection")
	100:	(shieldSpecialAbilities_minor() + ", " + shieldSpecialAbilities_minor())
}

table shieldSpecialAbilities_medium d100 {
	1-10:	("Arror deflection")
	11-16:	("Animated")
	17-20:	("Spell resistance (13)")
	21-25:	("Ghost touch")
	26-30:	("Fortification, moderate")
	31-40:	("Acid resistance")
	41-50:	("Cold resistance")
	51-60:	("Fire resistance")
	61-70:	("Lightning resistance")
	71-80:	("Sonic resistance")
	81-90:	("Reflecting")
	91-100:	(shieldSpecialAbilities_medium() + ", " + shieldSpecialAbilities_medium())
}

table shieldSpecialAbilities_major d100 {
	1-15:	("Animated")
	16-20:	("Spell resistance (13)")
	21-25:	("Ghost touch")
	26-35:	("Fortification, moderate")
	36-38:	("Acid resistance")
	39-41:	("Cold resistance")
	42-44:	("Fire resistance")
	45-47:	("Lightning resistance")
	48-50:	("Sonic resistance")
	51-55:	("Spell resistance (15)")
	56-60:	("Spell resistance (17)")
	61-65:	("Fortification, heavy")
	66-70:	("Reflecting")
	71-80:	("Spell resistance (19)")
	81-100:	(shieldSpecialAbilities_major() + ", " + shieldSpecialAbilities_major())
}

table specificShield_medium d100 {
	1-10:	("Darkwood shield")
	11-18:	("Mithral large shield")
	19-25:	("Adamantine shield")
	26-45:	("Spined shield")
	46-65:	("Caster's shield")
	66-90:	("Lion's shield")
	91-100:	("Winged shield")
}

table specificShield_major d100 {
	1-20:	("Spined shield")
	21-40:	("Caster's shield")
	41-60:	("Lion's shield")
	61-80:	("Winged shield")
	81-100:	("Absorbing shield")
}

// Armour
//
table armour_minor {
	1-20:	("+1 " + armourType())
	21-22:	("+2 " + armourType())
	23-35:	(armour_minor() + ", " + armourSpecialAbilities_minor())
}

table armour_medium {
	1-5:	("+1 " + armourType())
	6-15:	("+2 " + armourType())
	16-25:	("+3 " + armourType())
	26-27:	("+4 " + armourType())
	28-30:	(specificArmour_medium())
	31-67:	(armour_medium() + ", " + armourSpecialAbilities_medium())
}

table armour_major {
	1-8:	("+3 " + armourType())
	9-20:	("+4 " + armourType())
	21-27:	("+5 " + armourType())
	28-30:	(specificArmour_major())
	31-67:	(armour_major() + ", " + armourSpecialAbilities_major())
}

table armourType d100 {
	1:		("Padded")
	2:		("Leather")
	3-12:	("Hide")
	13-27:	("Studded leather")
	28-42:	("Chain shirt")
	43:		("Scale mail")
	44:		("Chainmail")
	45-57:	("Breastplate")
	58:		("Splint mail")
	59:		("Banded mail")
	60:		("Half-plate")
	61-100:	("Full plate")
}

table armourSpecialAbilities_minor d100 {
	1-30:	("Glamered")
	31-52:	("Slick")
	53-74:	("Shadow")
	75-96:	("Silent moves")
	97-98:	("Fortification, moderate")
	99-100:	(armourSpecialAbilities_minor() + ", " + armourSpecialAbilities_minor())
}

table armourSpecialAbilities_medium d100 {
	1-2:	("Fortification, light")
	3-7:	("Glamered")
	8-19:	("Slick")
	20-30:	("Shadow")
	31-49:	("Silent moves")
	50:		("Spell resistance (13)")
	51-60:	("Ghost touch")
	61-65:	("Fortification, moderate")
	66:		("Spell resistance (15)")
	67-71:	("Acid resistance")
	72-76:	("Cold resistance")
	77-81:	("Fire resistance")
	82-86:	("Lightning resistance")
	87-91:	("Sonic resistance")
	92-94:	("Spell resistance (17)")
	95:		("Etherealness")
	96-98:	("Fortification, heavy")
	99-100:	(armourSpecialAbilities_medium() + ", " + armourSpecialAbilities_medium())
}

table armourSpecialAbilities_major d100 {
	1-2:	("Fortification, light")
	2-8:	("Glamered")
	9:		("Slick")
	10-11:	("Shadow")
	12-14:	("Silent moves")
	15-16:	("Spell resistance (13)")
	17-21:	("Ghost touch")
	22-23:	("Invulnerability")
	24-27:	("Fortification, moderate")
	28-29:	("Spell resistance (15)")
	30-31:	("Acid resistance")
	32-41:	("Cold resistance")
	42-51:	("Fire resistance")
	52-61:	("Lightning resistance")
	62-64:	("Sonic resistance")
	65-67:	("Spell resistance (17)")
	68-69:	("Etherealness")
	70-72:	("Fortification, heavy")
	73-74:	("Spell resistance (19)")
	75-100:	(armourSpecialAbilities_major() + ", " + armourSpecialAbilities_major())
}

table specificArmour_medium d100 {
	1-10:	("Mithral shirt")
	11-25:	("Elven chain")
	26-35:	("Rhino hide")
	36-45:	("Adamantine breastplate")
	46-70:	("Dwarven plate")
	71-80:	("Plate armour of the deep")
	81-90:	("Banded mail of luck")
	91-100:	("Breastplate of command")
}

table specificArmour_major d100 {
	1-10:	("Plate armour of the deep")
	11-40:	("Banded mail of luck")
	41-60:	("Breastplate of command")
	61-80:	("Celestial armour")
	81-100:	("Demon armour")
}

for i in range(10) {
	print(armourAndShields_major());
}
