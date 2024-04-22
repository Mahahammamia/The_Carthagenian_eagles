         #include <stdlib.h>
	#include <stdio.h>
	#include <SDL/SDL.h>
	#include <SDL/SDL_image.h>
	#include <SDL/SDL_ttf.h>
	#include"minimap.h"
        #include<string.h>


void init_minimap(minimap *m)
	{
	
	m->pos.x=800;
	m->pos.y=10;
	
	m->image=IMG_Load("minimap.bmp");
	m->pos_temp.x=50;
	m->pos_temp.y=30;
        m->pos_tempEnigme.x=300;
        m->pos_tempEnigme.y=200;

       m->img_pers=IMG_Load("point.png");  

        m->pos_pers.x=0;
	m->pos_pers.y=0;
	
	m->single_img.w=81;
	m->single_img.h=63;
	m->single_img.x=0;
	m->single_img.y=0;
	m->img_num=0;

       
        }


void MAJMinimap(perso p, minimap * m)

{ 

m->pos_pers.x=p.pos_background.x/3+m->pos.x-40;
m->pos_pers.y=p.pos_background.y/10+m->pos.y+60;
}

void afficherminimap (minimap m, SDL_Surface * screen)
{
SDL_BlitSurface(m.image,NULL,screen,&m.pos);
SDL_BlitSurface(m.img_pers,&m.single_img,screen,&m.pos_pers);
}
void gestiontemp(minimap m,SDL_Surface * screen)
{
                TTF_Init();
                SDL_Color couleur;
                couleur.r=138;
                couleur.g=138;
                couleur.b=138;
                TTF_Font* police=NULL;
                police=TTF_OpenFont("angelina.TTF",60);
                sprintf(m.temp,"tempsJ: %d s",m.temp_sec);
                m.temps=TTF_RenderText_Solid(police,m.temp,couleur);
                SDL_BlitSurface(m.temps,NULL,screen,&m.pos_temp);
                TTF_CloseFont(police);
                TTF_Quit();
                 SDL_FreeSurface(m.temps);
}
	void gestiontempEnigme(minimap m,SDL_Surface * screen)
{

  TTF_Init();
                SDL_Color couleur;
                couleur.r=255;
                couleur.g=255;
                couleur.b=0;
                TTF_Font* police=NULL;
                police=TTF_OpenFont("angelina.TTF",60);
                sprintf(m.temp,"tempsE: %d s",m.temp_sec);
                m.temps=TTF_RenderText_Solid(police,m.temp,couleur);
                SDL_BlitSurface(m.temps,NULL,screen,&m.pos_tempEnigme);
                TTF_CloseFont(police);
                TTF_Quit();
                 SDL_FreeSurface(m.temps);



}
        void initperso(perso *p)

{

p->image=IMG_Load("perso.png");
p->pos_background.x=50;
p->pos_background.y=50;
p->pos_background.w=10;
p->pos_background.h=50;

}
        void initbackground( photo *b)

{
     b->imag=IMG_Load("background.bmp");
     b->pos.x=0;
     b->pos.y=0;
}

  void initbackgroundEnigme( photo *b)

{
     b->imagenigme=IMG_Load("enigme.jpg");
     b->posenigme.x=200;
     b->posenigme.y=200;
}


SDL_Color GetPixel(SDL_Surface *surface,int x,int y)
{
SDL_Color color ;
Uint32 col = 0 ;
char* pPosition = ( char* ) surface->pixels ;
pPosition += ( surface->pitch * y ) ;
pPosition += ( surface->format->BytesPerPixel * x ) ;
memcpy ( &col , pPosition , surface->format->BytesPerPixel ) ;
SDL_GetRGB ( col , surface->format , &color.r , &color.g , &color.b ) ;
return ( color ) ;
}
int  collisionparfaite(SDL_Surface *psurface,perso p)
{
int i;
SDL_Color couleur;
SDL_Rect *pos;
pos=(SDL_Rect*)malloc(sizeof(SDL_Rect)*8);
pos[0].x=p.pos_background.x;
pos[0].y=p.pos_background.y;


pos[1].x=p.pos_background.x+(p.pos_background.w/2);
pos[1].y=p.pos_background.y;

pos[2].x=p.pos_background.x+p.pos_background.w;
pos[2].y=p.pos_background.y;


pos[3].x=p.pos_background.x;
pos[3].y=p.pos_background.y+(p.pos_background.h/2);


pos[4].x=p.pos_background.x;
pos[4].y=p.pos_background.y+p.pos_background.h;


pos[5].x=p.pos_background.x+(p.pos_background.w/2);
pos[5].y=p.pos_background.y+p.pos_background.h;

pos[6].x=p.pos_background.x+p.pos_background.w;
pos[6].y=p.pos_background.y+p.pos_background.h;


pos[7].x=p.pos_background.x+p.pos_background.w;
pos[7].y=p.pos_background.y+(p.pos_background.h/2);
for(i=0;i<8;i++){
couleur=GetPixel(psurface,pos[i].x,pos[i].y);

if(couleur.r==0 && couleur.g==0 && couleur.b==0)
return i;
}

}




void collision(SDL_Surface *psurface,perso *p)
{	int i;
	i=collisionparfaite(psurface,*p);

	switch (i)
	{
		case 0 :p->pos_background.y=p->pos_background.y+15;
			break;
		case 1 :p->pos_background.y=p->pos_background.y+15;
			 break;
		case 2 :p->pos_background.y=p->pos_background.y+15;
			break;
		case 3 :p->pos_background.x=p->pos_background.x+15;
			break;
	        case 4 :p->pos_background.y=p->pos_background.y-15;
			break;
		case 5 :p->pos_background.y=p->pos_background.y-15; 
			break;
		case 6 :p->pos_background.y=p->pos_background.y-15; 
			break;
		case 7 :p->pos_background.x=p->pos_background.x-15;
			break;
		

	}
}

        void animerMinimap(minimap *e){
		 	
	if (e->img_num >=0 && e->img_num <3) {
        	e->img_num++;
	e->single_img.x=e->img_num * e->single_img.w;


	
	}
	
	if ( e->img_num == 3) {
         	e->img_num=0;
	e->single_img.x=e->img_num * e->single_img.w;

	
	}
	printf("%d ",e->img_num);
	 
 
}


