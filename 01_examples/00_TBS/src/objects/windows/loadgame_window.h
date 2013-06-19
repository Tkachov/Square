#ifndef LOADGAME_WINDOW_H
#define LOADGAME_WINDOW_H

#include "..\..\Engine\Objects\window.h"
#include "..\..\Engine\Objects\text.h"
#include "..\..\Engine\functor.h"
#include "..\buttons\blue_button.h"
#include "..\buttons\savegame_button.h"
#include "..\controls\edit.h"
#include <string>
using namespace Engine;
using namespace Engine::Data;
using namespace Engine::Objects;
using std::string;

class LoadGame_Window: public Window
{
 private:
  class slot {
   public:
    slot(long long unsigned int t, SaveGame_Button* o): modtime(t), button(o) {};
    long long unsigned int modtime;
    SaveGame_Button* button;
    bool operator<(const slot& other) const { return (modtime > other.modtime || (modtime==other.modtime && button->slotname < other.button->slotname)); }
  };

  typedef vector<slot> slotlist;

  bool loading_window;
  Blue_Button* bt_delete;
  Blue_Button* bt_load;
  Blue_Button* bt_save;
  Blue_Button* bt_cancel;
  Button* bt_scroll_up;
  Button* bt_scroll_dn;
  Text* tx_savename;
  Text* tx_savedate;
  Edit* ed_savename;
  map<string, SaveGame_Button*> saves;
  slotlist slots;
  int mvup_delay;
  int mvdn_delay;

  friend class Functor<LoadGame_Window>;
  void fnc_delete();
  void fnc_load();
  void fnc_save();
  void fnc_complete_save();
  void fnc_cancel();
  void fnc_move_up();
  void fnc_move_dn();
  void fnc_selection();
  void fnc_runchosen();
  void fnc_scroll_up();
  void fnc_scroll_dn();
  void fnc_update_name();

  string loc_name(int);
  bool valid_ASCII(char);
  bool key_hold_or_pressed(int,int);
  bool select_slot(string); //true if selected, false if failed
  int px;
  int py;
  int pw;
  int ph;
  void labels_update();

 protected:
  virtual void load();

 public:
  LoadGame_Window(bool, Game* g, Loader* l, int pr = 0);
  virtual ~LoadGame_Window();

  virtual void update();
  virtual void update(Input*);
};

#endif // LOADGAME_WINDOW_H
