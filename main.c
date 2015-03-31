#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>
#include<SDL_image.h>
#include"image.c"
#include"SDL_affichage.h"

int main(int argc, char *argv[])
{
  if(argc == 2)
  {
    char *path = argv[1]; 
    init_sdl();  
    SDL_Surface *img = load_image(path);
    display_image(img);
    unsigned long integ[img->h][img->w];
    integrale(img, integ);
    display_image(img);
    return 0; 
   }
}
