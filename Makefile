CC=g++
CFLAGS=-Wall -Wextra -O3
LDFLAGS=-lglfw3 -lgdi32

SRC = $(wildcard core/*.cpp)		\
	  $(wildcard core/**/*.cpp)		\
	  $(wildcard thirdparty/glad/src/*.c)

INCLUDES = -Ithirdparty/glad/include -Ithirdparty/glfw-3.3/include -Ithirdparty/glm/ -Ideps/stb -Ithirdparty/ -Ithirdparty/eigen-3.3.7
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
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) $(INCLUDES) -o build/$(TARGET_NAME)

run:
	./build/${EXEC_NAME}

.PHONY: clean
clean:
	$(DEL_CMD) ./build/$(TARGET_NAME)
	$(DEL_CMD) $(src.o)
