#ifndef MESSAGE_H
#define MESSAGE_H

#include "..\..\Engine\Objects\window.h"
#include "..\..\Engine\Objects\text.h"
#include "..\..\Engine\functor.h"
#include "..\buttons\blue_button.h"
#include <string>
using namespace Engine;
using namespace Engine::Objects;
using std::string;

class Message: public Window
{
 public:
  enum Design {
   MSG_NORMAL,
   MSG_SMALL
  };

 private:
  string message;
  functor* yep;
  functor* nope;

  friend class Functor<Message>;
  void fnc_yes();
  void fnc_no();

 public:
  Message(Design type, Game* g, Loader* l, string msg, functor* yes, functor* no, int pr = 0);
  virtual ~Message();

  virtual void update();
  virtual void update(Input*);
};

#endif // MESSAGE_H
