PROJ_NAME=sdb

# .c files
C_SOURCE=$(wildcard ./src/*.c)

# .h files
H_SOURCE=$(wildcard ./src/*.h)

# Object files
OBJ=$(subst .c,.o,$(subst src,obj,$(C_SOURCE)))

# Compiler
CC=gcc

# Compiler flags
CC_FLAGS = -c		\
	   -Wall	\
	   -pedantic	

# Linker flags
L_FLAGS= 

# Compilation and linking

all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo -e '\033[1;37mBuilding binary using GCC Linker:\033[0m $@'
	$(CC) -o $@ $^ $(L_FLAGS)
	@ echo
	@ echo -e '\033[1;37mFinished building binary:\033[0m $@'

./obj/%.o: ./src/%.c ./src/%.h
	@ echo -e '\033[1;37mBuilding target using GCC compiler:\033[0m $<'
	$(CC) -o $@ $< $(CC_FLAGS)
	@ echo

./obj/main.o: ./src/main.c $(H_SOURCE)
	@ echo -e '\033[1;37mBuilding target using GCC compiler:\033[0m $<'
	$(CC) -o $@ $< $(CC_FLAGS)
	@ echo

debug: L_FLAGS += -DDEBUG -g
debug: CC_FLAGS += -DDEBUG -g
debug: objFolder $(PROJ_NAME)

objFolder:
	@ mkdir -p obj

remake: clean objFolder $(PROJ_NAME)

clean:
	@ echo -e '\033[1;37mCleaning up files...\033[0m'
	@ rm -rf ./obj/*.o *~ $(PROJ_NAME)
	@ rm tempfile
	@ rmdir obj
