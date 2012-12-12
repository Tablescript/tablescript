
OBJS = 	DiceTest.o

CC = g++
CCFLAGS = -g -c -Wall -Werror -I../

all: $(OBJS)
	gcc -o testrunner $(OBJS) ../parser/*.o ../interpreter/*.o -ldl -lcppunit
	testrunner

.cpp.o:
	$(CC) $(CCFLAGS) $<

clean:
	rm -f *.o
	rm -f *~

