all: cminor

cminor: main.c lex.yy.o token.o
	gcc -g main.c lex.yy.o token.o -o cminor -lfl

lex.yy.o: scanner.l
	flex --header-file=lex.yy.h scanner.l
	gcc -g -c lex.yy.c

token.o: token.c
	gcc -g -c token.c

clean:
	rm lex.yy.c
	rm lex.yy.h
	rm *.o
	rm cminor
