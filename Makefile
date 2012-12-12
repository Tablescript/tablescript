
OBJS =	ts.o

CC = g++
CCFLAGS = -g -c -Wall

all:	$(OBJS)
	make -C parser all
	make -C interpreter all
	$(CC) -o ts $(OBJS) parser/*.o interpreter/*.o -ldl
#$(CC) -Wl,--export-dynamic -o ts $(OBJS) parser/*.o interpreter/*.o
#$(CC) -Wl,--export-dynamic -o ts $(OBJS) parser/*.o interpreter/*.o -ldl
#make -C libs all

parser:
	make -C parser

tsparse: parser tsparse.o
	gcc -o tsparse tsparse.o parser/*.o

.cpp.o:
	$(CC) $(CCFLAGS) $<
.c.o:
	gcc $(CCFLAGS) $<

test: all force
	make -C test all

doc: Doxyfile
	doxygen Doxyfile

clean:
	rm -f *.o
	rm -f *~
	rm -f ts
	rm -f tsparse
	make -C parser clean
	make -C interpreter clean
	make -C libs clean
	rm -rf doc/*

force: ;
