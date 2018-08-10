CC=gcc
DEPS=main.h msleep.h sprite.h salloc.h
OBJ=main.o msleep.o sprite.o salloc.o
CFLAGS=
SDL=SDL2-2.0.0

%.o: %.c $(DEPS)
	$(CC) -c -I include -L lib -l $(SDL) -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -I include -L lib -l $(SDL) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf main
	
