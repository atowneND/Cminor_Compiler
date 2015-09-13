all: cminor

cminor: main.c lex.yy.o token.o
	gcc main.c lex.yy.o token.o -o cminor -lfl

lex.yy.o:
	gcc -c lex.yy.c

token.o:
	gcc -c token.c

clean:
	rm *.o
	rm cminor
