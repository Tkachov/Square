#ifndef TEXT_MESSAGE_H
#define TEXT_MESSAGE_H

#include "..\..\Engine\Objects\window.h"
#include "..\..\Engine\Objects\text.h"
#include "..\..\Engine\functor.h"
#include "..\buttons\blue_button.h"
#include <string>
using namespace Engine;
using namespace Engine::Objects;
using std::string;

class Text_Message: public Window
{
 private:
  string message;

 protected:
  virtual void load();

  friend class Functor<Text_Message>;
  void fnc_OK();
  Image* newImage(string s, int x, int y, int pr =0);

 public:
  Text_Message(string, Game*, Loader*, int = 0);
  virtual ~Text_Message();

  virtual void update();
  virtual void update(Input*);
};

#endif // TEXT_MESSAGE_H
