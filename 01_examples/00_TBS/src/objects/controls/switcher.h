#ifndef SWITCHER_H
#define SWITCHER_H

#include <SDL.h>
#include "..\..\Engine\Objects\object.h"
#include "..\..\Engine\Objects\sprite.h"
#include "..\..\Engine\Objects\text.h"
#include "..\..\Engine\input.h"
#include <string>
using namespace Engine;
using namespace Engine::Objects;
using std::string;

class Switcher: public Object
{
 private:
  Text* label;
  string t_true;
  string t_false;
  bool current;
  Sprite state[4];
  SDL_Color color[4];
  int current_state;
  bool disabled;

 public:
  Switcher(Text* txt, string v1, string v2, bool first = true, int x = 0, int y = 0, int pr = 0);
  virtual ~Switcher();

  virtual void draw(SDL_Surface*);
  virtual void update(Input*);

  void set_color(int n, SDL_Color& c) { if(n>-1 && n<3) color[n]=c; }
  void set_icon(Sprite s1, Sprite s2, Sprite s3, Sprite s4) {
   state[0] = s1;
   state[1] = s2;
   state[2] = s3;
   state[3] = s4;
  }

  bool selected() { return current; }
  bool is_disabled() { return disabled; }

  void set_disabled(bool d) { disabled = d; }
};

#endif // SWITCHER_H
