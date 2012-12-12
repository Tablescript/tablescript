
table returnsLists {
	1:	([1,2,3,4])
	2:	([5,6,7,8,9])
}

s = "";
for i in returnsLists() {
	s = s + i;
}
print(s);

print(returnsLists());

table complex(i) {
	1:	{i = 12;} (i)
	2:	{j = 147;} (j)
}

q = 6;
print(complex(q));
print(q);

