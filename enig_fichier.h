#include <SDL/SDL_ttf.h>
#include <time.h>
#include <SDL/SDL_mixer.h>

typedef struct 
{
    SDL_Surface *image_Enigme[4]; 
    int current_frame; 
    //SDL_Surface *image_Enigme;
    SDL_Rect position_Enigme;
    SDL_Surface *reponse_1;
    SDL_Surface *reponse_2;
    SDL_Surface *reponse_3;
    SDL_Surface *question;
    SDL_Rect pos_reponse_1;
    SDL_Rect pos_reponse_2;
    SDL_Rect pos_reponse_3;
    SDL_Rect pos_question;
    SDL_Surface *correct;
    SDL_Surface *wrong;
    SDL_Rect position_correct;
    SDL_Rect position_wrong;
    SDL_Color Color;
    SDL_Color blanc;
    TTF_Font *police;
    Mix_Music *music;
    TTF_Font *police_q;
    int alea;
    int resultat;
    char* bonne_reponse;
    Mix_Chunk *congrats_sound;
    Mix_Chunk *wrong_sound;
} Enigme;

void init_Enigme( Enigme* e);
void afficherEnigme ( Enigme *e, SDL_Surface* screen);
void free_surface_Enigme( Enigme *e, SDL_Surface* screen );
void genererEnigme(Enigme *e , char* reponse, char* question, char* bonnes_reponses, SDL_Color Color);
int resolution(Enigme *e, SDL_Surface* screen);
void animerenigme(Enigme *e);

#endif
