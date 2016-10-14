/* 
 */

#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include "moteur.h"
#include "sdl.h"

#define VITESSE_DEPLACEMENT 5   
#define VITESSE_ROTATION 3  




extern int carte[LARGEUR_CARTE][HAUTEUR_CARTE]; 
/* Structure de couleur RGB */
struct couleur {
  int rouge;
  int vert;
  int bleu;
};

 /* Constantes couleur */
const  Couleur noir    = {  0,  0,  0};
const  Couleur rouge   = {255,  0,  0};
const  Couleur vert    = {  0,255,  0};
const  Couleur bleu    = {  0,  0,255};
const  Couleur blanc   = {255,255,255};
const  Couleur jaune   = {255,255,  0};
const  Couleur cyan    = {  0,255,255};
const  Couleur magenta = {255,  0,255};
const  Couleur gris    = {128,128,128};
const  Couleur marron  = {128,  0,  0};
const  Couleur violet  = {128,  0,128};

Couleur moteur_demi_couleur(Couleur ancienne) {
  Couleur nouvelle;
  nouvelle.rouge = ancienne.rouge / 2;
  nouvelle.vert  = ancienne.vert  / 2;
  nouvelle.bleu  = ancienne.bleu  / 2;
  return nouvelle;
};

struct coordoneReel
{
  double posX;
  double posY;
};

coordoneReel->posX = 12;
coordoneReel->posY = 10;

struct directionsRayon
{
  double dirX;
  double dirY;
};

struct planCamera
{
  double planX;
  double planY;
};

struct camera
{
  double cameraX;
};


struct positionRayon
{
  double rayPosX;
  double rayPosy;
};

struct directionRayon
{
  double rayDirX;
  double rayDirY;
};

struct positionCarte
{
int carteX;
int carteY;
};

struct distanceBord
{

double bordDistX;
double bordDistY;
  
};

struct delta
{
  double deltaDistX ;
  double deltaDistY ;
};

double perpWallDist;  /* Distance projetee sur la direction de la camera */

/*---------------  raycasting     ---------------*/

void moteur_dessiner(int x, int largeur, int hauteur) {



 /* Couleur de la partie de mur a dessiner */

  /* On calcule la position et la direction du rayon */
 

}

void moteur_gestion_des_actions(double temps_frame) {



  sdl_touches_lire();
  
 
  if (sdl_touches_appuyee(SDLK_UP )) {

   
  }

 
  if (sdl_touches_appuyee(SDLK_DOWN)) {
  
  }
  
  
  if (sdl_touches_appuyee(SDLK_s)) {
   
  }
 
  if (sdl_touches_appuyee(SDLK_RIGHT)) {
   
  }
  
  
  if (sdl_touches_appuyee(SDLK_LEFT)) {
  
  }
  
 
  if (sdl_touches_appuyee(SDLK_ESCAPE) || sdl_touches_appuyee(SDLK_q)) {
    sdl_quitter();
    exit(0);
  }
}
