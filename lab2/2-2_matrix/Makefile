CC=g++
CFLAGS=-I.
DEPS=Matrix.hpp r8lib.h r8mat_expm1.h
OBJ=main.o Matrix.o r8lib.cpp r8mat_expm1.cpp

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)