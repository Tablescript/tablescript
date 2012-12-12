
rolls = [0,0,0,0,0,0];
count = 0;
while(count < 1000000) {
	roll = d6;
	rolls[roll - 1] = rolls[roll - 1] + 1;
	++count;
}

for i in range(6) {
	print("%d: %d" % [i + 1, rolls[i]]);
}

