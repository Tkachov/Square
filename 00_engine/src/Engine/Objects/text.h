#ifndef TEXT_H
#define TEXT_H

#include "object.h"
#include "image.h"
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include "..\utils.h"
using std::vector;
using std::string;

namespace Engine { namespace Objects {

class Text: public Object
{
private:
 TTF_Font* _font;
 string _text;
 SDL_Color _color;
 Image* _image;
 bool _antialiased;
 int _width;

 void redraw();
 void free_surface();
 void clone(const Text&);
 SDL_Surface* draw_text(string);
 SDL_Surface* draw_text(string, TTF_Font*, SDL_Color, bool aa = true);

public:
 Text(TTF_Font* fnt, string txt = "", int wdth = 0, SDL_Color c = SDL_Color(), int x = 0, int y = 0, int pr = 0);
 Text(const Text&); //copy constructor
 Text& operator=(const Text&); //assignment
 virtual ~Text();

 virtual void update(Input*, int = 0, int = 0) {};
 virtual void draw(int, int);

 string const text() { return _text; }
 Image* const img() { return _image; };
 int const width() { return _width; }

 void set_font(TTF_Font*);
 void set_text(string);
 void set_color(SDL_Color&);
 void set_antialias(bool);
 void set_width(int);
};

} }

#endif // TEXT_H
