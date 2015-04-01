#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL/SDL.h>
#include"image.c"
#include"haar.c"

int main(int argc, char *argv[])
{
  if(argc == 2)
  {
    char *path = argv[1]; 
    init_sdl();  
    SDL_Surface *img = load_image(path);
    unsigned long integ[img->h][img->w];
    integrale(img, integ);
    return 0; 
   }
}
