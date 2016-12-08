#define SCREEN_WIDTH_M  600
#define SCREEN_HEIGHT_M 480



void menu(){

        SDL_Surface *ecran = NULL; ///Initialise un �cran sur lequel toutes les surfaces seront positionn�es

        SDL_Surface *menu = NULL; ///Initialise la surface qui servira de menu

        SDL_Event touche; ///Initialise un �vn�nement qui servira � r�cup�rer la saisie au clavier

        int compteur = 1; ///Bool�en pour la boucle

        /*Cr�e la position du menu sur l'�cran*/
        SDL_Rect MENU;
        MENU.x = 0;
        MENU.y = 0;

        SDL_Init(SDL_INIT_VIDEO); ///Initialise la SDL

        ecran = SDL_SetVideoMode(SCREEN_WIDTH_M, SCREEN_HEIGHT_M, 0, 0); ///Initialise la SDL

        menu = SDL_LoadBMP("menu.bmp"); ///Mets l'image du menu sur la surface menu

        SDL_BlitSurface(menu, NULL, ecran, &MENU); ///Colle le menu sur l'�cran

        SDL_Flip(ecran); ///Actualise l'�cran

        while(compteur)
        {
            SDL_WaitEvent(&touche); ///Attendre que l'on appuie sur une touche

            switch(touche.type)
            {
            case SDL_QUIT:
                compteur++;
                break;
            case SDL_KEYDOWN: ///Si une touche a �t� appuy�e
                switch(touche.key.keysym.sym)
                {
                case SDLK_SPACE: ///Si la touche appuy�e est espace
                    compteur=0;
                    SDL_FreeSurface(ecran);
                    break;
                case SDLK_ESCAPE:
                    compteur=0;
                    exit(EXIT_SUCCESS);
                }
                break;
            }
	}
}
