#ifndef __FORMS_H__
#define __FORMS_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class button {
public:
  int x, y, w, h;
  int max_chars;
  bool fill, center;
  bool wasClicked; // Per onClick
  bool wasPressed; // Per onRelease
  std::string text;
  TTF_Font *font;
  SDL_Color background_color;
  SDL_Color text_color;
  SDL_Renderer *renderer;
  button();
  void init(SDL_Renderer *new_renderer, int new_x, int new_y, int new_w,
            int new_h, bool new_fill, SDL_Color new_background_color,
            std::string new_text, TTF_Font *new_font, SDL_Color new_text_color,
            bool new_center);
  void draw();
  bool isClicked();
  bool onRelease();
  bool onClick();
};

class textbox {
public:
  int x, y, w, h;
  int max_chars;
  bool fill, center;
  std::string text;
  TTF_Font *font;
  SDL_Color background_color;
  SDL_Color text_color;
  SDL_Renderer *renderer;
  textbox();
  void init(SDL_Renderer *new_renderer, int new_x, int new_y, int new_w,
            int new_h, bool new_fill, SDL_Color new_background_color,
            std::string new_text, TTF_Font *new_font, SDL_Color new_text_color,
            bool new_center);
  void draw();
  void write(SDL_Event event);
  bool isSelected();
};

#endif
