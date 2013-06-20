#ifndef WINDOW_H
#define WINDOW_H

#include "object.h"
#include "..\screen.h"
#include "button.h"
#include "image.h"
using namespace Engine;
using namespace Engine::Objects;

namespace Engine { namespace Objects {

class Window: public Object, public Screen
{
 protected:
  virtual void load();
  virtual void disappear();

 public:
  Window(Game*, Loader*, int, int, int pr = 0);
  virtual ~Window();

  virtual void update();
  virtual void redraw() {};
  virtual void update(Input*);
  virtual void draw(int, int);
};

} }

#endif // WINDOW_H
