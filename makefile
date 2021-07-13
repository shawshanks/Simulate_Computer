CC = /usr/bin/gcc-7
CFLAGS = -Wall -g -O2 -Werror -std=gnu99

# EXE = program

EXECUTABLE = csapp

SRC = ./src



CODE = ./src/Memory/instruction.c ./src/Disk/code.c ./src/Memory/dram.c ./src/CPU/mmu.c ./src/main.c

.PHONY:csapp

csapp:
	$(CC) $(CFLAGS) -I$(SRC) $(CODE) -o $(EXECUTABLE)

run:
	./$(EXECUTABLE)