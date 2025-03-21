#Final executable name
TARGET = build/AlgebreDeBoule

#Compiler
CC = gcc

#Compilation args
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lm 

#Source
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)


# Transform .c files to .o files
OBJ = $(SRC:src/%.c=build/%.o)

# Regle principale
$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# Regle pour compiler les fichiers .c en .o
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@ 

# Cr�er le dossier build s'il n'existe pas
build:
	mkdir -p build

# Nettoyage
clean:
	rm -rf build/*

# Executer le programme
run: $(TARGET)
	./$(TARGET)