#ifndef BLUE_BUTTON_H
#define BLUE_BUTTON_H

#include <SDL.h>
#include "..\..\Engine\Objects\button.h"
#include "..\..\Engine\functor.h"
#include "..\..\Engine\loader.h"
#include "..\..\Engine\input.h"
#include "..\..\Engine\utils.h"
using namespace Engine;
using namespace Engine::Objects;

class Blue_Button: public Button
{
 private:
  int _width;
  SDL_Surface* surf;
  Image* surf_img;

  void redraw();
  void update_label();

 public:
  Blue_Button(string text, functor*, Loader*, int x, int y, int wd = 0, int pr = 0);
  virtual ~Blue_Button();

  virtual void draw(SDL_Surface*);
  virtual void update(Input*);
};

#endif // BLUE_BUTTON_H
