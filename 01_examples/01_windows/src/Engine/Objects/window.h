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

  void update_queue(int = 0, int = 0);

 public:
  Window(Game*, Loader*, int, int, int pr = 0);
  virtual ~Window();

  virtual void update(int = 0, int = 0);
  virtual void redraw() {};
  virtual void update(Input*, int = 0, int = 0);
  virtual void draw(int, int);
};

} }

#endif // WINDOW_H
