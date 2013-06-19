#include "map_entity_factory.h"
#include "..\..\Engine\debug.h"

namespace Map_Entities {

 Map_Entity_Factory::Map_Entity_Factory(Loader* l): loader(l) {};

Map_Entity* Map_Entity_Factory::build(ifstream& s, vector< vector<Map_Entity*> >& o, vector< vector<bool> >& v) {
  int type, x, y;
  s >> type >> x >> y;
  Map_Entity* e = building(type, x, y, s, v);
  if(e!=0) {
   if(o[x][y]!=0) {
#ifdef DBG_PRINT_WARNINGS
    cout << "[warning] Map_Entity_Factory::build() - rewriting building at (" << x << ", " << y << ")\n";
#endif
    delete (o[x][y]);
   }
   o[x][y]=e;
  }
  return e;
 }

 Map_Entity* Map_Entity_Factory::building(int type, int x, int y, ifstream& s, vector< vector<bool> >& v) {
  switch(type) {
   case 1: return build_1(x, y, s, v); break;
   case 2: return build_2(x, y, s, v); break;
   case 3: return build_3(x, y, s, v); break;
  }
  return 0;
 }

 void Map_Entity_Factory::set_obstacle(int x, int y, vector< vector<bool> >& v) {
  if(x<0||x>=(int)v.size()||y<0||y>=(int)v[x].size()) return;
  v[x][y] = true;
 }

 Map_Entity* Map_Entity_Factory::build_1(int x, int y, ifstream& s, vector< vector<bool> >& v) {
  string m = read_string(s);
  if(m.length()&&m[0]=='@') m = String_Table::translate[m.substr(1,m.length()-1)];
  Sign* building = new Sign(loader->load_sprite("res\\img\\map\\sign\\sign.sprite"), m);
  return building;
 }

 Map_Entity* Map_Entity_Factory::build_2(int x, int y, ifstream& s, vector< vector<bool> >& v) {
  set_obstacle(x-1,y,v);
  set_obstacle(x+1,y,v);
  set_obstacle(x,y-1,v);
  int sid, tx, ty;
  s >> sid >> tx >> ty;
  Portal* building = new Portal(loader->load_sprite("res\\img\\map\\portal\\portal.sprite"), sid, tx, ty);
  return building;
 }

 Map_Entity* Map_Entity_Factory::build_3(int x, int y, ifstream& s, vector< vector<bool> >& v) {
  int n;
  s >> n;
  string fl = "res\\img\\map\\obstacles\\";
  if(0<=n&&n<=16) {
   fl+="trees\\pines\\";
   n+=1;
   switch(n) {
    case 1: case 2: case 9: case 10: case 11: set_obstacle(x,y,v); break;
    case 3: case 4: case 12: case 13: set_obstacle(x,y,v); set_obstacle(x+1,y,v); set_obstacle(x+1,y-1,v); set_obstacle(x+2,y-1,v); break;
    case 5: case 6: case 14: case 15: set_obstacle(x,y,v); set_obstacle(x-1,y,v); set_obstacle(x-1,y-1,v); set_obstacle(x-2,y-1,v); break;
    case 7: case 16: set_obstacle(x-1,y-1,v); set_obstacle(x-2,y-1,v); set_obstacle(x,y,v); set_obstacle(x-1,y,v); set_obstacle(x-2,y,v); set_obstacle(x,y+1,v); set_obstacle(x-1,y+1,v); break;
    case 8: case 17: set_obstacle(x+1,y-1,v); set_obstacle(x+2,y-1,v); set_obstacle(x,y,v); set_obstacle(x+1,y,v); set_obstacle(x+2,y,v); set_obstacle(x,y+1,v); set_obstacle(x+1,y+1,v); break;
   }
  } else return 0;

  char buf[10]; itoa(n, buf, 10);
  fl+=buf; fl+=".sprite";
  return new Obstacle(loader->load_sprite(fl));
 }

}

