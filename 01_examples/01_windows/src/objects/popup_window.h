#ifndef POPUP_WINDOW_H
#define POPUP_WINDOW_H

#include "..\Engine\Objects\window.h"
using namespace Engine::Objects;

class Popup_Window: public Window
{
 private:
  int offset_x, offset_y;
  bool follow;

  friend class Functor<Popup_Window>;
  void fnc_close();

  void update(int, int);

 public:
  Popup_Window(Game*, Loader*, int x = 0, int y = 0, int pr = 0);
  virtual ~Popup_Window();

  virtual void update(Input*, int = 0, int = 0);
  virtual void update();
};

#endif // POPUP_WINDOW_H
