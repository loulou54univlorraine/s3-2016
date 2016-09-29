void sdl_ecran_init(int largeur, int hauteur);
void sdl_ligne_verticale(int x, int y1, int y2, int r, int v, int b);
void sdl_ligne_verticale_texture(int x, int texX,int type_cote,int y1, int y2);
void sdl_ecran_mise_a_jour();
void sdl_touches_lire();
void sdl_quitter();
int  sdl_touches_appuyee(int touche);
int  sdl_fin();
unsigned long sdl_date();

