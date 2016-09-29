/* 
 */

#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include "moteur.h"
#include "calcul.h"
#include "sdl.h"

#define VITESSE_DEPLACEMENT 5   
#define VITESSE_ROTATION 3  


extern int carte[LARGEUR_CARTE][HAUTEUR_CARTE]; 

Camera camera1= {10,12,-1,0,0,0.60};
Camera *pointeur = &camera1;
 
/*---------------  raycasting     ---------------*/

void moteur_dessiner(int x, int largeur, int hauteur) {
pointeur->posX = 13;
 printf("%.3d w1 \n",(int)camera1.posX);

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
