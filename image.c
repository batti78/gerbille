#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <err.h>
#include "image.h"

static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
      int bpp = surf->format->BytesPerPixel;
            return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}


Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) 
{
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
    case 1:
      return *p;
    case 2:
      return *(Uint16 *)p;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
      return *(Uint32 *)p;
  }
  return 0;
}


SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  img = IMG_Load(path);
  if (!img)
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}


void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
    case 1:
      *p = pixel;
      break;
    case 2:
      *(Uint16 *)p = pixel;
      break;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
      } 
      else {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
      }
      break;
      case 4:
      *(Uint32 *)p = pixel;
      break;
  }
}

void init_sdl(void) {
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
    }
}

unsigned long[][] integrale(SDL_Surface *img)
{
  unsigned integ[(img->w),(img->h)] = malloc(integ);
  int w, h;
  for (w = 0; w < img->w; w++)
  {
    for (h = 0; w < img->h; h++)
    {
      integ[w][h] = (unsigned long)getpixel(img, w, h);
      if(w != 0)
        integ[w][h] += integ[w-1,h];
      if(h != 0)
        integ[w][h] += integ[w,h-1];
    }
  }

}
