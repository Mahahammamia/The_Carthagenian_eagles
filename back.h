#ifndef BACKGROUND_H_INCLUDE
#define BACKGROUND_H_INCLUDE

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "perso.h"

#define SCREEN_W 1817
#define SCREEN_H 878

typedef struct
{
 TTF_Font *font;
 SDL_Color color;
 SDL_Surface* text;
 SDL_Rect postext;
}Text;

typedef struct
{

	SDL_Surface *img_back;

	SDL_Rect pos_back;
	SDL_Rect pos_back2;

	SDL_Rect camera; 
	SDL_Rect camera2;

	Mix_Music *music1;
        Mix_Music *music2;
	Mix_Chunk *bref1;//
	Mix_Chunk *bref2;//

	SDL_Surface *img_anim;  
	SDL_Rect pos_img_anim;
	SDL_Rect one_img;	
	int nb_img;


	 int score;
	 Text s; 

}background;

void initBackground(background *b); 
void initBackground2(background *b); 
void afficheBackground (background b, SDL_Surface *screen);
void afficheBackground2(background b, SDL_Surface *screen);
void scrolling (background *b,int direction,int pas);
void scrolling2 (background *b,int direction,int pas); 
void animerBackground(background *b);
void affiche_anim_back(background b,SDL_Surface *screen);




#endif  

