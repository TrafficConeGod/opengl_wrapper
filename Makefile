OBJECTS = $(patsubst %.cpp,%.o, $(shell find . -name *.cpp))
CC = g++
CFLAGS = -c -I lib -I src -I src/gl -Wall -std=c++17 -g

LDFLAGS = -pthread -lfmt -lGL -lglut -lGLEW -lglfw -lm -lX11 -lpthread -lXi -lXrandr -lfmt

OUT_FILE = app.elf

.PHONY: build
build: $(OBJECTS)
	$(CC) -o $(OUT_FILE) $(OBJECTS) $(LDFLAGS)

run: build
	./$(OUT_FILE)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OBJECTS) $(OUT_FILE)
