CC=g++
CFLAGS=-I. -O3 -Wall -fopenmp -ftree-vectorize
DEPS=Matrix.hpp r8lib.h r8mat_expm1.h
OBJ=main.o Matrix.o r8lib.cpp r8mat_expm1.cpp

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

lib:
	ar rvs ../../lab4-linked/lib/libmatrix.a Matrix.o