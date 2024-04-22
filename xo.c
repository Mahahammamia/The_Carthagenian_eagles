#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <limits.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>
#include "xo.h"
#include <math.h>
SDL_Surface *l,*d,*w,*anim;
void initialisation(tic * t)
{
    int i;
    for(i=0;i<9;i++)
    t-> tabsuivi[i]=0;
    t->image1=IMG_Load("fond.jpg");
    t->image2=IMG_Load("croix.jpg");
    t->image3=IMG_Load("rond.jpg");



    t->joueur=1;
    t->tour=0;
    t->comic=TTF_OpenFont("comic.ttf",40);

    t->couleur.r=0;
    t->couleur.g=0;
    t->couleur.b=0;
    t->posMSG.x=0;
    t->posMSG.y=0;
}
void affichage(tic t,SDL_Surface *ecran ) 
{
    int i;

    SDL_BlitSurface(t.image1,NULL,ecran,NULL);
    for(i=0;i<9;i++)
   {
		t.pos.x=190*(i%3);
		t.pos.y=190*(i/3);
        	switch(t.tabsuivi[i])
        	{
            		case -1:
                		SDL_BlitSurface(t.image2,NULL,ecran,&t.pos);	
            		break;
            		case 1:
                		SDL_BlitSurface(t.image3,NULL,ecran,&t.pos);
            		break;
        	}	
    }}
    
void liberationmemoire(tic t)
{
    SDL_FreeSurface(t.image1);
    SDL_FreeSurface(t.image2);
    SDL_FreeSurface(t.image3);
}
int atilganer(int tabsuivi[])
{
    int lignes_gagnantes[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i=0;i<8;++i)
        if(tabsuivi[lignes_gagnantes[i][0]]!=0&&
           tabsuivi[lignes_gagnantes[i][0]]==tabsuivi[lignes_gagnantes[i][1]]&&
           tabsuivi[lignes_gagnantes[i][0]]==tabsuivi[lignes_gagnantes[i][2]])
                return tabsuivi[lignes_gagnantes[i][2]];
    return 0;
}
int minimax(int tabsuivi[],int joueur)
{
    int gagnant=atilganer(tabsuivi);
    if(gagnant!=0)
        return gagnant*joueur;
    int coup=-1;
    int score=-2;
    int i;
    for(i=0;i<9;++i)
    {
        if(tabsuivi[i]==0)
        {
            tabsuivi[i]=joueur;
            int mmscore=-minimax(tabsuivi,joueur*-1);
            if(mmscore>score)
            {
                score=mmscore;
                coup=i;
            }
            tabsuivi[i]=0;
        }
    }
    if(coup==-1)
        return 0;
    return score;
}

void calcul_coup(int tabsuivi[])
{
    int coup=-1;
    int score=-2;
    int i;
    for(i=0;i<9;++i)
    {
        if(tabsuivi[i]==0)
        {
            tabsuivi[i]=1;
            int mmscore=-minimax(tabsuivi,-1);
            tabsuivi[i]=0;
            if(mmscore>score)
            {
                score=mmscore;
                coup=i;
            }
        }
    }
    tabsuivi[coup]=1;
}




void Resultat(tic t, SDL_Surface* ecran) {
    SDL_Rect pos;
    char msg[20];
	w=IMG_Load("winner.jpg");
        l=IMG_Load("loser.png");
        d=IMG_Load("draw.jpg");

    SDL_FillRect(ecran, 0, SDL_MapRGB(ecran->format, 255, 255, 255));
    pos.x = 0;
    pos.y = 0;
    affichage(t, ecran);
    switch (atilganer(t.tabsuivi)) {
        case 0:
SDL_BlitSurface(d,NULL,ecran,&pos);
            strcpy(msg, "It's a draw!");
            break;
        case 1:
SDL_BlitSurface(l,NULL,ecran,&pos);
            strcpy(msg, "Player wins!");
            break;
        case -1:
SDL_BlitSurface(w,NULL,ecran,&pos);
            strcpy(msg, "Computer wins!");
    }
	
    
    SDL_Flip(ecran);
    SDL_Delay(2000); 
}
void Rotozoom(SDL_Surface *ecran)
{
    SDL_Surface *loaded_image = IMG_Load("loser.png");
    SDL_Surface *optimized_image = NULL;
    SDL_Surface *background = NULL;
        Uint32 start_time = SDL_GetTicks();

    if (loaded_image != NULL)
    {
        optimized_image = SDL_DisplayFormatAlpha(loaded_image);
        SDL_FreeSurface(loaded_image);
    }

    background = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, ecran->w, ecran->h, ecran->format->BitsPerPixel,
                                       ecran->format->Rmask, ecran->format->Gmask, ecran->format->Bmask, ecran->format->Amask);
    SDL_FillRect(background, NULL, SDL_MapRGBA(background->format, 0, 0, 0, 0));

    if (optimized_image != NULL)
    {
        SDL_Rect dstrect;
        dstrect.w = optimized_image->w;
        dstrect.h = optimized_image->h;
        dstrect.x =0;
        dstrect.y =0;

        double angle = 0;
        double zoom = 1;
        double rotation_speed = 1;
        double zoom_speed = 0.01;
        SDL_Event event;
        int quit = 0;

        while (!quit)
        {
     
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit = 1;
                }
            }

            angle += rotation_speed;
            zoom += zoom_speed;


            SDL_BlitSurface(background, &dstrect, ecran, &dstrect);


            SDL_Surface *rotozoomed_image = rotozoomSurface(optimized_image, angle, zoom, SMOOTHING_ON);
            SDL_Rect image_rect = {0, 0, rotozoomed_image->w, rotozoomed_image->h};


            SDL_SetAlpha(rotozoomed_image, SDL_SRCALPHA, 128);
            SDL_BlitSurface(rotozoomed_image, &image_rect, ecran, &dstrect);

            SDL_FreeSurface(rotozoomed_image);

            SDL_Flip(ecran);
            SDL_Delay(10);
            if (SDL_GetTicks() - start_time >= 10000)
            {
                quit = 1;
            }

        }
       
        SDL_FreeSurface(optimized_image);
    }

    SDL_FreeSurface(background);
}
void Rotozoom2(SDL_Surface *ecran)
{
    SDL_Surface *loaded_image = IMG_Load("winner.jpg");
    SDL_Surface *optimized_image = NULL;
    SDL_Surface *background = NULL;
    Uint32 start_time = SDL_GetTicks();

    if (loaded_image != NULL)
    {
        optimized_image = SDL_DisplayFormatAlpha(loaded_image);
        SDL_FreeSurface(loaded_image);
    }

    background = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, ecran->w, ecran->h, ecran->format->BitsPerPixel,
                                       ecran->format->Rmask, ecran->format->Gmask, ecran->format->Bmask, ecran->format->Amask);
    SDL_FillRect(background, NULL, SDL_MapRGBA(background->format, 0, 0, 0, 0));

    if (optimized_image != NULL)
    {
        SDL_Rect dstrect;
        dstrect.w = optimized_image->w;
        dstrect.h = optimized_image->h;
        dstrect.x = 0;
        dstrect.y = 0;

        double angle = 0;
        double zoom = 1;
        double rotation_speed = 1;
        double zoom_speed = 0.01;
        SDL_Event event;
        int quit = 0;

        while (!quit)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit = 1;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            zoom += 0.1; // Augmenter le zoom
                            break;
                        case SDLK_DOWN:
                            zoom -= 0.1; // Diminuer le zoom
                            break;
                    }
                }
            }

            angle += rotation_speed;

            SDL_BlitSurface(background, &dstrect, ecran, &dstrect);

            SDL_Surface *rotozoomed_image = rotozoomSurface(optimized_image, angle, zoom, SMOOTHING_ON);
            SDL_Rect image_rect = {0, 0, rotozoomed_image->w, rotozoomed_image->h};

            SDL_SetAlpha(rotozoomed_image, SDL_SRCALPHA, 128);
            SDL_BlitSurface(rotozoomed_image, &image_rect, ecran, &dstrect);

            SDL_FreeSurface(rotozoomed_image);

            SDL_Flip(ecran);
            SDL_Delay(10);
            if (SDL_GetTicks() - start_time >= 10000)
            {
                quit = 1;
            }
        }

        SDL_FreeSurface(optimized_image);
    }

    SDL_FreeSurface(background);
}

/*void Rotozoom2(SDL_Surface *ecran)
{
    SDL_Surface *loaded_image = IMG_Load("winner.jpg");
    SDL_Surface *optimized_image = NULL;
    SDL_Surface *background = NULL;
        Uint32 start_time = SDL_GetTicks();

    if (loaded_image != NULL)
    {
        optimized_image = SDL_DisplayFormatAlpha(loaded_image);
        SDL_FreeSurface(loaded_image);
    }

    background = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, ecran->w, ecran->h, ecran->format->BitsPerPixel,
                                       ecran->format->Rmask, ecran->format->Gmask, ecran->format->Bmask, ecran->format->Amask);
    SDL_FillRect(background, NULL, SDL_MapRGBA(background->format, 0, 0, 0, 0));

    if (optimized_image != NULL)
    {
        SDL_Rect dstrect;
        dstrect.w = optimized_image->w;
        dstrect.h = optimized_image->h;
        dstrect.x =0;
        dstrect.y =0;

        double angle = 0;
        double zoom = 1;
        double rotation_speed = 1;
        double zoom_speed = 0.01;
        SDL_Event event;
        int quit = 0;

        while (!quit)
        {
     
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit = 1;
                }
            }

            angle += rotation_speed;
            zoom += zoom_speed;


            SDL_BlitSurface(background, &dstrect, ecran, &dstrect);


            SDL_Surface *rotozoomed_image = rotozoomSurface(optimized_image, angle, zoom, SMOOTHING_ON);
            SDL_Rect image_rect = {0, 0, rotozoomed_image->w, rotozoomed_image->h};


            SDL_SetAlpha(rotozoomed_image, SDL_SRCALPHA, 128);
            SDL_BlitSurface(rotozoomed_image, &image_rect, ecran, &dstrect);

            SDL_FreeSurface(rotozoomed_image);

            SDL_Flip(ecran);
            SDL_Delay(10);
            if (SDL_GetTicks() - start_time >=10000)
            {
                quit = 1;
            }

        }
       
        SDL_FreeSurface(optimized_image);
    }

    SDL_FreeSurface(background);
}*/

void Rotozoom3(SDL_Surface *ecran)
{
    SDL_Surface *loaded_image = IMG_Load("draw.jpg");
    SDL_Surface *optimized_image = NULL;
    SDL_Surface *background = NULL;
        Uint32 start_time = SDL_GetTicks();

    if (loaded_image != NULL)
    {
        optimized_image = SDL_DisplayFormatAlpha(loaded_image);
        SDL_FreeSurface(loaded_image);
    }

    background = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, ecran->w, ecran->h, ecran->format->BitsPerPixel,
                                       ecran->format->Rmask, ecran->format->Gmask, ecran->format->Bmask, ecran->format->Amask);
    SDL_FillRect(background, NULL, SDL_MapRGBA(background->format, 0, 0, 0, 0));

    if (optimized_image != NULL)
    {
        SDL_Rect dstrect;
        dstrect.w = optimized_image->w;
        dstrect.h = optimized_image->h;
        dstrect.x =0;
        dstrect.y =0;

        double angle = 0;
        double zoom = 1;
        double rotation_speed = 1;
        double zoom_speed = 0.01;
        SDL_Event event;
        int quit = 0;

        while (!quit)
        {
     
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit = 1;
                }
            }

            angle += rotation_speed;
            zoom += zoom_speed;


            SDL_BlitSurface(background, &dstrect, ecran, &dstrect);


            SDL_Surface *rotozoomed_image = rotozoomSurface(optimized_image, angle, zoom, SMOOTHING_ON);
            SDL_Rect image_rect = {0, 0, rotozoomed_image->w, rotozoomed_image->h};


            SDL_SetAlpha(rotozoomed_image, SDL_SRCALPHA, 128);
            SDL_BlitSurface(rotozoomed_image, &image_rect, ecran, &dstrect);

            SDL_FreeSurface(rotozoomed_image);

            SDL_Flip(ecran);
            SDL_Delay(10);
            if (SDL_GetTicks() - start_time >=10000)
            {
                quit = 1;
            }

        }
       
        SDL_FreeSurface(optimized_image);
    }

    SDL_FreeSurface(background);
}
void animation(SDL_Surface* ecran){

SDL_Rect pos;
pos.x=0;
pos.y=10;
anim=IMG_Load("pelastine.jpg");
SDL_BlitSurface(anim,NULL,ecran,&pos);
pos.x=pos.x+10;
if(pos.x<541){
pos.x=pos.x+10;
}


SDL_Flip(ecran);

}
void animation2(SDL_Surface* ecran){

SDL_Rect pos;
pos.x=0;
pos.y=450;
anim=IMG_Load("pelastine.jpg");
SDL_BlitSurface(anim,NULL,ecran,&pos);
pos.x=pos.x+10;
if(pos.x<541){
pos.x=pos.x+10;
}

SDL_Flip(ecran);

}
void animation3(SDL_Surface* ecran){

SDL_Rect pos;
pos.x=480;
pos.y=0;
anim=IMG_Load("pelastine.jpg");
SDL_BlitSurface(anim,NULL,ecran,&pos);
pos.x=pos.x+10;
if(pos.x<541){
pos.x=pos.x+10;
}

SDL_Flip(ecran);

}
void animation4(SDL_Surface* ecran){

SDL_Rect pos;
pos.x=480;
pos.y=450;
anim=IMG_Load("pelastine.jpg");
SDL_BlitSurface(anim,NULL,ecran,&pos);
pos.x=pos.x+10;
if(pos.x<541){
pos.x=pos.x+10;
}

SDL_Flip(ecran);

}








