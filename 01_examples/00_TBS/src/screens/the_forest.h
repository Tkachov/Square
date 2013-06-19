#ifndef THE_FOREST_H
#define THE_FOREST_H

#include "..\Engine\screen.h"
#include "..\Engine\Objects\button.h"
#include "..\objects\logo_fade.h"
#include "..\objects\level.h"
#include "..\objects\pause_menu.h"
#include "..\objects\buttons\blue_button.h"
using namespace Engine;
using namespace Engine::Data;

class The_Forest: public Screen
{
 private:
  bool __first_visit;
  Level* level;
  Pause_Menu* pause_menu;

  friend class Functor<The_Forest>;
  void fnc_menu();

 protected:
  virtual void load();

 public:
  The_Forest(Game* game, SDL_Surface* surf, Loader* ld, Input* in);
  virtual ~The_Forest();

  virtual void start();
  virtual void update();
  virtual void save_state(ofstream&);
  virtual void load_state(ifstream&);

  virtual ScreenID ID() { return s_THE_FOREST; }
};

#endif // THE_FOREST_H
