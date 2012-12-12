
OBJS = 	math.o

CC = g++
CCFLAGS = -g -fPIC -c -Wall -I../../interpreter

all: $(OBJS)
	$(CC) -shared -Wl,-soname,libmath.so.1 -o math.so $(OBJS)

.cpp.o:
	$(CC) $(CCFLAGS) $<

clean:
	rm -f *.o
	rm -f *~
	rm -f *.so
