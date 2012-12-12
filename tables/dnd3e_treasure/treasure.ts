// treasure.ts
//

import "gems";
import "art";

table treasure1Coins d100 {
	1-14:
	15-29:	((d6 * 1000) + "cp")
	30-52:	((d8 * 100) + "sp")
	53-95:	((2d8 * 10) + "gp")
	96-100:	((d4 * 10) + "pp")
}

table treasure1Goods d100 {
	1-9:
	10-95:	(gems())
	96-100:	(art())
}

table treasure1Items d100 {
	1-100:	("wnakity")
}

table treasure2Coins d100 {
	1-100:	("huh")
}

table treasure2Goods d100 {
  1-100:  ("goods")
}

table treasure2Items d100 {
  1-100:  ("items")
}

treasureTables = [
	[treasure1Coins, treasure1Goods, treasure1Items],
	[treasure2Coins, treasure2Goods, treasure2Items]];

print( len( ARGV ) );
if ( len( ARGV ) != 3 )
{

    print( "Usage: treasure.ts <level>" );
    exit;
}

level = int(ARGV[2]);

tables = treasureTables[level - 1];

print("Coins: " + tables[0]());
print("Goods: " + tables[1]());
print("Items: " + tables[2]());
