

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define LARGEUR_ECRAN 600
#define HAUTEUR_ECRAN 480
#define NB_FRAMES_ENTRE_AFFICHAGES_FPS 2000
#define VITESSE_DEPLACEMENT 3
#define VITESSE_ROTATION 3
#define texWidth 256
#define texHeight 256
#define NB_BLOCS_LARGEUR    24
#define NB_BLOCS_HAUTEUR    24

int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] ;

double ZBuffer[LARGEUR_ECRAN];

typedef struct CoordonneesReel CoordonneesReel;

struct CoordonneesReel

{
  double x; // Abscisses
  double y; // Ordonnées
  int texture;
};

typedef struct Coordonnees Coordonnees;
struct Coordonnees

{
  int x; // Abscisses
  int y; // Ordonnées
};

typedef struct Sprite
{
  double x;
  double y;
  int texture;
  int visible;
}Sprite;

struct couleur {
  int rouge;
  int vert;
  int bleu;
};

typedef struct score {
  int vie;
  int score;
  int niveau;
}Score;

#endif
