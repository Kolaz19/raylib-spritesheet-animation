CC = gcc
LIB_DIR = ./lib/ #where your libraylib.a file is
INCL_DIR = ./include/

LINKERS =-L $(LIB_DIR) -lraylib -lopengl32 -lgdi32 -lwinmm
OUTPUT_FLAGS = -Wall -std=c99 -Wno-missing-braces
CFLAGS = -static -fdiagnostics-color=always

build_debug: main.o rect.o borders.o Animation.o
	$(CC) $(CFLAGS) -g -o demo $(OUTPUT_FLAGS) main.o rect.o borders.o Animation.o $(LINKERS)

build_static_lib: Animation.o
	ar rcs librayanim.a Animation.o

main.o: main.c
	$(CC) -c main.c

rect.o: rect.c
	$(CC) -c rect.c

borders.o: borders.c
	$(CC) -c borders.c

Animation.o: Animation.c
	$(CC) -c Animation.c

clean: 
	rm -f demo *.o

run: 
	./demo
