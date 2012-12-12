// gems.ts
//

table gems d100 {
	1-25:	(gems1() + " [" + 4d4 + "gp value]")
	26-50:	(gems2() + " [" + (2d4 * 10) + "gp value]")
	51-70:	(gems3() + " [" + (4d4 * 10) + "gp value]")
	71-90:	(gems4() + " [" + (2d4 * 100) + "gp value]")
	91-99:	(gems5() + " [" + (4d4 * 100) + "gp value]")
	100:	(gems6() + " [" + (2d4 * 1000) + "gp value]")
}

table gems1 {
	1:	("banded agate")
	2:	("eye agate")
	3:	("moss agate")
	4:	("azurite")
	5:	("blue quartz")
	6:	("hematite")
	7:	("lapis lazuli")
	8:	("malachite")
	9:	("obsidian")
	10:	("rhodochrosite")
	11:	("tiger eye tourquise")
	12:	("freshwater (irregular) pearl")
}

table gems2 {
	1:	("bloodstone")
	2:	("carnelian")
	3:	("chalcedony")
	4:	("chrysoprase")
	5:	("citrine")
	6:	("iolite")
	7:	("jasper")
	8:	("moonstone")
	9:	("onyx")
	10:	("peridot")
	11:	("clear quartz")
	12:	("sard")
	13:	("sardonyx")
	14:	("rose quartz")
	15:	("smoky quartz")
	16:	("star rose quartz")
	17:	("zircon")
}

table gems3 {
	1:	("amber")
	2:	("amethyst")
	3:	("chrysoberyl")
	4:	("coral")
	5:	("red garnet")
	6:	("brown-green garnet")
	7:	("jade")
	8:	("jet")
	9:	("white pearl")
	10:	("golden pearl")
	11:	("pink pearl")
	12:	("silver pearl")
	13:	("red spinel")
	14:	("red-brown spinel")
	15:	("deep green spinel")
	16:	("tourmaline")
}

table gems4 {
	1:	("alexandrite")
	2:	("aquamarine garnet")
	3:	("violet garnet")
	4:	("black pearl")
	5:	("deep blue spinel")
	6:	("golden yellow topaz")
}

table gems5 {
	1:	("emerald")
	2:	("white opal")
	3:	("black opal")
	4:	("fire opal")
	5:	("blue sapphire")
	6:	("fiery yellow corundum")
	7:	("rich purple corundom")
	8:	("blue star sapphire")
	9:	("black start sapphire")
	10:	("star ruby")
}

table gems6 {
	1:	("clearest bright green emerald")
	2:	("blue-white diamond")
	3:	("canary diamond")
	4:	("pink diamond")
	5:	("brown diamond")
	6:	("blue diamond")
	7:	("jacinth")
}
