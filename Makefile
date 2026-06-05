CC = g++
DFLGS = -O3 -flto
RFLGS = -Ofast -Wall -Wextra -fwhole-program -flto -freciprocal-math -fno-math-errno -ffinite-math-only -funsafe-math-optimizations -ffast-math -funroll-loops -march=native
LIBS = -lglfw -lGL
MAIN = main.cpp

.PHONY = ctdbg ctrel

ctdbg: main.cpp
	$(CC) $(DFLGS) $(MAIN) -o a.elf $(LIBS)
	./a.elf
	rm a.elf
ctrel: main.cpp
	$(CC) $(RFLGS) $(MAIN) -o a.elf $(LIBS)
	./a.elf
	rm a.elf
