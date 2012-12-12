table testTable(first, second) {
	1:	(first + "-" + second)
	2:	(second + "-" + first)
}

for i in range(10) {
	print(testTable("yabba", "dabba"));
}
