#ifndef SCREEN_H
#define SCREEN_H

#include <fstream>
#include "Entity.h"
#include "../Global/ScreenID.h"
using std::ifstream;
using std::ofstream;
using Engine::Global::ScreenID;

namespace Engine { namespace Entities {

class Screen: public Entity {
 protected:
  bool _static;

  virtual void update_after_queue(int x, int y);

 public:
  static const ScreenID _id = Global::s_UNKNOWN_ID;

  Screen(Controller* controller);

  void start();

  virtual void save_state(ofstream& fout);
  virtual void load_state(ifstream& fin);

  virtual ScreenID id() { return _id; }
  bool is_static() { return _static; }
};

} }

#endif //SCREEN_H
