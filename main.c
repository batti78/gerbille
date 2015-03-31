#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>
#include<SDL_image.h>
#include"image.c"

int main(int argc, char *argv[])
{
  if(argc == 2)
  {
    char *path = argv[1]; 
    init_sdl();  
    SDL_Surface *img = load_image(path);
    unsigned long integ[img->w][img->h];
    integrale(img, integ);
    return 0; 
                                        }
}
