
// gross hack until I add a list-sorting built-in function
function sort(list) {

	result = [];
	seen = {};

	for i in range(len(list)) {

		maxIndex = 0;
		maxElement = 0;
		for i in range(len(list)) {

			if(hasKey(seen, str(i)) == 0) {

				if(list[i] > maxElement) {

					maxElement = list[i];
					maxIndex = i;
				}
			}
		}

		seen[str(maxIndex)] = 1;
		append(result, maxElement);
	}

	return result;
}

table class {
	1:	("cleric")
	2:	("rogue")
	3:	("barbarian")
}

table race {
	1:	(["human",           [ 0, 0, 0, 0, 0, 0]])
	2:	(["elf",             [ 0, 2,-2, 0, 0, 0]])
	3:	(["dwarf",           [ 0, 0, 2, 0, 0,-2]])
	4:	(["halfling",        [-2, 2, 0, 0, 0, 0]])
	5:	(["half-elf",        [ 0, 0, 0, 0, 0, 0]])
	6:	(["half-orc",        [ 2, 0, 0,-2, 0,-2]])
	7:	(["gnome",           [-2, 0, 2, 0, 0, 0]])
}

function getPriorities(class) {
	if(class == "cleric") {
		return ["wis", "cha", "str", "int", "con", "dex"];
	} elseif(class == "rogue") {
		return ["dex", "int", "cha", "str", "con", "wis"];
	} elseif(class == "barbarian") {
		return ["str", "con", "dex", "cha", "wis", "int"];
	}
}

function getBonus(attr) {
	bonus = (attr - 10) / 2;
	if(bonus >= 0) {
		return ("+" + bonus);
	}
	return str(bonus);
}

character = {};

// generate a random class
character["class"] = class();

raceBits = race();
character["race"] = raceBits[0];
racialBonuses = raceBits[1];

// get the attribute priorities for that class
priorities = getPriorities(character["class"]);

// roll attributes
rolls = [];
for i in range(6) {
	append(rolls, 4D6L1);
}

// sort rolls
sortedRolls = sort(rolls);

// apply rolls
for i in range(6) {
	character[priorities[i]] = sortedRolls[i];
}

// apply racial bonuses
attrs = ["str", "dex", "con", "int", "wis", "cha"];
for i in range(6) {
	if(racialBonuses[i] != 0) {
		print("adding " + racialBonuses[i] + " to " + attrs[i] + " (" + character[attrs[i]] + ")");
		character[attrs[i]] = character[attrs[i]] + racialBonuses[i];
	}
}

// dump results
print("Class: " + character["class"]);
print("Race: " + character["race"]);
print("Str: " + character["str"] + " (" + getBonus(character["str"]) + ")");
print("Dex: " + character["dex"] + " (" + getBonus(character["dex"]) + ")");
print("Con: " + character["con"] + " (" + getBonus(character["con"]) + ")");
print("Int: " + character["int"] + " (" + getBonus(character["int"]) + ")");
print("Wis: " + character["wis"] + " (" + getBonus(character["wis"]) + ")");
print("Cha: " + character["cha"] + " (" + getBonus(character["cha"]) + ")");
