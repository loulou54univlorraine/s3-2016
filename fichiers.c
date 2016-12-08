
#include <stdlib.h>
#include <stdio.h>
#include "constantes.h"
#include "fichiers.h"

int chargerNiveau(int niveau , int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR])
{   char chaine[100];
  sprintf(chaine, "niveau/niveaux.lvl%d",niveau);
  FILE* fichier = NULL;
  char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0};
  int i = 0, j = 0;

  fichier = fopen(chaine, "r");
  if (fichier == NULL)
    return 0;

  fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);

  for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
      for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
	  switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
            {
	    case '0':
	      carte[j][i] = 0;
	      break;
	    case '1':
	      carte[j][i] = 1;
	      break;
	    case '2':
	      carte[j][i] = 2;
	      break;
	    case '3':
	      carte[j][i] = 3;
	      break;
	    case '4':
	      carte[j][i] = 4;
	      break;
	    default:
	      carte[j][i] = 0;
	      break;
            }
        }
    }

  fclose(fichier);
  return 1;
}

int sauvegarderNiveau(int carte[][NB_BLOCS_HAUTEUR])
{
  FILE* fichier = NULL;
  int i = 0, j = 0;

  fichier = fopen("niveau/niveaux.lvl", "w");
  if (fichier == NULL)
    return 0;
 
  for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
      for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
	  fprintf(fichier, "%d", carte[j][i]);
        }
    }

  fclose(fichier);
  return 1;
}
