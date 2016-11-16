#include <SDL/SDL.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
#include "moteur.h"
#define texWidth 256
#define texHeight 256
SDL_Surface* ecran ,* texture[10]={NULL}, * map,* loadedSurface = NULL;
SDL_Surface* surface = NULL;
Uint8* touches_lues;
/* Fonction d'initialisation de la SDL et de la fenetre d'affichage */
void sdl_ecran_init(int largeur, int hauteur) {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Probleme initialisation SDL: %s\n",SDL_GetError());
		SDL_Quit();
		exit(1);
	}
/* Mode video : fenetre couleurs 32 bits de taille hauteur * largeur */
	ecran = SDL_SetVideoMode(largeur,hauteur,32,SDL_HWSURFACE | SDL_HWPALETTE);
	if(ecran == NULL) {
		printf("Probleme configuration mode video: %s\n",SDL_GetError());
		SDL_Quit();
		exit(1);
	}
	SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
	loadedSurface = IMG_Load("textures/mur1d.bmp");
	if(loadedSurface == NULL)
	{
		printf("Erreur de chargement de l'image : %s",SDL_GetError());
		exit(1);
	}
	else {  texture[1] = SDL_ConvertSurface( loadedSurface, ecran->format, SDL_HWSURFACE | SDL_HWPALETTE );
		SDL_FreeSurface(loadedSurface);
		if( texture[1] == NULL ) {
			printf( "Unable to optimize image ! SDL Error: %s\n",  SDL_GetError() );
			exit(1);
		}
	}
}
/* Dessin d'une ligne verticale depuis (x,y1) jusqu'a (x,y2), en couleur */
void sdl_ligne_verticale(int x, int y1, int y2, int r, int v, int b) {
	int y;
	Uint32 colorSDL = SDL_MapRGB(ecran->format,r,v,b);
	Uint32* bufp;
	bufp = (Uint32*)ecran->pixels + y1 * ecran->pitch / 4 + x;
	for(y = y1; y <= y2; y++) {
		*bufp = colorSDL;
		bufp += ecran->pitch / 4;
	}
}
Uint32 get_pixel32( SDL_Surface *surface, int x, int y ) {
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[ ( y * surface->w ) + x ];
}
void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel ) {
	Uint32 *pixels = (Uint32 *)surface->pixels;
	pixels[ ( y * surface->w ) + x ] = pixel; }
	void sdl_ligne_verticale_texture(int x, int texX,int type_cote,int y1, int y2,int Y3){
		SDL_LockSurface(texture[1]);
		SDL_LockSurface(ecran);
		int y,w;
		double rx,ry;
		Uint8 r, v, b,a;
		Uint32 pixel;
		ry = Y3*1.0/texture[1]->h;
		for(y = y1; y < y2; y++) {
			w = ((y-y1))/ry;
			pixel= get_pixel32(texture[1],texX,w);
			if (!type_cote)
			{
				SDL_GetRGB(pixel, texture[1]->format, &r, &v, &b);
				pixel=SDL_MapRGBA(ecran->format, r >>1, v>>1, b>>1, a);
			}
			put_pixel32(ecran,x,y,pixel);
		}
		SDL_UnlockSurface(texture[1]);
		SDL_UnlockSurface(ecran);
	}
/* Fonction pour mettre a jour l'affichage */
	void sdl_ecran_mise_a_jour() {
		SDL_Rect positionFond;
		positionFond.x = 0;
		positionFond.y = 0;
		SDL_UpdateRect(ecran,0,0,0,0);
		SDL_FillRect(ecran,NULL,0);
	}
/* Lit les touches appuyees et place l'information dans touches_lues */
	void sdl_touches_lire() {
		touches_lues = SDL_GetKeyState(NULL);
	}
/* Verifie si la touche en paramettre a ete appuyee, renvoie 1 (oui), 0 (non) */
	int sdl_touches_appuyee(int touche) {
		return (touches_lues[touche] != 0);
	}
/* Retourne le nombre de millisecondes depuis le debut du programme */
	unsigned long sdl_date() {
		return SDL_GetTicks();
	}
/* Retourne 1 si la fenetre a ete fermee */
	int sdl_fin() {
		int done = 0;
		SDL_Event event;
		if(!SDL_PollEvent(&event))
			return 0;
		if(event.type == SDL_QUIT)
			done = 1;
		return done;
	}
/* Liberer les ressources de la SDL */
	void sdl_quitter() {
		SDL_FreeSurface(texture[1]);
		SDL_Quit();
	}
