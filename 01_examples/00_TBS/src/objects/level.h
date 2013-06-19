#ifndef LEVEL_H
#define LEVEL_H

#include "..\Engine\Objects\object.h"
#include "..\Engine\Objects\sprite.h"
namespace Engine { namespace Objects { class Map_Entity; class Window; } };
namespace Map_Entities {};
#include "map_entities\map_entity_factory.h"
#include "..\Engine\Objects\window.h"
#include "..\Engine\screen.h"
#include "..\Engine\utils.h"
#include <algorithm>
#include <fstream>
#include <vector>
#include <stack>
using namespace Engine;
using namespace Engine::Objects;
using namespace Map_Entities;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::stack;

class Level: public Object, public Screen
{
 private:
  Screen* screen;
  vector< vector<int> > tiles;
  Image* tileset;
  int tw, th, w, h; //size of map (tile- / pixel-based)
  int vx, vy, vw, vh; //currenly drawn area
  bool view_following;
  static const int vspd = 2; //view
  static const int hspd = 2; //hero

  vector< vector<Map_Entity*> > entities; //map objects like buildings, trees, enemies, treasures, etc
  map<int, Map_Entity*> entities_by_id; //to save, load or change it's states
  vector<Sprite> hero;
  int hero_direction;
  int hsx, hsy; //hero's screen position (at %hero% is storaged tile-based position)

  vector< vector<bool> > obstacles; //true if there is obstacle and false if there is not
  int tx, ty; //hero's target position (where he's going)
  stack<int> path;
  Image* path_cell;
  Image* path_next;
  Image* path_trgt;

  void move_target(int, int);
  void A_star();
  void draw_entity(int, int, SDL_Surface*);
  void draw_path_cell(int, int, int, SDL_Surface*);
  Map_Entity* entity(int);
  void delete_entity(int);

 protected:
  virtual void load();

 public:
  Level(const char* filename, Game* gm, Loader* ld, Screen* sc, int pr = 0);
  virtual ~Level();

  virtual void update() {};
  virtual void redraw() {};
  virtual void update(Input*);
  virtual void draw(SDL_Surface*);
  virtual void save_state(ofstream&);
  virtual void load_state(ifstream&);

  void show_message(Window*);

  //getters
  Game* get_game() { return game; }
  Loader* get_loader() { return loader; }

  //setters
  void replace_hero(int x, int y, bool do_activities = true);
};

#endif // LEVEL_H
