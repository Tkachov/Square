#ifndef THE_DUNGEON_H
#define THE_DUNGEON_H

#include "..\Engine\screen.h"
#include "..\Engine\Objects\button.h"
#include "..\Engine\Objects\fade_effect.h"
#include "..\objects\level.h"
#include "..\objects\pause_menu.h"
#include "..\objects\buttons\blue_button.h"
using namespace Engine;
using namespace Engine::Data;

class The_Dungeon: public Screen
{
 private:
  Level* level;
  Pause_Menu* pause_menu;

  friend class Functor<The_Dungeon>;
  void fnc_menu();

 protected:
  virtual void load();

 public:
  The_Dungeon(Game* game, SDL_Surface* surf, Loader* ld, Input* in);
  virtual ~The_Dungeon();

  virtual void start();
  virtual void update();
  virtual void save_state(ofstream&);
  virtual void load_state(ifstream&);

  virtual ScreenID ID() { return s_THE_DUNGEON; }
};

#endif // THE_DUNGEON_H
