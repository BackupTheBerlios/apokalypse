
//sdl_utils.cpp

#include "sdl_utils.h"
#include "logging.h"
#include <alloc.h>

//Routine zum skalieren von Bildern BEGIN
void scalepattern(int *dpattern, int x, int y){
	int a,dx,dy;
	x--;
	y--;
	if (x>y){
		dy = 2*y;
		dx=a=2*x-dy;
		do{
			dpattern[y]=x;
			if (a<=0){
				y--;
				a+=dx;
				}else a-=dy;
			}while(x--);
		}else{
		dy=2*x;
		dx=a=2*y-dy;
		do{
			dpattern[y]=x;
			if (a<=0){
				x--;
				a+=dx;
				}else a-=dy;
			}while(y--);
		}
}

void scalesurface(SDL_Surface *dest, SDL_Surface *src){
	if (!dest || !src) return;
	int *xpattern = (int*)malloc(dest->w * sizeof(int));
	int *ypattern = (int*)malloc(dest->h * sizeof(int));
	int ix,iy,pc;

	scalepattern(xpattern, src->w, dest->w);
	scalepattern(ypattern, src->h, dest->h);
	Uint8 *destbuf = (Uint8*)dest->pixels;
	Uint8 *srcbuf = (Uint8*)src->pixels;

	for( iy=0; iy < dest->h; iy++ ){
		for( ix=0; ix < dest->w; ix++ ){
			for( pc=0; pc < dest->format->BytesPerPixel; pc++){
				*(destbuf+(iy*dest->pitch)+(ix*dest->format->BytesPerPixel)+pc) =
					*(srcbuf+(ypattern[iy]*src->pitch)+(xpattern[ix]*src->format->BytesPerPixel)+pc);
				}
			}
		}

	free(xpattern);
	free(ypattern);
	LogDebug("scaled image (%d,%d)-->(%d,%d)",src->w,src->h,ix,iy);
}

//END


