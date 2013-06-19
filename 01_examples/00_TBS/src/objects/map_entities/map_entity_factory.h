#ifndef MAP_ENTITY_FACTORY_H
#define MAP_ENTITY_FACTORY_H

#include "..\..\Engine\loader.h"
#include "..\..\Engine\utils.h"
#include "..\..\Engine\Objects\map_entity.h"
#include "sign.h" //#1
#include "portal.h" //#2
#include "obstacle.h" //#3
#include <fstream>
#include <vector>
using namespace Engine;
using namespace Engine::Objects;
using std::ifstream;
using std::vector;

namespace Map_Entities {

 class Map_Entity_Factory
 {
  private:
   Loader* loader;

   void set_obstacle(int, int, vector< vector<bool> >&);
   Map_Entity* build_1(int, int, ifstream&, vector< vector<bool> >&); //sign
   Map_Entity* build_2(int, int, ifstream&, vector< vector<bool> >&); //portal
   Map_Entity* build_3(int, int, ifstream&, vector< vector<bool> >&); //obstacle
   Map_Entity* building(int, int, int, ifstream&, vector< vector<bool> >&);

  public:
   Map_Entity_Factory(Loader*);
   Map_Entity* build(ifstream&, vector< vector<Map_Entity*> >&, vector< vector<bool> >&);
 };

}

#endif // MAP_ENTITY_FACTORY_H
