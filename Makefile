CC		= gcc
CFLAGS 	= -w -std=c99

OBJ = $(wildcard src/*.c)			\
	  $(wildcard src/core/components/*.c) 	\
	  $(wildcard src/core/renderer/*.c) 	\
	  $(wildcard src/core/utility/*.c) 	\
	  deps/glad/glad.c

INCLUDES = -Ideps/glfw-3.3/include

EXEC_NAME = kevin

ifeq ($(OS), Windows_NT)
	DEL_CMD = del
	LDFLAGS = -lopengl32 -lglfw3 -lgdi32
	TARGET_NAME = $(EXEC_NAME).exe
else
	DEL_CMD = rm

	LDFLAGS = `pkg-config --static --libs glfw3`

	UNAME = $(shell uname -s)
	ifeq ($(UNAME), Linux)
		TARGET_NAME = $(EXEC_NAME)
	endif

endif

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(INCLUDES) -o bin/$(TARGET_NAME)

.PHONY: clean
clean:
	$(DEL_CMD) ./bin/$(TARGET_NAME)

