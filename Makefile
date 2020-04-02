CC=g++
CFLAGS=-Wall -Wextra
LDFLAGS=-lglfw3 -lgdi32

SRC = $(wildcard src/*.cpp)	\
	  $(wildcard deps/glad/src/*.c)

INCLUDES = -Ideps/glad/include -Ideps/glfw-3.3/include -Ideps/glm/ -Ideps/stb -Ideps/
EXEC_NAME = kevengine

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

all: $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) $(INCLUDES) -o bin/$(TARGET_NAME)

run:
	./bin/$(EXEC_NAME)

.PHONY: clean
clean:
	$(DEL_CMD) ./bin/$(TARGET_NAME)