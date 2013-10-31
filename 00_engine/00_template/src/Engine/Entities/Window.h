#ifndef WINDOW_H
#define WINDOW_H

#include "Entity.h"

namespace Engine { namespace Entities {

class Window: public Entity {
 private:
  bool _modal;

 public:
  Window(Controller* controller, int x, int y, bool modal = false);
  virtual ~Window();

  void update(int x, int y);

  bool modal() { return _modal; }
};

} }

#endif // WINDOW_H
