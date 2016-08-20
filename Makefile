TARGET = bin/prog
LIBS = -lraylib -lglfw3 -lGL -lopenal -lm -pthread -ldl -lX11 \
       -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor
INCLUDES = -I/usr/local/include -I./include
CC = clang
CFLAGS = -g -Wall -Werror

.PHONY: default all clean run

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard src/*.c))
#HEADERS = $(wildcard includes/*.h)

%.o: %.c# $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) $(INCLUDES) -o $@

clean:
	-rm -rf -- ./**/*.o
	-rm -rf -- ./**/*.d
	-rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)