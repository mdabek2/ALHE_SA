CC := g++

TARGET := bin/run

SOURCES := $(shell find src -type f -name *.cpp)
OBJ := $(patsubst src/%, build/%, $(patsubst %.cpp, %.o, $(SOURCES)))
DEPS := include/*.h
CFLAGS := -std=c++11 -g -Wall -pedantic
INC := -I include

bin/run : $(OBJ) bin
	$(CC) $(CFLAGS) $(OBJ) -o bin/run

build/%.o : src/%.cpp $(DEPS) build
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build:
	mkdir build

bin:
	mkdir bin

clean:
	rm -r build
	rm -r bin

.PHONY: clean
