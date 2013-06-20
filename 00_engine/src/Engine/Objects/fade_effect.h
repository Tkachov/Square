#ifndef FADE_EFFECT_H
#define FADE_EFFECT_H

#include "object.h"
#include "sprite.h"
#include "..\functor.h"
#include "..\utils.h"

namespace Engine { namespace Objects {

enum Fade_Mode {
 m_FADE_IN, //0->255 transparency transition
 m_FADE_OUT, //255->0 transparency transition
 m_IMAGE_IN, //same, but for image
 m_IMAGE_OUT //same
};

class Fade_Effect: public Object
{
 private:
  Fade_Mode mode;
  functor* func;
  int counter;
  int limit;

  //color mode
  int r,g,b,w,h;
  //image mode
  Sprite img;

 public:
  Fade_Effect(Fade_Mode, int delay, functor* = 0, int sx = 0, int sy = 0, int pr = 0);
  virtual ~Fade_Effect();

  virtual void update(Input*);
  virtual void draw(int, int);

  void color_mode(int r, int g, int b, int w, int h);
  void image_mode();

  Sprite* spr() { return &img; }
};

} }

#endif // FADE_EFFECT_H
