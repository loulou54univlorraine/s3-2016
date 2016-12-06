#include <stdio.h>
#include <stdlib.h>
#include "moteur.h"
#include "constantes.h"
#include "sdl.h"

int numfantome = 3;

int main() {
  int x;
  double date_actuelle = 0,
  date_precedente = 0,
  temps_frame,
  temps_total,
  nb_frames;
 double distanceFantome[numfantome];
 int ordrefantome[numfantome];
  sdl_ecran_init(LARGEUR_ECRAN,HAUTEUR_ECRAN);
  chargement();
  while(!sdl_fin()) {
    for (x = 0; x < LARGEUR_ECRAN; x++){
   moteur_dessiner_colonne(x,LARGEUR_ECRAN,HAUTEUR_ECRAN);
  }
   for (int i = 0; i < numfantome; ++i)
   {
      distanceFantome[i] = moteur_dessiner_Fantome(i);
      ordrefantome[i]=i;
    
   }
    moteur_dessiner_Fruit();
    date_precedente = date_actuelle;
    date_actuelle = sdl_date();
    temps_frame = (date_actuelle - date_precedente) / 1000.0;
    temps_total += temps_frame;
    nb_frames++;


  
for(int i=0; i<numfantome; i++){
   for(int j=i+1; j<numfantome; j++) {
      if(distanceFantome[i]<distanceFantome[j]) {
         int tmp = distanceFantome[i];
         int tmp2 =  ordrefantome[i];
         distanceFantome[i] = distanceFantome[j];
        ordrefantome[i]= ordrefantome[j];
         distanceFantome[j] = tmp;  
          ordrefantome[j]  =tmp2 ;
      }
   }
   } 
    for (int i = 0; i < numfantome; ++i){


    sdl_fantome_mise_a_jour(ordrefantome[i] );
       }

       sdl_ecran_mise_a_jour(nb_frames);

    moteur_gestion_actions(temps_total/nb_frames);
  }
  return 0;
 
}
