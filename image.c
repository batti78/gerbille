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

void grey(SDL_Surface *img)
{
  Uint8 r, g, b, med, max = 0;
  Uint8 min = 255;
  unsigned x,y;
  for (x = 0; x < (unsigned) img->h; x++)
  {
    for (y = 0; y < (unsigned) img->w; y++)
    {
      SDL_GetRGB(getpixel(img, y, x), img->format, &r, &g, &b);
      med = 0.3 * r + 0.59 * g + 0.11 * b;
      r = g = b = med;
      max = (max < med ? med : max);
      min = (min > med ? med : min);
      putpixel(img, y, x, SDL_MapRGB(img->format, r, g, b));
    }
  }
  for (x = 0; x < (unsigned) img->h; x++)
  {
    for (y = 0; y < (unsigned) img->w; y++)
    {
      SDL_GetRGB(getpixel(img, y, x), img->format, &r, &g, &b);
      med = (b - min) * 255 / (max - min);
      putpixel(img, y, x, SDL_MapRGB(img->format, med, med ,med));
    }
  }
}



void integrale(SDL_Surface *img, unsigned long integ[img->h][img->w])
{
  grey(img);
  unsigned w, h;
  for (h = 0; h < (unsigned) img->h; h++)
  {
    for (w = 0; w < (unsigned) img->w; w++)
    {
      integ[h][w] = getpixel(img, w, h);
      if(w)
        integ[h][w] += integ[h][w-1];
      if(h)
        integ[h][w] += integ[h-1][w];
    }
  }

}
