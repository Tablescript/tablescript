// art.ts
//

table art d100 {
	1-10:	(art1() + " [" + (1d10 * 10) + "gp value]")
	11-25:	(art2() + " [" + (3d6 * 10) + "gp value]")
	26-40:	(art3() + " [" + (1d6 * 100) + "gp value]")
	41-50:	(art4() + " [" + (1d10 * 100) + "gp value]")
	51-60:	(art5() + " [" + (2d6 * 100) + "gp value]")
	61-70:	(art6() + " [" + (3d6 * 100) + "gp value]")
	71-80:	(art7() + " [" + (4d6 * 100) + "gp value]")
	81-85:	(art8() + " [" + (5d6 * 100) + "gp value]")
	86-90:	(art9() + " [" + (1d4 * 1000) + "gp value]")
	91-95:	(art10() + " [" + (1d6 * 1000) + "gp value]")
	96-99:	(art11() + " [" + (2d4 * 1000) + "gp value]")
	100:	(art12() + " [" + (2d6 * 1000) + "gp value]")
}

table art1 {
	1:	("silver ewer")
	2:	("carved bone statuette")
	3:	("carved ivory statuette")
	4:	("finely wrought small gold bracelet")
}

table art2 {
	1:	("cloth of gold vestments")
	2:	("black velvet mask with numerous citrines")
	3:	("silver chalice with lapis lazuli gems")
}

table art3 {
	1:	("large well-done wool tapestry")
	2:	("brass mug with jade inlays")
}

table art4 {
	1:	("silver comb with moonstones")
	2:	("silver-plated steel longsword with jet jewel in hilt")
}

table art5 {
	1:	("carved harp of exotic wood with ivory inlay and zircon gems")
	2:	("solid gold idol (10lb)")
}

table art6 {
	1:	("gold dragon comb with red garnet eye")
	2:	("gold and topaz bottle stopper cork")
	3:	("ceremonial electrum dagger with a star ruby in the pommel")
}

table art7 {
	1:	("eyepatch with mock eye of sapphire and moonstone")
	2:	("fire opal pendant on a fine gold chain")
	3:	("old masterpiece painting")
}

table art8 {
	1:	("embroidered silk and velvet mantle with numerous moonstones")
	2:	("sapphire pendant on gold chain")
}

table art9 {
	1:	("embroidered and bejeweled glove")
	2:	("jeweled anklet")
	3:	("gold music box")
}

table art10 {
	1:	("golden circlet with four aquamarines")
	2:	("a string of small pink pearls (necklace)")
}

table art11 {
	1:	("jeweled gold crown")
	2:	("jeweled electrum ring")
}

table art12 {
	1:	("gold and ruby ring")
	2:	("gold cup set with emeralds")
}

