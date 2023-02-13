CC = gcc
LIB_DIR = ./lib/ #where your libraylib.a file is
INCL_DIR = ./include/
EX_DIR = ./example/
OBJ_DIR = ./object_files/

LINKERS =-L $(LIB_DIR) -lraylib -lopengl32 -lgdi32 -lwinmm
OUTPUT_FLAGS = -Wall -std=c99 -Wno-missing-braces
CFLAGS = -static -fdiagnostics-color=always

build_debug: $(OBJ_DIR)main.o $(OBJ_DIR)Animation.o
	$(CC) $(CFLAGS) -o $(EX_DIR)demo $(OUTPUT_FLAGS) $(OBJ_DIR)main.o $(OBJ_DIR)Animation.o $(LINKERS)

build_lib: $(OBJ_DIR)Animation.o
	ar rcs librayanim.a $(OBJ_DIR)Animation.o

$(OBJ_DIR)main.o: $(EX_DIR)main.c
	$(CC) -c $(EX_DIR)main.c
	mv main.o $(OBJ_DIR)

$(OBJ_DIR)Animation.o: Animation.c
	$(CC) -c Animation.c
	mv Animation.o $(OBJ_DIR)

clean: 
	rm -f ./object_files/*.o
	rm -f ./example/demo.exe

run: 
	$(EX_DIR)demo
