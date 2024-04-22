        #ifndef Header_H
	#define Header_H
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <SDL/SDL.h>
	#include <SDL/SDL_image.h>
	#include <SDL/SDL_ttf.h>
	
	typedef struct {
	  SDL_Surface * image;
	  SDL_Surface * temps;
	  SDL_Rect pos,pos_temp,pos_tempEnigme;
	  SDL_Surface * img_pers;
 	  SDL_Rect pos_pers;
          char temp[20];
	  SDL_Rect single_img;
          int img_num;

          int temp_sec;

	}minimap;
	typedef struct perso
         {

     SDL_Surface *image;
     SDL_Rect pos_background;             
       }perso;

      typedef struct{
      SDL_Surface *imag;

      SDL_Surface *imagenigme;
      SDL_Rect pos;
      SDL_Rect posenigme;
      }photo;
        
        void animerMinimap(minimap *m);
	void init_minimap(minimap *m);
	void MAJMinimap(perso p, minimap * m);
	void afficherminimap (minimap m, SDL_Surface * screen);
	void gestiontemp(minimap m,SDL_Surface * screen); 
	void gestiontempEnigme(minimap m,SDL_Surface * screen); 
        void initperso(perso *p);     
        void initbackground( photo *b);
        void initbackgroundEnigme( photo *b);
        SDL_Color GetPixel(SDL_Surface *surface,int x,int y);
        int  collisionparfaite(SDL_Surface *psurface,perso p);
        void collision(SDL_Surface *psurface,perso *p);
	#endif
