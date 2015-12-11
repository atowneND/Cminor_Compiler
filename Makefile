CMINOR_EXEC=bar
LFLAGS=
CMINOR_OBJECT_FILES=library.o
OBJECT_FILES=token.o decl.o expr.o type.o stmt.o param_list.o reg.o scope.o hash_table.o

all: $(CMINOR_EXEC) cminor

# generate executable
$(CMINOR_EXEC): $(CMINOR_EXEC).o $(CMINOR_OBJECT_FILES)
	gcc $< -o $@ $(LFLAGS) $(CMINOR_OBJECT_FILES)

# compile assembly into .o
$(CMINOR_EXEC).o: $(CMINOR_EXEC).s
	gcc -c $< -o $@

# run CMINOR compiler, generate assembly
$(CMINOR_EXEC).s: $(CMINOR_EXEC).cminor cminor
	./cminor -codegen $< $@
	
# generate cminor
cminor: main.o scanner.o parser.tab.o $(OBJECT_FILES)
	gcc -g main.o scanner.o parser.tab.o $(OBJECT_FILES) -o cminor -lm -lfl

# generate that cminor depends on
%.o: %.c *.h
	gcc -g -Wall -c $< -o $@

# generate parser
parser.tab.c parser.tab.h: grammar.bison
	yacc -d -bparser -v -t grammar.bison

# generate scanner
scanner.c: scanner.l parser.tab.h
	flex -oscanner.c scanner.l

clean:
	rm -f parser.tab.* parser.output *.o cminor scanner.c $(CMINOR_EXEC)
