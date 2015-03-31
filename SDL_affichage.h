# include <SDL/SDL.h>
# include <SDL.h>

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
