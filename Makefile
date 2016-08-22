MKDIR = mkdir -p
BIN = bin
TARGET = $(BIN)/shader-canvas
LIBS = -lraylib -lglfw3 -lGL -lopenal -lm -pthread -ldl -lX11 \
       -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor
INCLUDES = -I/usr/local/include -I./include
CC = clang # Should be GCC compatible
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
	$(MKDIR) $(BIN)
	$(CC) $(OBJECTS) -Wall $(LIBS) $(INCLUDES) -o $@

clean:
	-rm -rf -- ./$(BIN)
	-rm -f -- ./**/*.o
	-rm -f -- ./**/*.d

run: $(TARGET)
	./$(TARGET)