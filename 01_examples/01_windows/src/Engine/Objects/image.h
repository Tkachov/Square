#ifndef IMAGE_H
#define IMAGE_H

#include "object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace Engine { namespace Objects {

class Image: public Object
{
 GLuint* image;
 SDL_Surface* bitmap;
 int _w, _h; //size of IMAGE (any positive int)
 int tw, th; //size of TEXTURE (only powers of 2)
 bool eat_click;

 public:
  Image(GLuint*,SDL_Surface*,int,int,int,int,int = 0,int = 0,int = 0);
  virtual ~Image() {};

  void draw(int, int);
  void update(Input*, int = 0, int = 0);

  GLuint* const img() { return image; };
  SDL_Surface* const bmp() { return bitmap; };
  bool is_intersected(int mx, int my);

  bool eating_clicks() { return eat_click; }
  int w() { return _w; }
  int h() { return _h; }
  int pw() { return tw; }
  int ph() { return th; }

  void set_eating_clicks(bool e) { eat_click = e; }
  void set_img(GLuint* s) { image = s; }
  void set_bmp(SDL_Surface* s) { bitmap = s; }
};

} }

#endif // IMAGE_H
