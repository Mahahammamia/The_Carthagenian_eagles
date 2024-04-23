#ifndef PERSO_H_INCLUDED
#define PERSO_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include <stdbool.h>
typedef struct
{
  	SDL_Surface *img_perso;
  	SDL_Rect pos_perso;
	SDL_Rect pos_perso2;
	Uint8 *keystate; 
}perso;

void init_perso(perso *p);
void init_perso2(perso *p);
void afficher_perso(SDL_Surface *screen,perso p);
void afficher_perso2(SDL_Surface *screen,perso p);
void deplacer_perso(perso *p);
void deplacer_perso2(perso *p);
void free_perso(perso p);


#endif
