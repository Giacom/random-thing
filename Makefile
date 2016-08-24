# Window users, please use a terminal with Unix commands.

BIN = bin
TARGET = $(BIN)/shader-canvas

LINUX_LIBS = -lraylib -lglfw3 -lGL -lopenal -lm -pthread -ldl -lX11 \
	-lXrandr -lXinerama -lXxf86vm -lXcursor
WIN_LIBS = -lraylib -lglfw3 -lopengl32 -lopenal32 -lgdi32
WIN_LIB_PATHS = -l C:\dev\libs # Linux users, put yours in /usr/local/lib

ifeq ($(OS),Windows_NT)
	LIBS = $(WIN_LIBS)
else
	LIBS = $(LINUX_LIBS)
endif

MKDIR = mkdir -p $(BIN)

# Win only
RAYLIB_WIN_PATH=C:\Users\giaco\raylib

INCLUDES = -I/usr/local/include -I./include -I$(RAYLIB_WIN_PATH)\include -I$(RAYLIB_WIN_PATH)\raylib\src\external\glfw3\include -I$(RAYLIB_WIN_PATH)\raylib\src\external\openal_soft\include
CC = clang
ifeq ($(OS),Windows_NT)
	CC = gcc # Should be GCC compatible
endif
CFLAGS = -g -Wall -Werror -std=c99

.PHONY: default all clean run

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard src/*.c))
#HEADERS = $(wildcard includes/*.h)

%.o: %.c# $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(MKDIR)
	$(CC) $(OBJECTS) -Wall $(WIN_LIB_PATH) $(LIBS) $(INCLUDES) -o $@

clean:
	-rm -rf -- ./$(BIN)
	-rm -f -- ./**/*.o
	-rm -f -- ./**/*.d

run: $(TARGET)
	./$(TARGET)
