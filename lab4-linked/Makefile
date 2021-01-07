CC=g++
LIBS=-L../lab3/bin/ -L../lab2/2-2_matrix/ -ldomain -lmatrix
INCLUDES=-Iinclude/ -I../lab3/include/ -I../lab2/2-2_matrix/
CFLAGS:=-Wall -std=c++14 -fopenmp -O3 $(INCLUDES) 
DEPS:=$(shell ls include/*.hpp)
OBJ:=$(patsubst src/%.cpp,bin/%.o,$(shell ls src/*.cpp))


# $(info $$DEPS is [${DEPS}])
# $(info $$OBJ is [${OBJ}])

bin/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
