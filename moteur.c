#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include "moteur.h"
#include "sdl.h"
#define VITESSE_DEPLACEMENT 1
#define VITESSE_ROTATION 3
#define texWidth 256
#define texHeight 256
extern int carte[LARGEUR_CARTE][HAUTEUR_CARTE];
CoordonneesReel Pos ={10,12} ,Dir={-1,0},Plan ={0,0.60};
CoordonneesReel RayPos={0,0},RayDir={0,0},BordDist ={0,0},DeltaDist ={0,0};
Coordonnees Carte={0,0},Pas={0,0};
/* Structure de couleur RGB */
struct couleur {
  int rouge;
  int vert;
  int bleu;
};
/* Constantes couleur */
const struct couleur noir    = {  0,  0,  0};
const struct couleur rouge   = {255,  0,  0};
const struct couleur vert    = {  0,255,  0};
const struct couleur bleu    = {  0,  0,255};
const struct couleur blanc   = {255,255,255};
const struct couleur jaune   = {255,255,  0};
const struct couleur cyan    = {  0,255,255};
const struct couleur magenta = {255,  0,255};
const struct couleur gris    = {128,128,128};
const struct couleur marron  = {128,  0,  0};
const struct couleur violet  = {128,  0,128};
struct couleur moteur_demi_couleur(struct couleur ancienne) {
  struct couleur nouvelle;
  nouvelle.rouge = ancienne.rouge / 2;
  nouvelle.vert  = ancienne.vert  / 2;
  nouvelle.bleu  = ancienne.bleu  / 2;
  return nouvelle;
}
/*---------------  raycasting     ---------------*/
void moteur_dessiner_colonne(int x, int largeur, int hauteur) {
  int
  touche = 0,
  type_cote,
  hauteur_ligne,
  pixel_haut,
  pixel_bas;
  double cameraX,
  perpWallDist;
  struct couleur color;
  RayPos.x = Pos.x;
  RayPos.y = Pos.y;
  cameraX = 2 * x / (double)(largeur) - 1;
  RayDir.x = Dir.x + Plan.x * cameraX;
  RayDir.y = Dir.y + Plan.y * cameraX;
  /* On calcule le carre de la carte dans lequel on est */
  Carte.x = (int)(RayPos.x);
  Carte.y = (int)(RayPos.y);
  /* On calcule la longueur du rayon d'un cote x ou y a l'autre cote x ou y */
  DeltaDist.x = sqrt(1 + (RayDir.y * RayDir.y) / (RayDir.x * RayDir.x));
  DeltaDist.y = sqrt(1 + (RayDir.x * RayDir.x) / (RayDir.y * RayDir.y));
  /* On calcule la direction vers laquelle on va et la longueur jusqu'au bord */
  if (RayDir.x < 0) {
    Pas.x = -1;
    BordDist.x = (RayPos.x - Carte.x) * DeltaDist.x;
  }
  else {
    Pas.x = 1;
    BordDist.x = (Carte.x + 1.0 - RayPos.x) * DeltaDist.x;
  }
  if (RayDir.y < 0) {
    Pas.y = -1;
    BordDist.y = (RayPos.y - Carte.y) * DeltaDist.y;
  }
  else {
    Pas.y = 1;
    BordDist.y = (Carte.y + 1.0 - RayPos.y) * DeltaDist.y;
  }
  /* Coeur du raycasting */
  while (touche == 0) {
    if (BordDist.x < BordDist.y) {
      BordDist.x += DeltaDist.x;
      Carte.x += Pas.x;
      type_cote = 0;
    }
    else {
      BordDist.y += DeltaDist.y;
      Carte.y += Pas.y;
      type_cote = 1;
    }
    /* On regarde si on a frappe dans un mur */
    if (carte[Carte.x][Carte.y] > 0)
      touche = 1;
  }
  if (type_cote == 0)
    perpWallDist = fabs((Carte.x - RayPos.x + (1 - Pas.x) / 2) / RayDir.x);
  else
    perpWallDist = fabs((Carte.y - RayPos.y + (1 - Pas.y) / 2) / RayDir.y);
  /*  hauteur de la colonne de mur a dessiner a l'ecran */
  hauteur_ligne = abs((int)(hauteur / perpWallDist));
  /* On calcule le y du pixel du haut et du bas de la ligne de mur */
  pixel_haut = -hauteur_ligne / 2 + hauteur / 2;
  if(pixel_haut < 0)
    pixel_haut = 0;
  pixel_bas = hauteur_ligne / 2 + hauteur / 2;
  if(pixel_bas >= hauteur)
    pixel_bas = hauteur - 1;
     //calculate value of wallX
  double wallX;
  if (type_cote == 0) {wallX = RayPos.y + perpWallDist * RayDir.y;
  }
  else    {    wallX = RayPos.x + perpWallDist * RayDir.x;
  }
  wallX -= floor((wallX));
  int texX = (int)(wallX * (double)(texWidth));
  if(type_cote == 0 && RayDir.x > 0) texX = texWidth - texX - 1;
  if(type_cote == 1 && RayDir.y < 0) texX = texWidth - texX - 1;
  switch(carte[Carte.x][Carte.y]) {
    case 1:  color = rouge;   break;
    case 2:  color = vert;    break;
    case 3:  color = bleu;    break;
    case 4:  color = blanc;   break;
    case 5:  color = jaune;   break;
    case 6:  color = cyan;    break;
    case 7:  color = magenta; break;
    case 8:  color = gris;    break;
    case 9:  color = marron;  break;
    default: color = violet;  break;
  }
  if (type_cote == 1) {
    color = moteur_demi_couleur(color);
  }
  /*  on dessine la colonne de mur a l'ecran */
  sdl_ligne_verticale(x,pixel_haut,pixel_bas,color.rouge,color.vert,color.bleu);
  sdl_ligne_verticale_texture(x,texX,type_cote,pixel_haut,pixel_bas,hauteur_ligne);
  sdl_ligne_verticale(x,0,pixel_haut,25,25,100);
  sdl_ligne_verticale(x,pixel_bas,hauteur-1,25,100,26);
}
void moteur_gestion_actions(double temps_frame) {
  double old_dirX, old_planX;
  double vitesse_dep;            /* Vitesse de deplacement en ligne */
  double vitesse_rot;            /* Vitesse de deplacement en rotation */
  /* Ajustement de la vitesse de deplacement et de rotation */
  vitesse_dep = temps_frame * VITESSE_DEPLACEMENT;
  vitesse_rot = temps_frame * VITESSE_ROTATION;
  sdl_touches_lire();
  /* Touche up : on se deplace vers l'avant si aucun mur devant soi */
  if (sdl_touches_appuyee(SDLK_UP )) {
    if(carte[(int)(Pos.x + Dir.x * vitesse_dep)+1][(int)(Pos.y)] == 0)
      Pos.x += Dir.x * vitesse_dep;
    if(carte[(int)(Pos.x)][(int)(Pos.y + Dir.y * vitesse_dep)] == 0)
      Pos.y += Dir.y * vitesse_dep;
  }
  /* Touche down : on se deplace vers l'arriere si aucun mur devant soi */
  if (sdl_touches_appuyee(SDLK_DOWN)) {
    if(carte[(int)(Pos.x - Dir.x * vitesse_dep)][(int)(Pos.y)] == 0)
      Pos.x -= Dir.x * vitesse_dep;
    if(carte[(int)(Pos.x)][(int)(Pos.y - Dir.y * vitesse_dep)] == 0)
      Pos.y -= Dir.y * vitesse_dep;
  }
  /* Touche down : on se deplace vers l'arriere si aucun mur devant soi */
  if (sdl_touches_appuyee(SDLK_s)) {
    if(carte[(int)(Pos.x - Dir.x * vitesse_dep)][(int)(Pos.y)] == 0)
      Pos.x -= Dir.x * vitesse_dep;
    if(carte[(int)(Pos.x)][(int)(Pos.y - Dir.y * vitesse_dep)] == 0)
      Pos.y -= Dir.y * vitesse_dep;
  }
  /* Touche droite : on se deplace vers la droite si aucun mur devant soi */
  if (sdl_touches_appuyee(SDLK_RIGHT)) {
    /* La direction ET le plan de la camera doivent effectuer la rotation */
    old_dirX = Dir.x;
    Dir.x = Dir.x * cos(-vitesse_rot) - Dir.y * sin(-vitesse_rot);
    Dir.y = old_dirX * sin(-vitesse_rot) + Dir.y * cos(-vitesse_rot);
    old_planX = Plan.x;
    Plan.x = Plan.x * cos(-vitesse_rot) - Plan.y * sin(-vitesse_rot);
    Plan.y = old_planX * sin(-vitesse_rot) + Plan.y * cos(-vitesse_rot);
  }
  /* Touche gauche : on se deplace vers la gauche si aucun mur devant soi */
  if (sdl_touches_appuyee(SDLK_LEFT)) {
    /* La direction ET le plan de la camera doivent effectuer la rotation */
    old_dirX = Dir.x;
    Dir.x = Dir.x * cos(vitesse_rot) - Dir.y * sin(vitesse_rot);
    Dir.y = old_dirX * sin(vitesse_rot) + Dir.y * cos(vitesse_rot);
    old_planX = Plan.x;
    Plan.x = Plan.x * cos(vitesse_rot) - Plan.y * sin(vitesse_rot);
    Plan.y = old_planX * sin(vitesse_rot) + Plan.y * cos(vitesse_rot);
  }
  /* Touche 'Esc' ou 'q', on arrete l'application */
  if (sdl_touches_appuyee(SDLK_ESCAPE) || sdl_touches_appuyee(SDLK_q)) {
    sdl_quitter();
    exit(0);
  }
}
