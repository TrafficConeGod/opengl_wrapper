OBJECTS = $(patsubst %.cpp,%.o, $(shell find ./src/ -name *.cpp))
CC = g++
CFLAGS = -c -I src -Wall -std=c++17 -g

LDFLAGS = -pthread -lfmt -lGL -lglut -lGLEW -lglfw -lm -lX11 -lpthread -lXi -lXrandr

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
