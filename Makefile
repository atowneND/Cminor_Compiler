all: cminor

cminor: main.c lex.yy.o token.o
	gcc -g main.c lex.yy.o token.o -o cminor -lfl

lex.yy.o: scanner.l
	flex --header-file=lex.yy.h scanner.l
	gcc -g -c lex.yy.c

#parser.tab.c parser.tab.h: cminor.bison
#	yacc -d -bparser -v cminor.bison
parser.tab.c parser.tab.h: grammar.bison
	yacc -d -bparser -v grammar.bison

token.o: token.c
	gcc -g -c token.c

clean:
	rm lex.yy.c
	rm lex.yy.h
	rm *.o
	rm cminor
	rm parser.tab.h
	rm parser.tab.c
	rm parser.output
	rm results.log
