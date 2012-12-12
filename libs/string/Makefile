
OBJS = 	string.o

CC = g++
CCFLAGS = -g -fPIC -c -Wall -I../../interpreter

all: $(OBJS)
	$(CC) -shared -Wl,-soname,libstring.so.1 -o string.so $(OBJS)

.cpp.o:
	$(CC) $(CCFLAGS) $<

clean:
	rm -f *.o
	rm -f *~
	rm -f *.so
