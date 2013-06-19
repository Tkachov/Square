#include "level.h"
#include "..\Engine\Objects\map_entity.h"
#include <iostream>
using std::cout;
using std::min;
using std::max;

Level::Level(const char* fn, Game* gm, Loader* ld, Screen* sc, int pr):
 Object(0,0, pr), Screen(gm, 0, ld, 0), screen(sc), vx(0), vy(0), vw(gm->w()), vh(gm->h()), view_following(true), hero_direction(7), path_cell(0) {
  load(); //prepare necessary images

  //open file & prepare arrays of tiles & objects
  ifstream mp(fn);
  mp.ignore(3,'\n');
  mp >> tw >> th;
  tiles.resize(tw);
  for(int i=0; i<tw; ++i) tiles[i].resize(th);
  entities.resize(tw);
  for(int i=0; i<tw; ++i) entities[i].resize(th);
  obstacles.resize(tw);
  for(int i=0; i<tw; ++i) obstacles[i].resize(th);
  //read tiles
  string ts;
  mp >> ts;
  tileset = loader->load_texture(string("res\\img\\tiles\\")+ts);
  vector<int> obstacle_tile_types;
  int ott;
  mp >> ott;
  obstacle_tile_types.resize(ott);
  for(int i=0;i<ott;++i) mp >> obstacle_tile_types[i];
  for(int j=0;j<th;++j)
   for(int i=0;i<tw;++i) {
    mp >> tiles[i][j];
    entities[i][j]=0;
    obstacles[i][j]=(find(obstacle_tile_types.begin(),obstacle_tile_types.end(),tiles[i][j])!=obstacle_tile_types.end());
   }
  w=tw*32; h=th*32;
  //read hero position
  mp >> hsx >> hsy;
  hero[hero_direction].set_x(hsx);
  hero[hero_direction].set_y(hsy);
  tx=hsx; ty=hsy;
  hsx*=32; hsy*=32;
  //read objects
  Map_Entity_Factory f(loader);
  int cnt;
  mp >> cnt;
  for(int i=0; i<cnt; ++i) entities_by_id[i] = f.build(mp, entities, obstacles);
  mp.close();
 };

Level::~Level() {
 for(int i=0; i<tw; ++i)
  for(int j=0; j<th; ++j) {
   Map_Entity* p = entities[i][j];
   if(p!=0) {
    delete p;
    entities[i][j] = 0;
   }
  }
};

void Level::load() {
 hero.push_back(loader->load_sprite("res\\img\\map\\hero\\up_left.sprite")); //0
 hero.push_back(loader->load_sprite("res\\img\\map\\hero\\up.sprite")); //1
 hero.push_back(loader->load_sprite("res\\img\\map\\hero\\up_right.sprite"));
 hero.push_back(loader->load_sprite("res\\img\\map\\hero\\left.sprite"));
 hero.push_back(Sprite()); //4
 hero.push_back(loader->load_sprite("res\\img\\map\\hero\\right.sprite"));
 hero.push_back(loader->load_sprite("res\\img\\map\\hero\\down_left.sprite"));
 hero.push_back(loader->load_sprite("res\\img\\map\\hero\\down.sprite"));
 hero.push_back(loader->load_sprite("res\\img\\map\\hero\\down_right.sprite"));
 path_cell = new Image(*loader->load_texture("res\\img\\map\\path\\cell.png"));
 path_next = new Image(*loader->load_texture("res\\img\\map\\path\\next.png"));
 path_trgt = new Image(*loader->load_texture("res\\img\\map\\path\\trgt.png"));
}

void Level::update(Input* i) {
 int view_bottom_border = h-vh-32;

 int hx, hy, ptx, pty;
 hx = hero[hero_direction].x();
 hy = hero[hero_direction].y();
 ptx = tx; pty = ty;

 input=i;
 if(i->paused()) return;
 for(int t=tw-1; t>=0; --t)
  for(int k=th-1; k>=0; --k) {
   Map_Entity* p = entities[t][k];
   if(p!=0 && p->enabled()) {
    p->update(t*32-vx, k*32-vy, input);
    if(p->clicked()) move_target(t, k);
   }
  }

 if(!i->paused()) {
  #ifdef DBG_MAP_CONTROL_VIEW
  if(path.empty()) {
   if((i->key_hold(SDLK_UP)||i->mouse_y()<16) && vy-vspd>=0) {vy-=vspd; view_following = false;}
   if((i->key_hold(SDLK_DOWN)||(i->mouse_y()>vh-16&&i->mouse_y()<=vh)) && vy+vspd<=view_bottom_border) {vy+=vspd; view_following = false;}
   if((i->key_hold(SDLK_LEFT)||i->mouse_x()<16) && vx-vspd>=0) {vx-=vspd; view_following = false;}
   if((i->key_hold(SDLK_RIGHT)||i->mouse_x()>vw-16) && vx+vw+vspd<=w) {vx+=vspd; view_following = false;}
  }
  #endif
  if(tx==ptx && ty==pty) {
   if(i->key_release(SDLK_w)) move_target(hx,hy-1);
   if(i->key_release(SDLK_s)) move_target(hx,hy+1);
   if(i->key_release(SDLK_a)) move_target(hx-1,hy);
   if(i->key_release(SDLK_d)) move_target(hx+1,hy);
  }
  if(i->mouse_release(1)) {
   move_target((vx+i->mouse_x())/32,(vy+i->mouse_y())/32);
   i->mouse_eat(1);
  }
#ifdef DBG_MAP_CONTROL_OBSTACLES
  if(i->mouse_release(SDL_BUTTON_RIGHT)) {
   bool can_remove = true;
   int cx = (vx+i->mouse_x())/32;
   int cy = (vy+i->mouse_y())/32;
   stack<int> st = path;
   while(!st.empty()) {
    int p = st.top();
    st.pop();
    if(p%tw == cx && p/tw == cy) {can_remove = false; break;}
   }
   if(can_remove) {
    obstacles[cx][cy]=!obstacles[cx][cy];
    i->mouse_eat(SDL_BUTTON_RIGHT);
   }
  }
#endif
 }

 update_queue();

 //go to (tx,ty)
 if(tx!=ptx || ty!=pty) {
  int pp = -1;
  if(hsx%32!=0||hsy%32!=0) pp = path.top();
  A_star(); //recalculate path
  if(pp!=-1) path.push(pp);
  view_following = true;
 }

 if(!path.empty()) {
  int p = path.top();
  int px = p%tw;
  int py = p/tw;
  bool from_distance = (px==tx && py==ty && entities[tx][ty] && entities[tx][ty]->visit_from_distance());

  //012
  //345 //4 == [don't move]
  //678
  int dir = 4;
  int nsx = hsx;
  int nsy = hsy;
  if(nsx<px*32) {nsx+=hspd; dir+=1;} //move right
  if(nsx>px*32) {nsx-=hspd; dir-=1;} //move left
  if(nsy<py*32) {nsy+=hspd; dir+=3;} //move down
  if(nsy>py*32) {nsy-=hspd; dir-=3;} //move up
  if(hsx!=px*32||hsy!=py*32||from_distance) {
   if(dir!=4) {
    hero[hero_direction].update(input);
    if(dir!=hero_direction) {
     hero[dir].set_index(0);
     hero[dir].set_x(hx);
     hero[dir].set_y(hy);
    }
    hero_direction = dir;
   } else hero[hero_direction].set_index(0);
  }

  hero[hero_direction].set_x(px);
  hero[hero_direction].set_y(py);

  if((hsx==px*32 && hsy==py*32)||from_distance) {
   path.pop();
   if(entities[tx][ty]!=0) { //the place can be visited - check if it should be
    if((hx==tx && hy==ty) || from_distance) {
     hero[hero_direction].set_x(hx);
     hero[hero_direction].set_y(hy);
     px=tx; py=ty;
     tx=hx; ty=hy;
     hsx=hx*32; hsy=hy*32;
     entities[px][py]->hero_visit(this);
    }
   }
  } else {
   hsx = nsx;
   hsy = nsy;
  }
 } else hero[hero_direction].set_index(0);
 //view move
 if(view_following) {
  int tvx = min(max(hsx+16-vw/2, 0), w-vw);
  int tvy = min(max(hsy+16-vh/2, 0), view_bottom_border);
  if(abs(tvx-vx)>vspd) {
   if(vx<tvx) vx+=vspd; else if(vx>tvx) vx-=vspd;
  } else vx = tvx;
  if(abs(tvy-vy)>vspd) {
   if(vy<tvy) vy+=vspd; else if(vy>tvy) vy-=vspd;
  } else vy=tvy;
 }
}

void Level::move_target(int x, int y) {
 if(x<0||x>=tw||y<0||y>=th||obstacles[x][y]) return;
 tx=x; ty=y;
}

void Level::A_star() {
 vector< vector<int> > visited;
 vector< vector<int> > G, M, T; //Graph, Manhattan, Total
 vector< vector<int> > P; //Parents

 visited.resize(tw);
 G.resize(tw);
 M.resize(tw);
 T.resize(tw);
 P.resize(tw);
 for(int i=0; i<tw; ++i) {
  visited[i].resize(th);
  G[i].resize(th);
  M[i].resize(th);
  T[i].resize(th);
  P[i].resize(th);
 }

 int hx, hy;
 hx = hero[hero_direction].x();
 hy = hero[hero_direction].y();

 vector<int> work_with;
 work_with.push_back(hx+hy*tw);

 for(int i=0; i<tw; ++i)
  for(int j=0; j<th; ++j) {
   Map_Entity* e = entities[i][j];
   int v = 0;
   if(e && (i!=hx || j!=hy) && (i!=tx || j!=ty)) {
    if(e->prevents_way()) v=2;
   }
   visited[i][j]=v;
   M[i][j] = (abs(tx-i)+abs(ty-j))*10;
   P[i][j] = -1;
  }

 G[hx][hy]=0;
 T[hx][hy]=M[hx][hy];

 for(;work_with.size();) {
  vector<int>::iterator me = work_with.begin();
  int mn = T[*me%tw][*me/tw];
  for(vector<int>::iterator i = work_with.begin(); i!=work_with.end(); ++i) {
   if(T[*i%tw][*i/tw] < mn) {
    me = i;
    mn = T[*me%tw][*me/tw];
   }
  }
  int cx, cy;
  cx = *me%tw;
  cy = *me/tw;
  work_with.erase(me);
  visited[cx][cy]=2;
  bool stop = false;
  for(int i=0; i<3; ++i) {
   if(stop) break;
   int wx = cx-1+i;
   if(wx<0||wx>=tw) continue;
   for(int j=0; j<3; ++j) {
    if(stop) break;
    int wy = cy-1+j;
    if((i==1 && j==1)||wy<0||wy>=th) continue;
    if(visited[wx][wy]!=2 && !obstacles[wx][wy]) {
     bool update_cell = false;
     if(visited[wx][wy]==0) {
      work_with.push_back(wx+wy*tw);
      visited[wx][wy] = 1;
      update_cell = true;
     } else if(G[cx][cy]+((abs(cx-wx)+abs(cy-wy))==1?10:14) < G[wx][wy]) update_cell = true;
     if(update_cell) {
      G[wx][wy] = G[cx][cy]+((abs(cx-wx)+abs(cy-wy))==1?10:14);
      T[wx][wy] = G[wx][wy] + M[wx][wy];
      P[wx][wy] = cx+cy*tw;
     }
     if(wx==tx && wy==ty) stop=true;
    }
   }
  }
  if(stop) work_with.clear();
 }

 while(!path.empty()) path.pop();
 if(P[tx][ty] != -1) {
  int bx, by;
  bx = tx;
  by = ty;
  while(bx!=hx || by!=hy) {
   path.push(bx+by*tw);
   int prt = P[bx][by];
   if(prt<0) break;
   bx = prt%tw;
   if(bx<0||bx>=tw) break;
   by = prt/tw;
   if(by<0||by>=th) break;
  }
 }
}

void Level::draw_entity(int x, int y, SDL_Surface* s) {
 Object* e = entities[x][y];
 if(e!=0) {
  if(e->enabled() && e->visible()) e->draw(x*32-vx,y*32-vy,s);
 }
}

void Level::draw_path_cell(int x, int y, int type, SDL_Surface* s) {
 x*=32; x-=vx;
 y*=32; y-=vy;
 switch(type) {
  case 1: path_next->draw(x,y,s); break;
  case 2: path_cell->draw(x,y,s); break;
  case 3: path_trgt->draw(x,y,s); break;
 }
}

Map_Entity* Level::entity(int eid) {
 if(entities_by_id.count(eid)&&entities_by_id[eid]) return entities_by_id[eid];
 return 0;
}

void Level::delete_entity(int eid) {
 Map_Entity* ent = entity(eid);
 if(ent) {
  for(int i=0;i<tw;++i)
   for(int j=0;j<th;++j)
    if(entities[i][j]==ent) entities[i][j]=0;
  delete ent;
  entities_by_id[eid]=0;
 }
}

void Level::draw(SDL_Surface* s) {
 //draw tiles
 if(tileset!=0) {
  int tileset_w = tileset->w() / 32;
  int tileset_h = tileset->h() / 32;
  for(int i=0;i<tw;++i) {
   if(i*32+32 < vx) continue;
   if(i*32 > vx+vw) break;
   for(int j=0;j<th;++j) {
    if(j*32+32 < vy) continue;
    if(j*32 > vy+vh) break;
    int t = tiles[i][j];
    if(t) {
     glColor4f(1,1,1,1);
     glBindTexture(GL_TEXTURE_2D,*tileset->img());
     draw_texture(tileset->pw(), tileset->ph(), 32*((t-1)%tileset_w), 32*(((t-1)/tileset_w)%tileset_h), 32, 32, i*32 - vx, j*32 - vy, 32, 32, 0, false);
    }
    #ifdef DBG_MAP_SHOW_OBSTACLES
     if(obstacles[i][j]) {
      glColor4f(1,0,0,0.45);
      draw_rectangle(i*32 - vx, j*32 - vy, 32, 32);
     }
    #endif
   }
  }
 }
 //draw objects

 //00000
 //11H22
 //33333

 vector< vector<int> > path_cells;
 path_cells.resize(tw);
 for(int i=0; i<tw; ++i) path_cells[i].resize(th);
 stack<int> pth = path;
 int cell = 1;
 while(!pth.empty()) {
  int p = pth.top();
  pth.pop();
  int px = p%tw;
  int py = p/tw;
  if(px==tx && py==ty) cell=3;
  path_cells[px][py] = cell;
  cell=2;
 }

 int hx, hy;
 hx = hero[hero_direction].x();
 hy = hero[hero_direction].y();
 if(hero_direction<3 && (hsx%32!=0&&hsy%32!=0)) {
  ++hy;
  hx-=hero_direction-1;
  if(hx<0) hx=0; if(hy<0) hy=0;
  //cout << hx << ", " << hy << " " << (path_cells[hx][hy]?"path":"") << "\n";
 }
 //0 sequence
 for(int i=0;i<tw;++i)
  for(int j=0;j<hy;++j) {
   draw_entity(i,j,s);
   if(path_cells[i][j]) draw_path_cell(i,j,path_cells[i][j],s);
  }

 //1 sequence
 for(int i=0;i<hx;++i) {
  draw_entity(i,hy,s);
  if(path_cells[i][hy]) draw_path_cell(i,hy,path_cells[i][hy],s);
 }

 //H cell
 draw_entity(hx,hy,s);
 if(path_cells[hx][hy]) draw_path_cell(hx,hy,path_cells[hx][hy],s);
 hero[hero_direction].draw(hsx-vx,hsy-vy,s);

 //2 sequence
 for(int i=hx+1;i<tw;++i) {
  draw_entity(i,hy,s);
  if(path_cells[i][hy]) draw_path_cell(i,hy,path_cells[i][hy],s);
 }

 //3 sequence
 for(int i=0;i<tw;++i)
  for(int j=hy+1;j<th;++j) {
   draw_entity(i,j,s);
   if(path_cells[i][j]) draw_path_cell(i,j,path_cells[i][j],s);
  }

 surface=s;
 draw_queue();
}

void Level::save_state(ofstream& fout) {
 //save hero values
 fout << hero_direction << " " << hero[hero_direction].x() << " " << hero[hero_direction].y() << " " << hsx << " " << hsy << "\n";
 //view
 fout << vx << " " << vy << " " << (view_following?1:0) << "\n";
 //print out target position and the path to it
 fout << tx << " " << ty << " " << path.size();
 stack<int> p;
 while(!path.empty()) {p.push(path.top()); path.pop();}
 while(!p.empty()) {
  int v = p.top(); p.pop();
  path.push(v);
  fout << " " << v;
 }
 fout << "\n";
 //now entities
 for(map<int,Map_Entity*>::iterator i = entities_by_id.begin(); i!=entities_by_id.end(); ++i) {
  Map_Entity* ent = i->second;
  fout << i->first << " " << (ent==0?0:1);
  if(ent&&ent->changeable()) {fout << " "; ent->save(fout);}
  fout << "\n";
 }
 fout << "-1\n";
}

void Level::load_state(ifstream& fin) {
 //load hero values
 fin >> hero_direction;
 int v;
 fin >> v;
 hero[hero_direction].set_x(v);
 fin >> v;
 hero[hero_direction].set_y(v);
 fin >> hsx >> hsy;
 //view
 fin >> vx >> vy >> v;
 view_following=(v==0?false:true);
 //read target position and the path to it
 fin >> tx >> ty;
 while(!path.empty()) path.pop();
 fin >> v;
 int hvl = hero[hero_direction].x()+hero[hero_direction].y()*tw;
 stack<int> p;
 for(int i=0; i<v; ++i) {
  int a;
  fin >> a;
  p.push(a);
 }
 while(!p.empty()) {
  int a = p.top(); p.pop();
  int b = (path.empty()?hvl:path.top());
  int ax = a%tw;
  int ay = a/tw;
  int bx = b%tw;
  int by = b/tw;
  if(abs(ax-bx)<=1 && abs(ay-by)<=1) path.push(a);
 }
 p = path;
 while(!path.empty()) path.pop();
 while(!p.empty()) {path.push(p.top()); p.pop();}
 //now entities
 fin >> v;
 while(v!=-1) {
  int c;
  fin >> c;
  if(c==0) delete_entity(v);
  Map_Entity* ent = entity(v);
  if(ent&&ent->changeable()) ent->load(fin);
  fin >> v;
 }
}

void Level::show_message(Window* wnd) { screen->show_message(wnd); }

void Level::replace_hero(int new_x, int new_y, bool do_activities) {
 hero[hero_direction].set_x(new_x);
 hero[hero_direction].set_y(new_y);
 tx=new_x; ty=new_y;
 hsx=tx*32; hsy=ty*32;

 if(do_activities) {
  if(entities[new_x][new_y]!=0)
   entities[new_x][new_y]->hero_visit(this);
 }
}
