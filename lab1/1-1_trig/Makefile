CC=gcc
CFLAGS=-I.-lm
DEPS = taylor.hpp
OBJ = trig.o taylor.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)