#include <stdio.h>
#include <stdlib.h>
#include "moteur.h"
#include "sdl.h"
#define LARGEUR_ECRAN 600
#define HAUTEUR_ECRAN 480
#define NB_FRAMES_ENTRE_AFFICHAGES_FPS 2000

int main() {
  int x;
  double date_actuelle = 0,
  date_precedente = 0,
  temps_frame,
  temps_total,
  nb_frames;
  int numSprites = 20;

double ZBuffer[LARGEUR_ECRAN];

int spriteOrder[numSprites];
double spriteDistance[numSprites];
chargement();
  sdl_ecran_init(LARGEUR_ECRAN,HAUTEUR_ECRAN);
  while(!sdl_fin()) {
    for (x = 0; x < LARGEUR_ECRAN; x++){
    ZBuffer[x] = moteur_dessiner_colonne(x,LARGEUR_ECRAN,HAUTEUR_ECRAN);
  }
   for (x = 0; x < 19; x++){
   moteur_dessiner_Sprite(x);
   }
    date_precedente = date_actuelle;
    date_actuelle = sdl_date();
    temps_frame = (date_actuelle - date_precedente) / 1000.0;
    temps_total += temps_frame;
    nb_frames++;
    sdl_ecran_mise_a_jour(nb_frames/6);

    moteur_gestion_actions(temps_total/nb_frames);
  }
  return 0;
 
}
