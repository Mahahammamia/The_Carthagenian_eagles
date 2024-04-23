#include "back.h"
#include "perso.h"
#include <SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>

void initBackground(background *b)
{


b->img_back=IMG_Load("back_lvl1.png");
b->pos_back.x=0;
b->pos_back.y=0;



b->camera.x=0;
b->camera.y=250;
b->camera.w=SCREEN_W; 
b->camera.h=SCREEN_H;



         b->music2=Mix_LoadMUS("music2.mp3"); 
	 b->bref1 = Mix_LoadWAV("bref1.wav"); //
 	b->bref2 = Mix_LoadWAV("bref2.wav");

	b->img_anim=IMG_Load("animation.png");  

	b->pos_img_anim.x=125; 
	b->pos_img_anim.y=100;

	b->one_img.x=0;
	b->one_img.y=0;

	b->one_img.w=116;  
	b->one_img.h=140;  

	b->nb_img=0;  



TTF_Init();
b->s.font=TTF_OpenFont("angelina.TTF",50);

b->s.color=(SDL_Color) {0,0,0};
b->s.text=TTF_RenderText_Blended(b->s.font,"score1: 0",b->s.color);

b->s.postext.x=100;
b->s.postext.y=10;

b->score=0;

Mix_PlayMusic(b->music2, -1); 

}

void initBackground2(background *b)
{


b->img_back=IMG_Load("back_lvl1.png");
b->pos_back2.x=907;
b->pos_back2.y=0;



b->camera2.x=0;
b->camera2.y=250;
b->camera2.w=SCREEN_W; 
b->camera2.h=SCREEN_H;


	b->img_anim=IMG_Load("animation.png"); 
	b->pos_img_anim.x=1000;
	b->pos_img_anim.y=100;

	b->one_img.x=0;
	b->one_img.y=0;

	b->one_img.w=116;  
	b->one_img.h=140;  

	b->nb_img=0;  



TTF_Init();
b->s.font=TTF_OpenFont("angelina.TTF",50);

b->s.color=(SDL_Color) {0,0,0};
b->s.text=TTF_RenderText_Blended(b->s.font,"score2: 0",b->s.color); 

b->s.postext.x=1000;
b->s.postext.y=10;

b->score=0;


}

void afficheBackground (background b, SDL_Surface *screen)
{

	char sc[12];
	sprintf(sc,"score 1: %d",b.score);
	b.s.text=TTF_RenderText_Blended(b.s.font,sc,b.s.color);


	SDL_BlitSurface(b.img_back,&b.camera,screen,&b.pos_back);
	affiche_anim_back(b,screen); 
	SDL_BlitSurface(b.s.text,NULL,screen,&b.s.postext);


}
void afficheBackground2 (background b, SDL_Surface *screen)
{

	char sc[12];
	sprintf(sc,"score 2: %d",b.score);
	b.s.text=TTF_RenderText_Blended(b.s.font,sc,b.s.color);


	SDL_BlitSurface(b.img_back,&b.camera2,screen,&b.pos_back2);
	affiche_anim_back(b,screen); 
	SDL_BlitSurface(b.s.text,NULL,screen,&b.s.postext);

}

void scrolling (background *b,int direction,int pas)
{

if (direction ==0){   


	b->camera.x+= pas;
        b->score+=1;          
	
        }
else if (direction ==1){          


	b->camera.x-=pas; 
        b->score+=1;
	}
 
else if (direction ==2){


         b->camera.y-= pas;
         b->score+=1;
	}
else if (direction ==3){         


	 b->camera.y+= pas;
         b->score+=1;
	 }

}

void scrolling2 (background *b,int direction,int pas)
{

if (direction ==0){   


	b->camera2.x+= pas;
        b->score+=1;          
	
        }
else if (direction ==1){          


	b->camera2.x-=pas; 
        b->score+=1;
	}
 
else if (direction ==2){


         b->camera2.y-= pas;
         b->score+=1;
	}
else if (direction ==3){       


	 b->camera2.y+= pas;
         b->score+=1;
	 }

}

void animerBackground(background *b)
{
	if (b->nb_img >=0 && b->nb_img <9) {
	b->one_img.x=b->nb_img * b->one_img.w;
	b->nb_img++;
	}
	
	if ( b->nb_img == 9) { 
	b->one_img.x=b->nb_img * b->one_img.w;
	b->nb_img=0;
	}

}

void affiche_anim_back(background b,SDL_Surface *screen)
{
	SDL_BlitSurface(b.img_anim,&(b.one_img), screen, &b.pos_img_anim);
}









