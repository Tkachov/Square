#ifndef POPUP_WINDOW_H
#define POPUP_WINDOW_H

#include "../Engine/Entities/Window.h"
#include "../Engine/Functor.h"

namespace Engine {
 class Controller;
}

using Engine::Entities::Window;
using Engine::Controller;
using Engine::Functor;

class Popup_Window: public Window
{
 private:
  int offset_x, offset_y;
  bool follow;

  friend class Functor<Popup_Window>;
  void fnc_close();

 public:
  Popup_Window(Controller*, int x = 0, int y = 0, int pr = 0);
  virtual ~Popup_Window();

  virtual void update_after_queue(int, int);
};

#endif // POPUP_WINDOW_H
