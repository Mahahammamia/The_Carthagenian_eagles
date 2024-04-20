#include "collision.h"

int in_bounds(SDL_Rect x1,SDL_Rect x2)
{
return(x1.x>=x2.x)&&(x1.x<=x2.x+x2.w)&&((x1.y>=x2.y)&&(x1.y<=x2.y+x2.h)||((x1.y<=x2.y)&&(x1.y+x2.h>=x2.y)));
}
int collisionBB(SDL_Rect x1,SDL_Rect x2)
{
return in_bounds(x1,x2)||in_bounds(x2,x1);
}
int collisionTRI(SDL_Rect x1,SDL_Rect x2)
{
int r1,r2;
if (x1.w>x1.h) r1 = x1.w/2;
else r1 = x1.h/2;
if (x2.w>x2.h) r2 = x2.w/2;
else r2 = x2.h/2;
int distance = sqrt( (x2.y - x1.y)*(x2.y - x1.y) + (x2.x - x1.x)*(x2.x - x1.x) );
if(r1+r2>distance) return 1;
return 0;
}
