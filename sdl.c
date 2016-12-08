/*Sébastien André et Louis Dudot
  Basé sur les codes de Lode Vandevenne
  http://lodev.org/cgtutor/*/
#include <SDL/SDL.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "moteur.h"
#include "sdl.h"
#include "constantes.h"
// init 
SDL_Surface* ecran ,* mur[4]={NULL},* fruit[7]={NULL},*sol[2]={NULL},* ciel={NULL},* fantome={NULL}, *texte = NULL,*texte2 = NULL;
SDL_Surface *surface[10] = {NULL};
TTF_Font *police = NULL;
TTF_Font *police2 = NULL;
Uint8* touches_lues = NULL;
SDL_Rect position[10] ,copy;
SDL_Color couleurTexte = {255,255,0};
SDL_Color couleurTexte2  = {255,0,0};
SDL_Color couleurTexte3  = {255,0,255};
SDL_Rect positiontexte;
SDL_Rect positiontexte2;
char chaineTexte[50];
Score score={3,0,1};
int bool1 = 0;
int bool2 = 0;
int cmp;

SDL_Surface* Charger(const char* fic)
{
  SDL_Surface *res;
  SDL_Surface* tmp = IMG_Load(fic);
  if (tmp==NULL)
    {
      printf("Erreur chargement %s\n",fic);
      exit(-1);
    }
  res = SDL_DisplayFormat(tmp);
  SDL_FreeSurface(tmp);
  return res;
  SDL_FreeSurface(res);
}
void upVie(){
  score.vie=score.vie+1;
}
void mise_a_jour_vie(){
  if (cmp>500)
    {
      upVie();
      cmp=0;
    }
}
void upScore(int i){
  switch(i) {
  case 0 : score.score = score.score + 20;  cmp = cmp+20;  break;
  case 1: score.score = score.score + 30;  cmp = cmp+30; break;
  case 2: score.score = score.score + 60;  cmp = cmp+60; break;
  case 3:  score.score = score.score + 10;  cmp = cmp+10; break;
  case 4: score.score = score.score + 300;  cmp = cmp+300;  break;
  case 5:  score.score = score.score + 200; cmp = cmp+200;  break;
  case 6:  score.score = score.score + 40;  cmp = cmp+40; break;
  default:  score.score = score.score;  break;
  }
  mise_a_jour_vie();
  bool2=1;
}
int getniveau(){
  return score.niveau;
}
int getVie(){
  return score.vie;
}
void downVie(){
  score.vie=score.vie-1;
  bool1=1;
}
void upNiveau(){
  score.niveau=score.niveau+1;
}
void charger_mur(){
  mur[0] = Charger("textures/mur.bmp");
  mur[1] = Charger("textures/mur1.bmp");
  mur[2] = Charger("textures/mur2.bmp");
  mur[3] = Charger("textures/porte.bmp");
}
void charger_fruit(){
  fruit[0] = Charger("textures/cerise.png");
  fruit[1] = Charger("textures/carote.png");
  fruit[2] = Charger("textures/banane.png");
  fruit[3] = Charger("textures/framboise.png");
  fruit[4] = Charger("textures/sandwitch.png");
  fruit[5] = Charger("textures/tomate.png");
  fruit[6] = Charger("textures/fraise.png");
}
void charger_sol_et_ciel(){
  sol[0] = Charger("textures/herbe.png");
  sol[1]= Charger("textures/sol.bmp");
  ciel = Charger("textures/plafond.jpeg");
}
void charger_fantome(){
  fantome = Charger("textures/fantome.png");
}
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
  if(TTF_Init() == -1)
    {
      fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
      exit(EXIT_FAILURE);
    }
  police = TTF_OpenFont("font/verdana.ttf", 30);
  police2 = TTF_OpenFont("font/verdana.ttf",100);
  SDL_WM_SetCaption("RayCasting", NULL);
  charger_mur();
  charger_sol_et_ciel();
  charger_fantome();
  charger_fruit();
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
  pixels[ ( y * surface->w ) + x ] = pixel;
}
void zoom(SDL_Surface* src,SDL_Surface* dest,int decalage,int nombre,int x)
{SDL_LockSurface(src);
  SDL_LockSurface(dest);
  int i,j;
  double rx,ry;
  Uint8 r, v, b,a;
  Uint32 pixel;
  rx = dest->w*1.0/src->w;
  ry = dest->h*1.0/src->h;
  rx =rx*nombre;
  for(i=0;i<dest->w;i++)
    for(j=0;j<dest->h;j++)
      {
	if (x==0)
	  {pixel= get_pixel32(src,(int)i/rx + decalage%12 * (int)src->w/12 ,(int)((j/ry)));
	    put_pixel32(dest,i,j,pixel & 0x00FF0000);
	  }
	else if(x==1)
	  {pixel= get_pixel32(src,(int)i/rx + decalage%12 * (int)src->w/12 ,(int)((j/ry)));
	    put_pixel32(dest,i,j,pixel & 0x0000FF00);
	  }
	else if(x==2)
	  {pixel= get_pixel32(src,(int)i/rx + decalage%12 * (int)src->w/12 ,(int)((j/ry)));
	    put_pixel32(dest,i,j,pixel& 0x000000FF);
	  }
	else  if(x==3)
	  {pixel= get_pixel32(src,(int)i/rx ,(int)((j/ry)));
	    put_pixel32(dest,i,j,pixel);
	  }
      }
  SDL_UnlockSurface(src);
  SDL_UnlockSurface(dest);
}

void sdl_ligne_verticale_texture(int x, int y,int texX,int texY,int type_cote , int i){
  SDL_LockSurface(mur[i]);
  SDL_LockSurface(ecran);
  Uint8 r, v, b,a;
  Uint32 pixel;
  pixel= get_pixel32(mur[i],texX,texY);
  if (!type_cote)
    {
      SDL_GetRGB(pixel, mur[i]->format, &r, &v, &b);
      pixel=SDL_MapRGBA(ecran->format, r >>1, v>>1, b>>1, a);
    }
  put_pixel32(ecran,x,y,pixel & 0x00FFFFFF);
  SDL_UnlockSurface(mur[i]);
  SDL_UnlockSurface(ecran);
}
void sdl_ligne_verticale_texture_sprite(int x, int y,int texX,int texY, int i){
  SDL_LockSurface(fruit[i]);
  SDL_LockSurface(ecran);
  Uint8 r, v, b,a;
  Uint32 pixel;
  pixel= get_pixel32(fruit[i],texX,texY);
  if((pixel & 0x00FFFFFF) != 0)
    put_pixel32(ecran,x,y,pixel);
  SDL_UnlockSurface(fruit[i]);
  SDL_UnlockSurface(ecran);
}
void sdl_ligne_verticale_texture_sol(int x, int y ,int floorTexX,int floorTexY ){
  SDL_LockSurface(sol[0]);
  SDL_LockSurface(ciel);
  SDL_LockSurface(ecran);
  Uint8 r, v, b,a;
  Uint32 pixel;
  pixel= get_pixel32(sol[0],floorTexX,floorTexY);
  put_pixel32(ecran,x,y,pixel & 0x000FF000);
  pixel= get_pixel32(ciel,floorTexX,floorTexY);
  put_pixel32(ecran,x,480-y,pixel & 0x0000FFFF);
  SDL_UnlockSurface(sol[0]);
  SDL_UnlockSurface(ciel);
  SDL_UnlockSurface(ecran);
}
void sdl_ligne_fantome_texture(int x, int y ,int floorTexX,int floorTexY ,int i){
  position[i].x =x;
  position[i].y =y;
  position[i].h = floorTexX;
  position[i].w = floorTexY;
}
void sdl_fantome_mise_a_jour(int i){
  if (position[i].h<480) {
    copy=position[i];
    surface[i] = SDL_CreateRGBSurface(SDL_SWSURFACE, position[i].h, position[i].w, 32,0,0,0,0);
    zoom(fantome,surface[i],position[i].w,12,i);
    SDL_SetColorKey( surface[i], SDL_SRCCOLORKEY, SDL_MapRGB( surface[i]->format, 0, 0, 0 ) );
    SDL_SetAlpha(surface[i], SDL_SRCALPHA, 128);
    SDL_BlitSurface(surface[i],NULL,ecran,&copy);
  }
}
void sdl_fruit_mise_a_jour(int i){
  if (position[i].h<480) {
    copy=position[i];
    surface[i] = SDL_CreateRGBSurface(SDL_SWSURFACE, position[i].h, position[i].w, 32,0,0,0,0);
    zoom(fruit[i],surface[i],0,1,i);
    SDL_SetColorKey( surface[i], SDL_SRCCOLORKEY, SDL_MapRGB( surface[i]->format, 255, 255,255) );
    SDL_BlitSurface(surface[i],NULL,ecran,&copy);
  }
}
/* Fonction pour mettre a jour l'affichage */
void sdl_ecran_mise_a_jour(int nbframe) {
  SDL_Rect positionFond;
  positionFond.x = 0;
  positionFond.y = 0;
  positiontexte.x = 100;
  positiontexte.y = 420;
  positiontexte2.x = 100;
  positiontexte2.y = 150;
  sprintf(chaineTexte, "Niveau %d Sore %d Vie %d !",score.niveau,score.score,score.vie);
  texte = TTF_RenderText_Blended(police,chaineTexte, couleurTexte);
  if (bool2)
    {
      texte2 = TTF_RenderText_Blended(police2," MIAM ! ", couleurTexte3);
      SDL_BlitSurface(texte2, NULL, ecran, &positiontexte2);
      if( nbframe%10==1)bool2=0;
    }
  if (bool1)
    {if ( score.vie <= 0)
	{
	  texte2= TTF_RenderText_Blended(police2," PERDU ! ", couleurTexte3);
	  SDL_BlitSurface(texte2, NULL, ecran, &positiontexte2);
	} else{
	texte2 = TTF_RenderText_Blended(police2," OUTCH ! ", couleurTexte2);
	SDL_BlitSurface(texte2, NULL, ecran, &positiontexte2);
      }
      if( nbframe%10==1)bool1 =0;
    }
  SDL_BlitSurface(texte, NULL, ecran, &positiontexte);
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
void sdl_quitter() {int i;
  TTF_CloseFont(police);
  TTF_CloseFont(police2);
  TTF_Quit();
  for (i = 0; i < 4; ++i)
    {
      SDL_FreeSurface(mur[i]);
    }
  for (i = 0; i < 7; ++i)
    {
      SDL_FreeSurface(fruit[i]);
    }
  for (i = 0; i < 2; ++i)
    {
      SDL_FreeSurface(sol[i]);
    }
  for (i = 0; i < 10; ++i)
    {
      SDL_FreeSurface(surface[i]);
    }
  SDL_FreeSurface(ciel);
  SDL_FreeSurface(fantome);
  SDL_FreeSurface(texte);
  SDL_FreeSurface(texte2);
  SDL_Quit();
}
