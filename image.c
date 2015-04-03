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

void wait_for_keypressed(void) {
    SDL_Event             event;
      for (;;) {
        SDL_PollEvent( &event );
        switch (event.type) {
          case SDL_KEYDOWN: return; 
          default: break;
        }
      }
}

void init_sdl(void) {
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
}

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  img = IMG_Load(path);
  if (!img)
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    errx(1, "Couldn't set %dx%d video mode: %s\n",
        img->w, img->h, SDL_GetError());
      }
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
  wait_for_keypressed();
  return screen;
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

// convertie une image en image integrale normalisée et remplie un tableau de la dimension de l image avec les valeurs integrales

void integrale(SDL_Surface *img, unsigned long integ[img->h][img->w])
{
  Uint8 r, g, b, med, max = 0;
  Uint8 min = 255;
  unsigned x,y;
  display_image(img);
  // put picture in grey level and get min and max values
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
  display_image(img);
  // normalization of the picture depending on min and max
  for (x = 0; x < (unsigned) img->h; x++)
  {
    for (y = 0; y < (unsigned) img->w; y++)
    {
      SDL_GetRGB(getpixel(img, y, x), img->format, &r, &g, &b);
      med = (b - min) * 255 / (max - min);
      integ[x][y] = med;
      putpixel(img, y, x, SDL_MapRGB(img->format, med, med ,med));
      if(y)
        integ[x][y] += integ[x][y-1];
      if(x)
        integ[x][y] += integ[x-1][y];
    }
  }
  display_image(img);
}  
