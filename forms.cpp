#include "forms.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#define COST_TEXTBOX_CHARS 20
#define COST_BUTTON_CHARS 14

button::button() {
  wasClicked = false;
  wasPressed = false;
}

void button::init(SDL_Renderer *new_renderer, int new_x, int new_y, int new_w,
                  int new_h, bool new_fill, SDL_Color new_background_color,
                  std::string new_text, TTF_Font *new_font,
                  SDL_Color new_text_color, bool new_center) {
  x = new_x;
  y = new_y;
  w = new_w;
  h = new_h;
  fill = new_fill;
  background_color = new_background_color;
  text = new_text;
  font = new_font;
  text_color = new_text_color;
  renderer = new_renderer;
  center = new_center;
  max_chars = w / COST_BUTTON_CHARS;
}

void button::draw() {
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g,
                         background_color.b, background_color.a);

  // Disegno il pulsante
  fill == false ? SDL_RenderDrawRect(renderer, &rect)
                : SDL_RenderFillRect(renderer, &rect);

  // Scrivo dentro il testo
  SDL_Surface *text_surface =
      TTF_RenderText_Blended(font, text.c_str(), text_color);
  SDL_Texture *text_texture =
      SDL_CreateTextureFromSurface(renderer, text_surface);
  SDL_Rect text_rect;
  text_rect.w = (strlen(text.c_str()) * w) / max_chars;
  text_rect.h = h / 2;
  if (center == false)
    text_rect.x = x + w / max_chars;
  else
    text_rect.x = x + ((x + w) - (text_rect.w + x)) / 2;
  text_rect.y = y + ((y + h) - (text_rect.h + y)) / 2;
  SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
  SDL_FreeSurface(text_surface);
  SDL_DestroyTexture(text_texture);
}

bool button::isClicked() {
  int mousex, mousey;
  SDL_PumpEvents();
  if (SDL_GetMouseState(&mousex, &mousey) && SDL_BUTTON(SDL_BUTTON_LEFT))
    if (mousex >= x && mousex <= x + w)
      if (mousey >= y && mousey <= y + h)
        return 1;
  return 0;
}

bool button::onRelease() {
  if (isClicked()) {
    wasPressed = true;
    return 0;
  } else if (wasPressed == true) { // Ma ora non lo è più
    wasPressed = false;
    return 1;
  }
  return 0;
}

bool button::onClick() {
  if (isClicked()) {
    if (wasClicked == true) // Era già cliccato
      return 0;
    else {
      wasClicked = true;
      return 1;
    }
  }
  wasClicked = false;
  return 0;
}

textbox::textbox() { text = ""; }

void textbox::init(SDL_Renderer *new_renderer, int new_x, int new_y, int new_w,
                   int new_h, bool new_fill, SDL_Color new_background_color,
                   std::string new_text, TTF_Font *new_font,
                   SDL_Color new_text_color, bool new_center) {
  x = new_x;
  y = new_y;
  w = new_w;
  h = new_h;
  fill = new_fill;
  background_color = new_background_color;
  text = new_text;
  font = new_font;
  text_color = new_text_color;
  renderer = new_renderer;
  center = new_center;
  max_chars = w / COST_TEXTBOX_CHARS;
}

void textbox::draw() {
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g,
                         background_color.b, background_color.a);

  // Disegno la casella di testo
  fill == false ? SDL_RenderDrawRect(renderer, &rect)
                : SDL_RenderFillRect(renderer, &rect);

  // Scrivo dentro il testo
  SDL_Surface *text_surface =
      TTF_RenderText_Blended(font, text.c_str(), text_color);
  SDL_Texture *text_texture =
      SDL_CreateTextureFromSurface(renderer, text_surface);
  SDL_Rect text_rect;
  text_rect.w = (strlen(text.c_str()) * (w * 14) / 15) / max_chars;
  text_rect.h = h * 3 / 4;
  if (center == false)
    text_rect.x = x + w / max_chars;
  else
    text_rect.x = x + ((x + w) - (text_rect.w + x)) / 2;
  text_rect.y = y + ((y + h) - (text_rect.h + y)) / 2;
  SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
  SDL_FreeSurface(text_surface);
  SDL_DestroyTexture(text_texture);
}

void textbox::write(SDL_Event event) {
  if (isSelected()) {
    if (((event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) ||
         event.key.keysym.sym == SDLK_SPACE) &&
        (int)strlen(text.c_str()) < max_chars - 1)
      text = text + (char)event.key.keysym.sym;
    else if (event.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
      text.erase(text.end() - 1);
  }
}

bool textbox::isSelected() {
  int mousex, mousey;
  SDL_PumpEvents();
  SDL_GetMouseState(&mousex, &mousey);
  if (mousex >= x && mousex <= x + w)
    if (mousey >= y && mousey <= y + h)
      return 1;
  return 0;
}
