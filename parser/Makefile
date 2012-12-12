
OBJS = ts.tab.o \
		lex.yy.o \
		pexpression.o \
		plist.o \
		pstatement.o \
		pdump.o

CC = gcc
CCFLAGS = -c -Wall

all: $(OBJS)

.c.o:
	$(CC) $(CCFLAGS) $<

ts.tab.o: ts.tab.c
	$(CC) $(CCFLAGS) ts.tab.c
ts.tab.c: ts.y
	bison -d -v ts.y

lex.yy.o: lex.yy.c
	$(CC) $(CCFLAGS) lex.yy.c
lex.yy.c: ts.l
	flex ts.l

clean:
	rm -f *.o
	rm -f *~
	rm -f lex.yy.c
	rm -f ts.tab.c
	rm -f ts.tab.h
	rm -f main
	rm -f *.output

