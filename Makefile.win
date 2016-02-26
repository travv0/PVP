ifeq ($(OS),Windows_NT)
	OBJS = *.c
	CC = gcc
	INCLUDE_PATHS = -IC:\mingw_dev_lib\include
	LIBRARY_PATHS = -LC:\mingw_dev_lib\lib
	COMPILER_FLAGS = -w -Wl,-subsystem,windows
	LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2
	OBJ_NAME = game.exe
else
	OBJS = *.c
	CC = gcc
	LINKER_FLAGS = -lSDL2
	OBJ_NAME = game
endif

all : $(OBJS)
	$(CC) $(OBJS) -Wall -g $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
