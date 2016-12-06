#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include "moteur.h"
#include "constantes.h"
#include "fichiers.h"
#include "sdl.h"


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

Sprite fantomeSprite[3] ={{11.5, 11.5,0},
{11.5, 11.5,0},{11,11,0}};

int numSprites = 3;
Sprite sprite[3] ={{10.5,10.5,0},
{11.5, 9.5,0},{12,11,0}};

CoordonneesReel Pos ={22,11.5} ,Dir={-1,0},Plan ={0,0.60};
CoordonneesReel RayPos={0,0},RayDir={0,0},BordDist ={0,0},DeltaDist ={0,0};
Coordonnees Carte={0,0},Pas={0,0};
/* Structure de couleur RGB */


struct couleur moteur_demi_couleur(struct couleur ancienne) {
  struct couleur nouvelle;
  nouvelle.rouge = ancienne.rouge / 2;
  nouvelle.vert  = ancienne.vert  / 2;
  nouvelle.bleu  = ancienne.bleu  / 2;
  return nouvelle;
}

void sauvegarder(){
int a = sauvegarderNiveau(carte);}

void chargement(){
if (!chargerNiveau(1,carte))
        exit(EXIT_FAILURE);}


/*---------------  raycasting     ---------------*/
double moteur_dessiner_colonne(int x, int largeur, int hauteur) {
int
touche = 0,//le rayon touche un mur ou pas
type_cote,//quelle orientation à le mur (nord/sud ou est/ouest) dans la map
hauteur_ligne,
pixel_haut,
pixel_bas;
double cameraX,
perpWallDist;// distance corrigée du rayon
struct couleur color;
RayPos.x = Pos.x;// position de départ du rayon sur X
RayPos.y = Pos.y;// position de départ du rayon sur Y
//calculate ray position and direction
cameraX = 2 * x / (double)(largeur) - 1;// position de la colonne par rapport au centre de l’écran
RayDir.x = Dir.x + Plan.x * cameraX; // direction du rayon sur X
RayDir.y = Dir.y + Plan.y * cameraX;// direction du rayonsur Y
/* On calcule le carre de la carte dans lequel on est */
Carte.x = (int)(RayPos.x);// sur quelle case est la caméra
Carte.y = (int)(RayPos.y);// sur quelle case est la caméra
// longueur du rayon
DeltaDist.x = sqrt(1 + (RayDir.y * RayDir.y) / (RayDir.x * RayDir.x));
DeltaDist.y = sqrt(1 + (RayDir.x * RayDir.x) / (RayDir.y * RayDir.y));
/* On calcule la direction vers laquelle on va et la longueur jusqu'au bord */
if (RayDir.x < 0) {
Pas.x = -1;// vecteur de direction
BordDist.x = (RayPos.x - Carte.x) * DeltaDist.x;// distance
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
// tant que le rayon ne rencontre pas de mur
while (touche == 0) {
//Passe à la case suivante sur X ou Y
  if (BordDist.x < BordDist.y) {
BordDist.x += DeltaDist.x;// agrandis le rayon
Carte.x += Pas.x;// prochaine case ou case précédente sur X
type_cote = 0;// orientation du mur
}
else {
  BordDist.y += DeltaDist.y;
  Carte.y += Pas.y;
  type_cote = 1;
}
/* On regarde si on a frappe dans un mur */
if (carte[Carte.x][Carte.y] > 0)
touche = 1;// stoppe la boucle
}
if (type_cote == 0)
// Calcule la distance corrigée pour la projection
  perpWallDist = fabs((Carte.x - RayPos.x + (1 - Pas.x) / 2) / RayDir.x);
else
  perpWallDist = fabs((Carte.y - RayPos.y + (1 - Pas.y) / 2) / RayDir.y);
//Calcule la hauteur de la ligne à tracer
hauteur_ligne = abs((int)(hauteur / perpWallDist));
//Calcule les pixels max haut et max bas de la colonne à tracer
pixel_haut = -hauteur_ligne / 2 + hauteur / 2;
if(pixel_haut < 0)
  pixel_haut = 0;
pixel_bas = hauteur_ligne / 2 + hauteur / 2;
if(pixel_bas >= hauteur)
  pixel_bas = hauteur - 1;
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
sdl_ligne_verticale(x,0,pixel_haut,25,25,100);
sdl_ligne_verticale(x,pixel_bas,hauteur-1,25,100,26);
//pour les textures
double wallX;
if (type_cote == 0) {wallX = RayPos.y + perpWallDist * RayDir.y;
}
else    {    wallX = RayPos.x + perpWallDist * RayDir.x;
}
wallX -= floor((wallX));
int texX = (int)(wallX * (double)(texWidth));
if(type_cote == 0 && RayDir.x > 0) texX = texWidth - texX - 1;
if(type_cote == 1 && RayDir.y < 0) texX = texWidth - texX - 1;
int start;
for(start = pixel_haut; start < pixel_bas; start++)
      {
        int d = start * 256 - hauteur * 128 + hauteur_ligne * 128;  //256 and 128 factors to avoid floats
        int texY = ((d * texHeight) / hauteur_ligne) / 256;
        sdl_ligne_verticale_texture(x,start,texX,texY,type_cote,carte[Carte.x][Carte.y]-1);
  
      }

ZBuffer[x] = perpWallDist;
//pour les plafonds et les sols
//FLOOR CASTING
double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall
//4 different wall directions possible
if(type_cote == 0 && RayDir.x > 0)
{
  floorXWall = Carte.x ;
  floorYWall = Carte.y  + wallX;
}
else if(type_cote == 0 && RayDir.x < 0)
{
  floorXWall = Carte.x  + 1.0;
  floorYWall = Carte.y  + wallX;
}
else if(type_cote == 1 && RayDir.y > 0)
{
  floorXWall = Carte.x  + wallX;
  floorYWall = Carte.y ;
}
else
{
  floorXWall = Carte.x  + wallX;
  floorYWall = Carte.y  + 1.0;
}
double distWall, distPlayer,currentDist;
distWall = perpWallDist;
distPlayer = 0.0;
if (pixel_bas < 0) pixel_bas = hauteur; //becomes < 0 when the integer overflows
for(start = pixel_bas + 1; start < hauteur; start++)
{
currentDist = hauteur / (2.0 * start - hauteur); //you could make a small lookup table for this instead
double weight = (currentDist - distPlayer) / (distWall - distPlayer);
double currentFloorX = weight * floorXWall + (1.0 - weight) * Pos.x;
double currentFloorY = weight * floorYWall + (1.0 - weight) * Pos.y;
int floorTexX, floorTexY;
floorTexX = (int)(currentFloorX * texWidth) % texWidth;
floorTexY = (int)(currentFloorY * texHeight) % texHeight;
sdl_ligne_verticale_texture_sol(x, start ,floorTexX,floorTexY );
}

}
double moteur_dessiner_Fantome(int i){
  int largeur = 600;
  int hauteur = 480;
// double X=((double)rand()/(0,01*(double)RAND_MAX));
 //printf("%f\n", X);
  double fantomeDistance = ((Pos.x - fantomeSprite[i].x) * (Pos.x - fantomeSprite[i].x) + (Pos.y - fantomeSprite[i].y) * (Pos.y - fantomeSprite[i].y));
//translate sprite[i][i] position to relative to camera
  double spriteX = fantomeSprite[i].x - Pos.x;
  double spriteY = fantomeSprite[i].y - Pos.y;
  
if (i==0)
{ 
fantomeSprite[0].x=  fantomeSprite[0].x - 0.01*spriteX;
fantomeSprite[0].y=  fantomeSprite[0].y - 0.02*spriteY;
}
if (i==1)
{
fantomeSprite[1].x=  fantomeSprite[1].x - 0,02*spriteX;
fantomeSprite[1].y=  fantomeSprite[1].y - 0.02*spriteY;
}
if (i==2)
{
fantomeSprite[2].x=  fantomeSprite[2].x - 0.03*spriteX;
fantomeSprite[2].y=  fantomeSprite[2].y - 0.02*spriteY;
}


double invDet = 1.0 / (Plan.x * Dir.y - Dir.x * Plan.y); //required for correct matrix multiplication
double transformX = invDet * (Dir.y * spriteX - Dir.x * spriteY);
double transformY = invDet * (-Plan.y * spriteX + Plan.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
int spriteScreenX = (int)((largeur / 2) * (1 + transformX / transformY));
//calculate height of the sprite[i][i] on screen
int spriteHeight = abs((int)(hauteur / (transformY))); //using "transformY" instead of the real distance prevents fisheye
//calculate lowest and highest pixel to fill in current stripe
int drawStartY = -spriteHeight / 2 + hauteur / 2;
//if(drawStartY < 0) drawStartY = 0;
int drawEndY = spriteHeight / 2 + hauteur / 2;
if(drawEndY >= hauteur) drawEndY = hauteur - 1;
//calculate width of the sprite[i][i]
int spriteWidth = abs( (int) (hauteur / (transformY)));
int drawStartX = -spriteWidth / 2 + spriteScreenX;
//if(drawStartX < 0) drawStartX = 0;
int drawEndX = spriteWidth / 2 + spriteScreenX;
if(transformY > 0 )
sdl_ligne_fantome_texture(drawStartX, drawStartY,spriteWidth,spriteHeight,i);
return fantomeDistance;
}

 void moteur_dessiner_Fruit(){
  int largeur = 600;
  int hauteur = 480;

 double distanceSprite[numSprites];
 int ordreSprites[numSprites];

 for(int i = 0; i < numSprites; i++)
    {
      ordreSprites[i] = i;
      distanceSprite[i] = ((Pos.x - sprite[i].x) * (Pos.x - sprite[i].x) + (Pos.y - sprite[i].y) * (Pos.y - sprite[i].y));
    }

for(int i=0; i<numSprites; i++){
   for(int j=i+1; j<numSprites; j++) {
      if(distanceSprite[i]<distanceSprite[j]) {
         int tmp = distanceSprite[i];
         int tmp2 =  ordreSprites[i];
         distanceSprite[i] = distanceSprite[j];
        ordreSprites[i]= ordreSprites[j];
         distanceSprite[j] = tmp;  
          ordreSprites[j]  =tmp2 ;
      }
   }
   } 

     for(int i = 0; i < numSprites; i++)
    {
      //translate sprite position to relative to camera
      double spriteX = sprite[ordreSprites[i]].x - Pos.x;
      double spriteY = sprite[ordreSprites[i]].y - Pos.y;


      double invDet = 1.0 / (Plan.x * Dir.y - Dir.x * Plan.y); //required for correct matrix multiplication

      double transformX = invDet * (Dir.y * spriteX - Dir.x * spriteY);
      double transformY = invDet * (-Plan.y * spriteX + Plan.x * spriteY); 
     //this is actually the depth inside the screen, that what Z is in 3D

     int spriteScreenX = (int)((largeur / 2) * (1 + transformX / transformY));
//calculate height of the sprite[i][i] on screen
int spriteHeight = abs((int)(hauteur / (transformY))); //using "transformY" instead of the real distance prevents fisheye
//calculate lowest and highest pixel to fill in current stripe
int drawStartY = -spriteHeight / 2 + hauteur / 2;
if(drawStartY < 0) drawStartY = 0;
int drawEndY = spriteHeight / 2 + hauteur / 2;
if(drawEndY >= hauteur) drawEndY = hauteur - 1;
//calculate width of the sprite[i][i]
int spriteWidth = abs( (int) (hauteur / (transformY)));
int drawStartX = -spriteWidth / 2 + spriteScreenX;
if(drawStartX < 0) drawStartX = 0;
int drawEndX = spriteWidth / 2 + spriteScreenX;
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
 
        if(transformY > 0 && stripe > 0 && stripe < largeur  &&transformY < ZBuffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y) * 256 - hauteur * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * texHeight) / spriteHeight) / 256;
          sdl_ligne_verticale_texture_sprite(stripe,y,texX,texY,ordreSprites[i]);
          
        }
      }
}
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
    if(carte[(int)(Pos.x + Dir.x * vitesse_dep)][(int)(Pos.y)] == 0 ||carte[(int)(Pos.x + Dir.x * vitesse_dep)][(int)(Pos.y)] == 4)
      Pos.x += Dir.x * vitesse_dep;
    //else Pos.x = (int)Pos.x + 0.5;
    if(carte[(int)(Pos.x)][(int)(Pos.y + Dir.y * vitesse_dep)] == 0 ||carte[(int)(Pos.x)][(int)(Pos.y + Dir.y * vitesse_dep)] == 4)
      Pos.y += Dir.y * vitesse_dep;
    //else Pos.y= (int)Pos.y + 0.5;
  }
/* Touche down : on se deplace vers l'arriere si aucun mur devant soi */
  if (sdl_touches_appuyee(SDLK_DOWN)) {
    if(carte[(int)(Pos.x - Dir.x * vitesse_dep)][(int)(Pos.y)] == 0)
      Pos.x -= Dir.x * vitesse_dep;
    //else Pos.x= (int)Pos.x + 0.5;
    if(carte[(int)(Pos.x)][(int)(Pos.y - Dir.y * vitesse_dep)] == 0)
      Pos.y -= Dir.y * vitesse_dep;
    //else Pos.y= (int)Pos.y + 0.5;
  }
/* Touche down : on se deplace vers l'arriere si aucun mur devant soi */
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