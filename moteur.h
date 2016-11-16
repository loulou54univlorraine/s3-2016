#define LARGEUR_CARTE 24
#define HAUTEUR_CARTE 24


typedef struct CoordonneesReel CoordonneesReel;

struct CoordonneesReel

{
    double x; // Abscisses
    double y; // Ordonnées
};

typedef struct Coordonnees Coordonnees;
struct Coordonnees

{
    int x; // Abscisses
    int y; // Ordonnées
};

void moteur_dessiner_colonne(int x, int largeur, int hauteur);
void moteur_gestion_actions(double temps_frame);
