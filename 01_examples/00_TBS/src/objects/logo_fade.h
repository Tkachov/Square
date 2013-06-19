#ifndef LOGO_FADE_H
#define LOGO_FADE_H

#include "..\Engine\Objects\object.h"
#include "..\Engine\Objects\image.h"
#include "..\Engine\Objects\fade_effect.h"
#include "..\Engine\Objects\timer.h"
#include "..\Engine\screen.h"
#include "..\Engine\functor.h"
using namespace Engine;

class Logo_Fade: public Object, public Screen
{
 private:
  int fadephase;
  virtual void load();

  friend class Functor<Logo_Fade>;
  void fnc_phase1_delay();
  void fnc_phase2_fade_out();
  void fnc_phase3_destruct();

 public:
  Logo_Fade(Game* gm, Loader* ld, int sx = 0, int sy = 0, int pr = 0);
  virtual ~Logo_Fade();

  virtual void update() {};
  virtual void redraw() {};
  virtual void update(Input*);
  virtual void draw(SDL_Surface*);
};

#endif // LOGO_FADE_H
