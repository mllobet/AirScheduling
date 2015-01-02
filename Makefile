BIN = main
SRC = main.cc Solver.cc
OBJ = ${SRC:.cc=.o}
CC = g++	

CFLAGS = -Wall -O3 -std=c++11

all: options ${BIN}

options:
	@echo "CFLAGS = ${CFLAGS}"
	@echo "CC     = ${CC}"

.cc.o:
	${CC} ${CFLAGS} -c $<

${BIN}: ${OBJ}
	${CC} -o $@ ${OBJ}

run: ${BIN}
	./${BIN}

clean:
	rm -f *.o ${BIN}

.PHONY: all options run clean
