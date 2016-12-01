#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include "moteur.h"
#include "constantes.h"
#include "fichiers.h"
#include "sdl.h"

Sprite sprite ={11.5, 11.5, 10};



void moteur_dessiner_Sprite(int i){
  int largeur = 600;
  int hauteur = 480;
  double spriteDistance = ((Pos.x - sprite[i].x) * (Pos.x - sprite[i].x) + (Pos.y - sprite[i].y) * (Pos.y - sprite[i].y));
//translate sprite[i] position to relative to camera
  double spriteX = sprite[i].x - Pos.x;
  double spriteY = sprite[i].y - Pos.y;
double invDet = 1.0 / (Plan.x * Dir.y - Dir.x * Plan.y); //required for correct matrix multiplication
double transformX = invDet * (Dir.y * spriteX - Dir.x * spriteY);
double transformY = invDet * (-Plan.y * spriteX + Plan.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
int spriteScreenX = (int)((largeur / 2) * (1 + transformX / transformY));
//calculate height of the sprite[i] on screen
int spriteHeight = abs((int)(hauteur / (transformY))); //using "transformY" instead of the real distance prevents fisheye
//calculate lowest and highest pixel to fill in current stripe
int drawStartY = -spriteHeight / 2 + hauteur / 2;
if(drawStartY < 0) drawStartY = 0;
int drawEndY = spriteHeight / 2 + hauteur / 2;
if(drawEndY >= hauteur) drawEndY = hauteur - 1;
//calculate width of the sprite[i]
int spriteWidth = abs( (int) (hauteur / (transformY)));
int drawStartX = -spriteWidth / 2 + spriteScreenX;
// if(drawStartX < 0) drawStartX = 0;
int drawEndX = spriteWidth / 2 + spriteScreenX;
if(drawEndX >= largeur) drawEndX = largeur- 1;
for(int start= drawStartX; start < drawEndX; start++)
{
  int texX = (int)(256 * (start - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
  if(transformY > 0 && start > 0 && start < 600 )
for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
{
int d = (y) * 256 - hauteur * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
int texY = ((d * texHeight) / spriteHeight) / 256;
//sdl_ligne_verticale_texture_sprite(start,y,texX,texY);
}
}
if(transformY > 0 && drawStartX > 0 && drawStartX < 600 )
sdl_ligne_sprite_texture(drawStartX, drawStartY,spriteWidth,spriteHeight);
}