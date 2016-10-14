#define LARGEUR_CARTE 24
#define HAUTEUR_CARTE 24

typedef struct PosJoueur PosJoueur;

struct PosJoueur{
double posX; // Abscisses
double posY; // Ordonnées
};

typedef struct DirectionJoueur DirectionJoueur;

struct DirectionJoueur{
double dirX; 
double diry; 
};


typedef struct PlanCamera PlanCamera;

struct PlanCamera{
double planX;
double planY;
};

typedef struct PosCarteJoueur PosCarteJoueur;

struct PosCarteJoueur{
int carteX;          /* Position du carre dans lequel on est en x */
int carteY; 
};


typedef struct Camera Camera;

struct Camera{
double posX; // Abscisses
double posY; // Ordonnées
double dirX; 
double diry; 
double planX;
double planY;
int carteX;          /* Position du carre dans lequel on est en x */
int carteY; 
int pasX;             /* direction vers laquelle on va en x (-1 ou 1) */
int pasY;
int touche;
};

/* Structure de couleur RGB */
typedef struct Couleur Couleur;
struct Couleur {
  int rouge;
  int vert;
  int bleu;
};



struct Ray{
  int     
      type_cote, 
      hauteur_ligne,  
      pixel_haut,      
      pixel_bas;        
  double cameraX,      
         rayPosX,     
	 rayPosY,      
	 rayDirX,    
	 rayDirY,      
         bordDistX,    
         bordDistY,    
         deltaDistX,    
	 deltaDistY,   
         perpWallDist; 
     
};


void moteur_dessiner(int x, int largeur, int hauteur);
void moteur_gestion_des_actions(double temps_frame);
