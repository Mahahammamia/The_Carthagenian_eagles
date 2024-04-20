#include "ennemi.h"


void init_ennemi(ennemi * p) 
{
  ( * p).d = 0;
  ( * p).vie = 100;
  ( * p).pos.x = rand() % 600;
  ( * p).pos.y = 435;
  ( * p).sprite.x = 0;
  ( * p).sprite.y = 0;
  ( * p).state = 0;
  ( * p).sprite_n = 0;
  ( * p).speed = 5;
  ( * p).image = IMG_Load("ennemi.png");
  ( * p).pos.w = ( * p).image -> w/4;
  ( * p).pos.h = ( * p).image -> h/4;
  ( * p).sprite.w = ( * p).image -> w/4;
  ( * p).sprite.h = ( * p).image -> h/4;
}
void afficher_ennemi(ennemi p, SDL_Surface * screen) {
    SDL_BlitSurface(p.image, & p.sprite, screen, & p.pos);

}
void animer_ennemi(ennemi * p) 
{
    ( * p).sprite_n++;
    if (( * p).sprite_n >= 4) {
      ( * p).sprite_n = 0;
    }

    ( * p).sprite.x = ( * p).pos.w * ( * p).sprite_n;
    ( * p).sprite.y = ( * p).pos.h * 2*( * p).d;
}
void mouvement_aleatoire_ennemi(ennemi *p)
{
if (( * p).pos.x % 50<5) ( * p).d=rand()%2;
if(( * p).pos.x<50) ( * p).d=1;
if(( * p).pos.x>300) ( * p).d=0;
if (( * p).d==0) ( * p).pos.x-=( * p).speed;
else ( * p).pos.x+=( * p).speed;
}
