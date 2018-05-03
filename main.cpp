#include "forms.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#define MAXX 1000 // Le misure della finestra
#define MAXY 175
int chiudiSDL();
void eventi();
void draw();
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Color green = {0, 255, 0, 255};
SDL_Color white = {255, 255, 255, 255};
SDL_Color red = {255, 0, 0, 255};
SDL_Color blue = {0, 0, 255, 255};
SDL_Color magic = {51, 51, 51, 51};
SDL_Color black = {0, 0, 0, 255};

button Button;
textbox Box;

int main() {
  SDL_Init(0);
  TTF_Init();
  window =
      SDL_CreateWindow("SDL Form", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, MAXX, MAXY, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(renderer, magic.r, magic.g, magic.b, magic.a);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  // CODICE QUI
  TTF_Font *font = TTF_OpenFont("SourceSansPro-Semibold.ttf", 70);
  if (!font)
    printf("Font non aperto\n");
  Box.init(renderer, 1, 1, MAXX - 2, 100, true, white, "", font, black, true);
  Button.init(renderer, (MAXX - 100) / 2, 110, 100, 50, false, red, "Stampa",
              font, black, true);
  // CODICE QUI
  while (1) {
    SDL_SetRenderDrawColor(renderer, magic.r, magic.g, magic.b, magic.a);
    SDL_RenderClear(renderer);
    eventi();
    draw();
    SDL_Delay(10);
  }
  return chiudiSDL();
}

void eventi() {
  SDL_Event event;
  SDL_PollEvent(&event);
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_ESCAPE)
      chiudiSDL();
    else
      Box.write(event);
  }
  if (Button.onClick())
    printf("Testo: %s\n", Box.text.c_str());
}

void draw() {
  Box.draw();
  Button.draw();
  SDL_RenderPresent(renderer);
}

int chiudiSDL() {
  printf("Chiusura in corso...\n");
  TTF_Quit();
  SDL_DestroyWindow(window);
  SDL_Quit();
  exit(0);
}
