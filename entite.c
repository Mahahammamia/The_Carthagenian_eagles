#include "entite.h"

void init_entite(entite * p) 
{
  ( * p).d_h = 0;
  ( * p).d_v = 0;
  ( * p).affichage = 1;
  ( * p).pos.x = 400 + rand() % 200;
  ( * p).pos.y = 200;
  ( * p).sprite.x = 0;
  ( * p).sprite.y = 0;
  ( * p).sprite_n = 0;
  ( * p).speed = 10;
  ( * p).image = IMG_Load("mini-coin.png");
  ( * p).pos.w = ( * p).image -> w/6;
  ( * p).pos.h = ( * p).image -> h;
  ( * p).sprite.w = ( * p).image -> w/6;
  ( * p).sprite.y = 0;
  ( * p).sprite.h = ( * p).image -> h;
}
void afficher_entite(entite p, SDL_Surface * screen) {
    SDL_BlitSurface(p.image, & p.sprite, screen, & p.pos);
}
void animer_entite(entite * p) 
{
    ( * p).sprite_n++;
    if (( * p).sprite_n >= 6) {
      ( * p).sprite_n = 0;
    }

    ( * p).sprite.x = ( * p).pos.w * ( * p).sprite_n;
}
void mouvement_aleatoire_entite(entite *p)
{
if (( * p).pos.x % 100<( * p).speed) ( * p).d_h=rand()%2;
if(( * p).pos.x<100) ( * p).d_h=0;
if(( * p).pos.x>500) ( * p).d_h=1;
if (( * p).d_h==1) ( * p).pos.x-=( * p).speed;
else ( * p).pos.x+=( * p).speed;

if (( * p).pos.y % 100<( * p).speed) ( * p).d_v=rand()%2;
if(( * p).pos.y<100) ( * p).d_v=0;
if(( * p).pos.y>450) ( * p).d_v=1;
if (( * p).d_v==1) ( * p).pos.y-=( * p).speed;
else ( * p).pos.y+=( * p).speed;
}
