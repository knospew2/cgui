CC=gcc
DEPS=main.h msleep.h sprite.h salloc.h keys.h env.h mouse.h 
OBJ=main.o msleep.o sprite.o salloc.o keys.o env.o mouse.o 
CFLAGS=
SDL=SDL2-2.0.0

%.o: %.c $(DEPS)
	$(CC) -c -I include -L lib -l $(SDL) -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -I include -L lib -l $(SDL) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf main
	
