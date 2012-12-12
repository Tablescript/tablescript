
import "string";

s = "I'm a lumberjack and I'm okay.";
print("Splitting \"%s\"..." % [s]);
l = split(s);
for i in range(len(l)) {
	print("Element %d: \"%s\"" % [i, l[i]]);
}

s = "  	\tdoofus   ";
print("Trimming \"%s\"..." % [s]);
print("\"%s\"" % [trim(s)]);

print("Trimming \"%s\" with \" \\tdo\"..." % [s]);
print("\"%s\"" % [trim(s, " \tdo")]);

print("Left-trimming \"%s\"..." % [s]);
print("\"%s\"" % [ltrim(s)]);

print("Left-trimming \"%s\" with \" \\tdo\"..." % [s]);
print("\"%s\"" % [ltrim(s, " \tdo")]);

print("Right-trimming \"%s\"..." % [s]);
print("\"%s\"" % [rtrim(s)]);

print("Right-trimming \"%s\" with \" \\tdo\"..." % [s]);
print("\"%s\"" % [rtrim(s, " \tdo")]);

