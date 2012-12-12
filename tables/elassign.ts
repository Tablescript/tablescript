
l = [1,2,3,4,5];

s = "";
for i in l {
	s = s + i + " ";
}
print("Original: " + s);

s = "";
for i in range(5) {
	s = s + l[i] + " ";
}
print("Using list elements: " + s);

l[0] = 147;
s = "";
for i in range(5) {
	s = s + l[i] + " ";
}
print("After modifying an element: " + s);

function printMap(m) {
	for i in keys(m) {
		print("m[" + i + "] = " + m[i]);
	}
}

m = {"first" : 1, "second" : 2, "third" : 3};
printMap(m);

m["fourth"] = 4;
printMap(m);

m["first"] = 7;
printMap(m);
