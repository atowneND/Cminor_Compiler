OBJECT_FILES=token.o decl.o expr.o type.o stmt.o param_list.o scope.o symbol.o hash_table.o

# The top level rule indicates how to link everything together into calc

all: main.o scanner.o parser.tab.o $(OBJECT_FILES)
	gcc -g main.o scanner.o parser.tab.o $(OBJECT_FILES) -o cminor -lm -lfl

# This pattern indicates that any .o file depends
# upon the .c file of the same name, and all of the .h files.
# So, if a .o file is needed, it is built automatically.

%.o: %.c *.h
	gcc -g -Wall -c $< -o $@

# Only the files generated by flex and bison need explicit rules.

scanner.c: scanner.l parser.tab.h
	flex -oscanner.c scanner.l

parser.tab.c parser.tab.h: grammar.bison
	yacc -d -bparser -v -t grammar.bison

# clean causes all intermediate files to be deleted.

clean:
	rm -f parser.tab.* parser.output *.o cminor scanner.c
