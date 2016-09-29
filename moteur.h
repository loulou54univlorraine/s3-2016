#define LARGEUR_CARTE 24
#define HAUTEUR_CARTE 24

typedef struct Coordonnees Coordonnees;

struct Coordonnees{
double posX; // Abscisses
double posY; // Ordonnées
};


typedef struct Camera Camera;

struct Camera{
double posX; // Abscisses
double posY; // Ordonnées
double dirX; 
double diry; 
double planX;
double planY;
};

void moteur_dessiner(int x, int largeur, int hauteur);
void moteur_gestion_des_actions(double temps_frame);
