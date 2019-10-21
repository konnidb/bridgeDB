COMPILER=g++
CCFLAGS= -Wall
langbuilder: 
	flex --outfile=src/query/interpreter/lex.yy.c src/query/interpreter/lexer/lang.l
	bison --defines=src/query/interpreter/parser.tab.h --output=src/query/interpreter/parser.tab.c src/query/interpreter/parser/parser.y
	$(COMPILER) -Wall src/query/interpreter/int_runner.cpp -o src/query/interpreter/interpreter.out
	./src/query/interpreter/interpreter.out
network: utils storage admin graph
	cd src/network && $(MAKE)
graph:
	cd src/graph && $(MAKE)
utils:
	cd src/utils && $(MAKE)
admin:
	cd src/admin && $(MAKE)
storage:
	cd src/storage && $(MAKE)
clean:
	rm -rf $(wildcard */*.o)
ntclean:
	cd src/network && $(MAKE) clean