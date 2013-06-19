#include "sprite.h"

namespace Engine { namespace Objects {

Sprite::Sprite(const Sprite& t) {
 curframe=t.curframe;
 _counter=t._counter;
 animspeed=t.animspeed;
 _w=t._w; _h=t._h;
 for(vector<Image>::const_iterator i=t.frames.begin(); i!=t.frames.end(); ++i)
  frames.push_back(*i);
}

void Sprite::update(Input*) {
 //animation
 if(frames.size()!=0 && animspeed!=0) {
  if(++_counter % animspeed == 0) {
   _counter=1;
   if(++curframe % frames.size() == 0) curframe=0;
  }
 }

 //input is unused
}

void Sprite::draw(SDL_Surface* s) {
 if(frames.size()==0 || curframe>=frames.size()) return;
 //manually draw current frame's surface
 SDL_Rect dstrect;
 dstrect.x = _x+frames[curframe].x();
 dstrect.y = _y+frames[curframe].y();
 frames[curframe].draw(dstrect.x, dstrect.y, s);
 //SDL_BlitSurface(current_frame(), 0, s, &dstrect);
}

void Sprite::draw(int sx, int sy, SDL_Surface* s) {
 int px = _x; _x=sx;
 int py = _y; _y=sy;
 draw(s);
 _x=px; _y=py;
}

void Sprite::set_frame(GLuint* i,SDL_Surface* s,int w, int h, int pw, int ph) {
 frames.clear();
 _w = _h = 0;
 add_frame(i,s,w,h,pw,ph);
 _counter=1;
 curframe=0;
}

void Sprite::add_frame(GLuint* i,SDL_Surface* s,int w, int h, int pw, int ph) {
 if(i==0) return;
 frames.push_back(Image(i,s,w,h,pw,ph));
 if(w > _w) _w = w;
 if(h > _h) _h = h;
}

void Sprite::set_frame(Image i) {
 frames.clear();
 _w = _h = 0;
 add_frame(i);
 _counter=1;
 curframe=0;
}

void Sprite::add_frame(Image i) {
 frames.push_back(i);
 if(i.w() > _w) _w = i.w();
 if(i.h() > _h) _h = i.h();
}

bool Sprite::is_intersected(int mx, int my) {
 if(frames.size()<=curframe) return false;
 return frames[curframe].is_intersected(mx,my);
}

} }
