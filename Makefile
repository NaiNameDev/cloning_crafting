CC = g++
DFLGS = -O3 -flto
RFLGS = -Ofast -Wall -Wextra -fwhole-program -flto -freciprocal-math -fno-math-errno -ffinite-math-only -funsafe-math-optimizations -ffast-math -funroll-loops -march=native
LIBS = -lglfw -Iinclude
DEF = -DIMG_ENABLE
MAIN = main.cpp src/glad.c

.PHONY = ctdbg ctrel

ctdbg: main.cpp
	$(CC) $(DFLGS) $(DEF) $(MAIN) -o a.elf $(LIBS)
	./a.elf
	rm a.elf
ctrel: main.cpp
	$(CC) $(RFLGS) $(DEF) $(MAIN) -o a.elf $(LIBS)
	./a.elf
	rm a.elf
