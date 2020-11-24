CC=g++
CFLAGS=-Iinclude/ -Wall -std=c++14 -fopenmp -O2
DEPS:=$(shell ls include/*.hpp )
OBJ:=$(patsubst src/%.cpp,bin/%.o,$(shell ls src/*.cpp))

#$(info $$DEPS is [${DEPS}])
#$(info $$OBJ is [${OBJ}])

bin/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)