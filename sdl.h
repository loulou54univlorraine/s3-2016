void sdl_ecran_init(int largeur, int hauteur);
void sdl_ligne_verticale(int x, int y1, int y2, int r, int v, int b);
void sdl_ligne_verticale_texture(int x, int y,int texX,int texY,int type_cote , int i);
void sdl_ligne_verticale_texture_sol(int x, int y ,int floorTexX,int floorTexY );
void sdl_ecran_mise_a_jour(int i);
void sdl_touches_lire();
void sdl_quitter();
int  sdl_touches_appuyee(int touche);
int  sdl_fin();
unsigned long sdl_date();
void sdl_ligne_sprite_texture(int x, int y ,int floorTexX,int floorTexY );
void  sdl_ligne_verticale_texture_sprite(int x, int y ,int texY,int texX );

