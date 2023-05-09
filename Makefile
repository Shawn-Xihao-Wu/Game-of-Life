CC = gcc
CFLAGS = -I/opt/homebrew/Cellar/sdl2/2.26.5/include/
LDFLAGS = -L/opt/homebrew/Cellar/sdl2/2.26.5/lib
LDLIBS = -lSDL2

Game-of-Life: main.c sdl_helpers.c sparse_grid.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@

clean:
	rm -f Game-of-Life