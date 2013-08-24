#ifndef FADE_H
#define FADE_H

#include "Entity.h"
#include "Sprite.h"
#include "..\Functor.h"
#include "..\utils.h"

namespace Engine { namespace Entities {

enum Fade_Mode {
 m_FADE_IN, //0->255 transparency transition
 m_FADE_OUT //255->0 transparency transition
};

class Fade: public Entity
{
 private:
  Fade_Mode mode;
  functor* func;
  int counter, limit;
  bool show_color;

  //color mode
  SDL_Color color;
  int width, height;

  //image mode
  Sprite* image;

 public:
  Fade(Controller* controller, Fade_Mode mode, int length, SDL_Color color, int width, int height, functor* f = 0, int x = 0, int y = 0, int priority = 0);
  Fade(Controller* controller, Fade_Mode mode, int length, Sprite* image, functor* f = 0, int x = 0, int y = 0, int priority = 0);
  virtual ~Fade();

  virtual void update(int x, int y);
  virtual void redraw(int x, int y);
};

} }

#endif // FADE_H
