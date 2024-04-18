#include "enig_fichier.h"

int main(int argc, char *argv[])
{ 
    
    char reponse[20];
    char question[60];
    char bonnes_reponses[20];
    SDL_Surface *screen = NULL;
    SDL_Color Color;
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(1718, 878, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Enigme", NULL);
    TTF_Init();

    Enigme e;
    init_Enigme(&e);
    genererEnigme(&e, reponse, question, bonnes_reponses,Color);
    afficherEnigme(&e, screen);
    resolution(&e, screen);

    free_surface_Enigme(&e, screen);



    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

