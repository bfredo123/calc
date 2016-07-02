#OBJS=main.o calc.lex.o calc.y.o generator.o calcasm.o
OBJS=main.o calc.lex.o calc.y.o stacker.o 

CFLAGS=-g

calc: $(OBJS)
	g++ -g -o $@ $(OBJS) -ll -lm

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

%.o: %.cc
	gcc $(CFLAGS) -c $< -o $@

#main.o: main.c
#	gcc -c $<

#generator.o: generator.c
#	gcc $(CFLAGS)-c $<

calcasm.o: calcasm.asm
	nasm -f elf64 -o $@ $< 

calc.y.o: calc.y global.h
	bison -d calc.y
	mv calc.tab.h calc.h
	mv calc.tab.c calc.y.c
	gcc $(CFLAGS) -c calc.y.c -o calc.y.o

calc.lex.o: calc.lex calc.y
	flex calc.lex
	mv lex.yy.c calc.lex.c
	gcc $(CFLAGS) -c calc.lex.c -o calc.lex.o


