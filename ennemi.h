#ifndef _ES_H_
#define _ES_H_
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

enum state_es{move,run,attack,dead};
typedef struct
{
enum state_es state;
SDL_Rect pos;
SDL_Rect sprite;
int vie;
SDL_Surface *image;
int sprite_n;
int d;
int speed;
}ennemi;

void init_ennemi(ennemi *p);
void afficher_ennemi(ennemi p,SDL_Surface *screen);
void animer_ennemi(ennemi *p);
void mouvement_aleatoire_ennemi(ennemi *p);

#endif
