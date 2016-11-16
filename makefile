all: moteur.o sdl.o main.c moteur.h sdl.h
	gcc moteur.o sdl.o main.c -lSDL -lSDL_image -lm -o moteur3D

moteur.o: moteur.c sdl.h
	gcc -c moteur.c -O3

sdl.o: sdl.c
	gcc -c sdl.c -lSDL -lSDL_image 

clean:
	rm sdl.o moteur.o moteur3D
