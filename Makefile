CC = clang
FLAGS = -Wall -Wextra -O0

all: circuits
clean:
	rm -f circuits

circuits: circuit.c circuitGate.c subsets.h
	${CC} ${FLAGS} circuit.c circuitGate.c -lm -o circuits
