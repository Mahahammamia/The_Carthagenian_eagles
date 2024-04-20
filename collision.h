#ifndef _BOUNDING_BOX_H_
#define _BOUNDING_BOX_H_
#include <SDL/SDL.h>
#include <math.h>


int collisionBB(SDL_Rect x1,SDL_Rect x2);
int collisionTRI(SDL_Rect x1,SDL_Rect x2);

#endif
