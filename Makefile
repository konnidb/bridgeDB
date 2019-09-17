COMPILER=g++
CCFLAGS= -Wall
langbuilder: 
	flex --outfile=src/query/interpreter/lex.yy.c src/query/interpreter/lexer/lang.l
	bison --defines=src/query/interpreter/parser.tab.h --output=src/query/interpreter/parser.tab.c src/query/interpreter/parser/parser.y
	$(COMPILER) -Wall src/query/interpreter/int_runner.cpp -o src/query/interpreter/interpreter.out
	./src/query/interpreter/interpreter.out
network:
	cd src/network && $(MAKE)