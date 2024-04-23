#include "perso.h"



void init_perso(perso *p)
{	
	p->img_perso=IMG_Load("perso.bmp");
	p->pos_perso.x=0;
	p->pos_perso.y=530;
	p->keystate = SDL_GetKeyState(NULL);
}

void init_perso2(perso *p)
{	
	p->img_perso=IMG_Load("perso.bmp");
	p->pos_perso2.x=910; 
	p->pos_perso2.y=530;
	p->keystate = SDL_GetKeyState(NULL);
}


void afficher_perso(SDL_Surface *screen,perso p)
{	
	SDL_BlitSurface(p.img_perso,NULL,screen,&p.pos_perso);
}

void afficher_perso2(SDL_Surface *screen,perso p)
{	
	SDL_BlitSurface(p.img_perso,NULL,screen,&p.pos_perso2);
}

void deplacer_perso(perso *p)
{	
   
	if(p->keystate[SDLK_UP])
	{
		if(p->pos_perso.y>0)
		{
                            p->pos_perso.y=p->pos_perso.y-6;
                           
		}
	}
                            
	if(p->keystate[SDLK_DOWN])
	{
		if(p->pos_perso.y<612)
		{
                            p->pos_perso.y=p->pos_perso.y+6;
                            
		}
	}

	if(p->keystate[SDLK_RIGHT])
	{
		if(p->pos_perso.x<750) //1014
		{
                            p->pos_perso.x=p->pos_perso.x+2; 
                       
		}
	}

	if(p->keystate[SDLK_LEFT])
	{
		if(p->pos_perso.x>0)
		{
                            p->pos_perso.x=p->pos_perso.x-2; 
                           
		}
	}
}
void deplacer_perso2(perso *p)
{
	                        
if(p->keystate[SDLK_z])
{
if(p->pos_perso2.y>0){
                            p->pos_perso2.y=p->pos_perso2.y-6;
                            
}

}
if(p->keystate[SDLK_s])
{
if(p->pos_perso2.y<612){
                            p->pos_perso2.y=p->pos_perso2.y+6; 
                            
}
}
if(p->keystate[SDLK_d])
{
if(p->pos_perso2.x<1500){ 	
                            p->pos_perso2.x=p->pos_perso2.x+2; 
                           
}
}
if(p->keystate[SDLK_q])
{
if(p->pos_perso2.x>1000){ 
                            p->pos_perso2.x=p->pos_perso2.x-2;
                            
}
}

}


void free_perso(perso p)
{
	SDL_FreeSurface(p.img_perso);
}


