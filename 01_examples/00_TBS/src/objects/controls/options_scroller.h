#ifndef OPTIONS_SCROLLER_H
#define OPTIONS_SCROLLER_H

#include "..\..\Engine\Objects\object.h"
#include "..\..\Engine\Objects\button.h"
#include "..\..\Engine\Objects\text.h"
#include "..\..\Engine\functor.h"
#include "..\..\Engine\loader.h"
#include "..\..\Engine\input.h"
#include <string>
#include <vector>
#include <map>
using namespace Engine;
using namespace Engine::Objects;
using std::string;
using std::vector;
using std::map;

class Options_Scroller: public Object
{
 private:
  int distance;
  Button* left;
  Button* right;
  Text* label;
  map<string, string> options;
  vector<string> olist;
  int current;

  friend class Functor<Options_Scroller>;
  void fnc_scroll_left();
  void fnc_scroll_right();

  void update_label();

 public:
  Options_Scroller(Loader* l, int distance, int x = 0, int y = 0, int pr = 0);
  virtual ~Options_Scroller();

  virtual void draw(SDL_Surface*);
  virtual void update(Input*);

  void push(string key, string value) {
   olist.push_back(key);
   options[key]=value;
   if(olist.size()==1) update_label();
  }
  void select(int n) { if(n>-1&&n<int(olist.size())) current = n; update_label(); }

  string selected() { return olist[current]; }
  string curvalue() { return options[olist[current]]; }
};

#endif // OPTIONS_SCROLLER_H
