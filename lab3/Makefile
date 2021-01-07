CC=g++
CFLAGS=-Iinclude/ -Wall -std=c++14 -fopenmp -O3 -ftree-vectorize -fopt-info-vec-optimized
DEPS:=$(shell ls include/*.hpp )
OBJ:=$(patsubst src/%.cpp,bin/%.o,$(shell ls src/*.cpp))
LIB:=$(patsubst bin/main.o,,$(OBJ))

#$(info $$DEPS is [${DEPS}])
#$(info $$OBJ is [${OBJ}])

bin/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

lib: main
	ar rvs ../lab4-linked/lib/libdomain.a $(LIB)
