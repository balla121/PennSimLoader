#
# Makefile for CIT 593 LC4 project
#

# this rule invokes the lc4: rule below
#
all: lc4

# this rule partially compiles lc4_memory.c, to the target: lc4_memory.o
#
lc4_memory.o: lc4_memory.c lc4_memory.h
	clang -g -c lc4_memory.c

lc4_loader.o: lc4_loader.c lc4_loader.h
	clang -g -c lc4_loader.c

lc4_disassembler.o: lc4_disassembler.c lc4_disassembler.h
	clang -g -c lc4_disassembler.c

lc4: lc4.c lc4_memory.o lc4_loader.o lc4_disassembler.o
	clang -g -o lc4 lc4.c lc4_memory.o lc4_loader.o lc4_disassembler.o


clean:
	rm -rf *.o

clobber: clean
	rm -rf lc4
	
