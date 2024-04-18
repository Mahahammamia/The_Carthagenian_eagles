#include "enig_fichier.h"
#include <SDL/SDL_mixer.h>

void init_Enigme( Enigme* e)
{
    e->image_Enigme[0] = IMG_Load("bg_enigme.jpg");
    e->image_Enigme[1] = IMG_Load("wel.jpg");
    e->image_Enigme[2] = IMG_Load("TO.jpg");
    e->image_Enigme[3] = IMG_Load("animation.jpg");
    e->current_frame = 0;
    e->position_Enigme.x = 0;
    e->position_Enigme.y = 0;
    e->resultat = 0;
    e->correct =IMG_Load("correct.png");
    e->wrong =IMG_Load("wrong.png");
    e->position_correct.x = 1050;
    e->position_correct.y = 380;
    e->position_wrong.x = 1050;
    e->position_wrong.y = 380;

    e->police=TTF_OpenFont("police.ttf",50 );
    e->reponse_1 = NULL;
    e->pos_reponse_1.x=800;
    e->pos_reponse_1.y=500;

    e->reponse_2 = NULL;
    e->pos_reponse_2.x=1050;
    e->pos_reponse_2.y=500;

    e->reponse_3 =NULL;
    e->pos_reponse_3.x=1300;
    e->pos_reponse_3.y=500;

    e->police_q=TTF_OpenFont("police.ttf",45 );
    e->question = NULL;
    e->pos_question.x=750;
    e->pos_question.y=250;

    e->alea = 0;

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }

   
    e->music = Mix_LoadMUS("game1.mp3");
    if(e->music == NULL)
    {
        printf("%s", Mix_GetError());
    }

    
    Mix_PlayMusic(e->music, -1);
    e->congrats_sound = Mix_LoadWAV("congratulations.wav");
    e->wrong_sound = Mix_LoadWAV("wrong.wav");



}

void animerenigme(Enigme *e)
{
  e->current_frame++;
  if (e->current_frame == 4)
    e->current_frame = 0;
}
void afficherEnigme ( Enigme *e, SDL_Surface* screen)
{
        SDL_BlitSurface(e->image_Enigme[e->current_frame],NULL, screen, &e->position_Enigme );  
        SDL_Delay(100);
        e->current_frame = (e->current_frame + 1) % 4; //
        SDL_Flip(screen);
        //SDL_BlitSurface(e->image_Enigme,NULL, screen, &e->position_Enigme );
	SDL_BlitSurface(e->reponse_1,NULL,screen,&e->pos_reponse_1);
        SDL_BlitSurface(e->reponse_2,NULL,screen,&e->pos_reponse_2);
        SDL_BlitSurface(e->reponse_3,NULL,screen,&e->pos_reponse_3);
        SDL_BlitSurface(e->question,NULL,screen,&e->pos_question);
}

void free_surface_Enigme( Enigme *e,SDL_Surface* screen )
{  
    for(int i = 0; i < 4; i++)
    {
        SDL_FreeSurface(e->image_Enigme[i]);
    }
    //SDL_FreeSurface(e->image_Enigme);
    SDL_FreeSurface(e->correct);
    SDL_FreeSurface(e->wrong);
    SDL_FreeSurface(e->reponse_1);
    SDL_FreeSurface(e->reponse_2);
    SDL_FreeSurface(e->reponse_3);
    SDL_FreeSurface(e->question);
    TTF_CloseFont(e->police);
    TTF_CloseFont(e->police_q);
    Mix_FreeMusic(e->music);
    Mix_CloseAudio();
    Mix_FreeChunk(e->congrats_sound);
    Mix_FreeChunk(e->wrong_sound);
 
}

void genererEnigme(Enigme *e , char* reponse, char* question, char* bonnes_reponses, SDL_Color Color)

{
    FILE* fichier = NULL;
    FILE* fichier_reponse = NULL;
    FILE* fichier_bonne_reponse = NULL; 
    char ques[60] = {0};
    char rep1[20] = {0};
    char rep2[20] = {0};
    char rep3[20] = {0};
    char bonne_rep[20] = {0}; 
    int caracterelu_question,caracterelu_reponses,ligne =1,ligne_reponse=1;
    srand(time(0));
    do {
        e->alea = rand()%3 +1;
    }while ( e->alea <1 || e->alea > 3 );

    fichier_reponse = fopen("reponse.txt","r"); 
    fichier = fopen("question.txt","r"); 
    fichier_bonne_reponse = fopen("bonnes_reponses.txt","r");  
    if ( fichier != NULL && fichier_reponse != NULL && fichier_bonne_reponse != NULL )
    {
        while ( caracterelu_question!=EOF && ligne < e->alea )
        {
            caracterelu_question = fgetc(fichier);
            if ( caracterelu_question == '\n')
                ligne++;
        }
        fgets(ques,45,fichier);
        fclose(fichier);
        while ( caracterelu_reponses!=EOF && ligne_reponse < e->alea )
        {
            caracterelu_reponses = fgetc(fichier_reponse);
            if ( caracterelu_reponses == '\n')
                ligne_reponse++;
        }
        fscanf(fichier_reponse,"%s %s %s",rep1,rep2,rep3);
        fclose(fichier_reponse);
        fgets(bonne_rep, 20, fichier_bonne_reponse);
        fclose(fichier_bonne_reponse);
    }
    SDL_Color blanc = {255, 0, 255};
    e->question = TTF_RenderText_Blended(e->police_q,ques,blanc);
    e->reponse_1 = TTF_RenderText_Blended(e->police,rep1,Color);
    e->reponse_2 = TTF_RenderText_Blended(e->police,rep2,Color);
    e->reponse_3 = TTF_RenderText_Blended(e->police,rep3,Color);
    e->bonne_reponse = bonne_rep; 
}





int resolution(Enigme *e, SDL_Surface* screen)
{

    SDL_Event event;
    int continuer=1;
    char reponse[20]; 
    char question[60];
    char bonnes_reponses[20];
    SDL_Color Color = {0,0,0};
    genererEnigme(e, reponse, question, bonnes_reponses, Color);
    while(continuer == 1)
    {
        while (SDL_PollEvent(&event)){ 
        switch(event.type)
        {
        case SDL_QUIT:
            continuer=0;

            break;

        case SDL_MOUSEBUTTONDOWN:
        {
            switch(event.button.button)
            {
            case SDL_BUTTON_LEFT:
            {
                if ( event.button.x>800 && event.button.x<950 && event.button.y>500 && event.button.y<600) 
                {
                    if ( e->alea == 1 )
                    {
                        e->resultat= 1;
                    }
                    else if ( e->alea == 2)
                    {
                        e->resultat = 2;
                    }
                    else if ( e->alea == 3)
                    {
                        e->resultat = 1;
                    }
                    
                }
                if ( event.button.x>1050 && event.button.x<1200 && event.button.y>500 && event.button.y<600) 
                {
                    if ( e->alea == 1 )
                    {
                        e->resultat= 2;
                    }
                    else if ( e->alea == 2)
                    {
                        e->resultat = 2;
                    }
                    else if ( e->alea == 3)
                    {
                        e->resultat = 2;
                    }
                }
                if ( event.button.x>1300 && event.button.x<1450 && event.button.y>500 && event.button.y<600) 
                {
                    if ( e->alea == 1 )
                    {
                        e->resultat= 2;
                    }
                    else if ( e->alea == 2)
                    {
                        e->resultat = 1;
                    }
                    else if ( e->alea == 3)
                    {
                        e->resultat = 2;
                    }
                }
            }
            break; 
            }
        }
        break;

        }}
         afficherEnigme(e, screen);

            if ( e->resultat == 1 )
{
    Mix_PlayChannel(-1, e->congrats_sound, 0);
    SDL_BlitSurface(e->correct,NULL, screen, &e->position_correct );
    SDL_Flip(screen);
    SDL_Delay(2000);
    continuer = 0;
    return 1;
}
else if ( e->resultat == 2 )
{
    Mix_PlayChannel(-1, e->wrong_sound, 0);
    SDL_BlitSurface(e->wrong,NULL, screen, &e->position_wrong );
    SDL_Flip(screen);
    SDL_Delay(2000);
    continuer = 0;
    return 2;
}


        SDL_Flip(screen);


    }

}


