# $Id$

MKFILE = Makefile
DEPSFILE = ${MKFILE}.deps

GCC = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS = gcc -MM
GRIND = valgrind --leak-check=full

CHEADER = inssort.h
SOURCES = inssort.h numsort.c inssort.c linesort.c ${MKFILE}

SUBMIT = submit cmps012b-wm.w14 lab9

all : numsort linesort

numsort : numsort.o inssort.o
	${GCC} -o $@ numsort.o inssort.o

linesort : linesort.o inssort.o
	${GCC} -o $@ numsort.o inssort.o

%.o : %.c
	cid + $<
	${GCC} -c $<

ci : ${SOURCES}
	cid + ${SOURCES}
	- checksource $<

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}
