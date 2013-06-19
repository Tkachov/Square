#ifndef EDIT_H
#define EDIT_H

#include "..\..\Engine\Objects\button.h"
#include "..\..\Engine\functor.h"
#include "..\..\Engine\loader.h"
using namespace Engine;
using namespace Engine::Objects;

class Edit: public Button
{
 private:
  int width;
  int height;
  Text* txt;
  bool selected;
  int frame;
  int delay;
  functor* checker;

  void check_keys(Input*);

 public:
  Edit(Text*, functor*, Loader*, int, int, int w, int pr = 0);
  virtual ~Edit();

  virtual void update(Input*);
  virtual void draw(SDL_Surface*);

  void set_checker(functor* f) {checker = f;}

  bool is_selected() {return selected;}
};

#endif // EDIT_H
