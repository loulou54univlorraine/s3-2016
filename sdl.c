/* */
 
#include <SDL/SDL.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
#include "moteur.h"

SDL_Surface* ecran ,* texture, * map,* lecture_texture = NULL;

SDL_Surface* surface = NULL;

Uint8* touches_lues;

void sdl_ecran_init(int largeur, int hauteur) {
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("Probleme initialisation SDL: %s\n",SDL_GetError());
    SDL_Quit();
    exit(1);
  }


  ecran = SDL_SetVideoMode(largeur,hauteur,32,SDL_HWSURFACE | SDL_HWPALETTE);
  if(ecran == NULL) {
    printf("Probleme configuration mode video: %s\n",SDL_GetError());
    SDL_Quit();
    exit(1);
  }

SDL_WM_SetCaption("raycasting", NULL);

lecture_texture = IMG_Load("textures/murs.bmp");
/* lecture surface*/
 
if(lecture_texture == NULL)
{
    printf("Erreur de chargement de la texture : %s",SDL_GetError());
    exit(1);
}
  else {  texture = SDL_ConvertSurface( lecture_texture, ecran->format, SDL_HWSURFACE | SDL_HWPALETTE ); 
    SDL_FreeSurface(lecture_texture);

  if( texture == NULL ) { 
  printf( "Erreur optimisation  de la texture  %s\n",  SDL_GetError() ); 
   exit(1);
} 
 
}

}

/* Dessin d'une ligne verticale depuis (x,y1) jusqu'a (x,y2), en couleur */

void sdl_ligne_verticale(int x, int y1, int y2, int r, int v, int b) {

}


Uint32 get_pixel32( SDL_Surface *surface, int x, int y ) { 
Uint32 *pixels = (Uint32 *)surface->pixels;
return pixels[ ( y * surface->w ) + x ];
 }

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel ) {
Uint32 *pixels = (Uint32 *)surface->pixels;
pixels[ ( y * surface->w ) + x ] = pixel; }



Uint32 obtenirPixel(SDL_Surface *surface, int x, int y){
int nbOctetsParPixel = surface->format->BytesPerPixel;
Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;

  switch(nbOctetsParPixel)

    {
        case 1:
        return *p;
       case 2:
 return *(Uint16 *)p;
 case 3:
if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
return p[0] << 16 | p[1] << 8 | p[2];
 else
return p[0] | p[1] << 8 | p[2] << 16;
case 4:
return *(Uint32 *)p;
default:
return 0; 
}
}

void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)

{
 int nbOctetsParPixel = surface->format->BytesPerPixel;
 Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;


    switch(nbOctetsParPixel)

    {
 case 1:
*p = pixel;
break;
 case 2:
 *(Uint16 *)p = pixel;
 break;
case 3:
if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
 {
 p[0] = (pixel >> 16) & 0xff;
p[1] = (pixel >> 8) & 0xff;
p[2] = pixel & 0xff;
}
else
{
p[0] = pixel & 0xff;
p[1] = (pixel >> 8) & 0xff;
p[2] = (pixel >> 16) & 0xff;
}
break;
case 4:
 *(Uint32 *)p = pixel;
 break;
}
}



void sdl_ligne_verticale_texture(int x, int texX,int type_cote,int y1, int y2){
SDL_LockSurface(texture);
SDL_LockSurface(ecran);

SDL_UnlockSurface(texture);
SDL_UnlockSurface(ecran);
}

void sdl_ecran_mise_a_jour() {

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

  SDL_FreeSurface(texture);
  SDL_Quit();
}

