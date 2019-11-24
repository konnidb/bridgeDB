COMPILER=g++
CCFLAGS= -Wall

all: utils storage admin graph
	cd src/network && ./proto.sh
	cd src/network && $(MAKE)
network:
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
	rm -rf $(wildcard **/**.o)
ntclean:
	cd src/network && $(MAKE) clean