#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Entity.h"
using std::string;

namespace Engine { namespace Data { class Frame; } }
using Engine::Data::Frame;

namespace Engine { namespace Entities {

class Text: public Entity
{
 private:
  bool _antialiasing;
  SDL_Color _color;
  TTF_Font* _font;
  Frame* _label;
  string _text;
  unsigned int _width;

  void clone(const Text&);
  SDL_Surface* draw_text(string);
  SDL_Surface* draw_text(string, TTF_Font*, SDL_Color, bool aa = true);
  void free_surface();
  void refresh();

 public:
  Text(
   Controller* controller,
   TTF_Font* font = 0, string text = "", unsigned int width = 0, SDL_Color* color = 0,
   int x = 0, int y = 0, int priority = 0
  );
  Text(const Text&); //copy constructor
  Text& operator=(const Text&); //assignment
  virtual ~Text();

  virtual void update(int x, int y) {};
  virtual void redraw(int x, int y);

  bool antialiasing() { return _antialiasing; }
  SDL_Color color() { return _color; }
  TTF_Font* const font() { return _font; }
  Frame* const label() { return _label; }
  string const text() { return _text; }
  unsigned int const width() { return _width; }

  void set_antialiasing(bool);
  void set_color(SDL_Color&);
  void set_font(TTF_Font*);
  void set_text(string);
  void set_width(unsigned int);

};

} }

#endif // TEXT_H
