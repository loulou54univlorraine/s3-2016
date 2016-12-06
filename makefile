all: moteur.o fichiers.o sdl.o main.c moteur.h sdl.h
	gcc moteur.o fichiers.o sdl.o main.c -lSDL -lSDL_image  -lSDL_ttf -lm -o moteur3D

moteur.o: moteur.c sdl.h
	gcc -c moteur.c -O3

sdl.o: sdl.c
	gcc -c sdl.c  -lSDL -lSDL_ttf -lm

fichier.o: fichiers.c constantes.h fichiers.h
	gcc -c fichiers.c 
clean:
	rm sdl.o moteur.o fichiers.o moteur3D
