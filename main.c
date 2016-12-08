/*Sébastien André et Louis Dudot
  Basé sur les codes de Lode Vandevenne
  http://lodev.org/cgtutor/*/
#include <stdio.h>
#include <stdlib.h>
#include "moteur.h"
#include "constantes.h"
#include "sdl.h"
int numfantome = 3;
int main() {
  menu();
  int x;
  int i ,j, tmp ,tmp2;
  double date_actuelle = 0,
    date_precedente = 0,
    temps_frame,
    temps_total,
    nb_frames;
  double distanceFantome[numfantome];
  int ordrefantome[numfantome];
  sdl_ecran_init(LARGEUR_ECRAN,HAUTEUR_ECRAN);
  // on charge la map
  chargement(1);
  while(!sdl_fin()) {
    date_precedente = date_actuelle;
    date_actuelle = sdl_date();
    temps_frame = (date_actuelle - date_precedente) / 1000.0;
    temps_total += temps_frame;
    nb_frames++;
    // Si il reste des vies
    if(getVie()>=1){
      for (x = 0; x < LARGEUR_ECRAN; x++){
	// on lance le Raycasting
	moteur_dessiner_colonne(x,LARGEUR_ECRAN,HAUTEUR_ECRAN);
      }
      moteur_dessiner_Fruit();
      for (i = 0; i < numfantome; ++i)
	{
	  distanceFantome[i]= moteur_dessiner_Fantome(i);
	  ordrefantome[i]=i;
	}
      // trie des fantomes en fonction de leur position 
      for(i=0; i<numfantome; i++){
	for(j=i+1; j<numfantome; j++) {
	  if(distanceFantome[i]<distanceFantome[j]) {
	    tmp = distanceFantome[i];
	    tmp2 =  ordrefantome[i];
	    distanceFantome[i] = distanceFantome[j];
	    ordrefantome[i]= ordrefantome[j];
	    distanceFantome[j] = tmp;
	    ordrefantome[j]  =tmp2 ;
	  }
	}
      }
      for (i = 0; i < numfantome; ++i){
	// dessin des fantomes dans l'ordre de distances  
	sdl_fantome_mise_a_jour(ordrefantome[i] );
      }
      sdl_ecran_mise_a_jour(nb_frames);
    }
    moteur_gestion_actions(temps_total/nb_frames);
  }
  return 0;
}
