#include "Sprite.h"
#include "../utils.h"

namespace Engine { namespace Entities {

//{ /* CONSTRUCTORS */

Sprite::Sprite(Controller* c): Entity(c) {
 curframe=0;
 _counter=1;
 animspeed=1;
 _left=_top=_right=_bottom=0;
}

Sprite::Sprite(Controller* c, Frame f): Entity(c) {
 curframe=0;
 _counter=1;
 animspeed=1;
 _left=_top=_right=_bottom=0;

 set_frame(f);
}

Sprite::Sprite(const Sprite& t): Entity(t.controller) {
 curframe=t.curframe;
 _counter=t._counter;
 animspeed=t.animspeed;
 _left=t._left;
 _top=t._top;
 _right=t._right;
 _bottom=t._bottom;
 for(vector<Frame>::const_iterator i=t.frames.begin(); i!=t.frames.end(); ++i)
  frames.push_back(*i);
}

Sprite::~Sprite() {}

//}

//{ ENTITY FUNCTIONS

void Sprite::update(int x_shift, int y_shift) {
 //animation
 if(frames.size()!=0 && animspeed!=0) {
  if(++_counter%animspeed==0) {
   _counter=1;
   if(++curframe%frames.size()==0) curframe=0;
  }
 }
}

void Sprite::redraw(int x_shift, int y_shift) {
 if(frames.size()==0 || curframe>=frames.size()) return;
 draw_frame(frames[curframe], _x+x_shift, _y+y_shift);
}

//}

void Sprite::set_frame(Frame f) {
 frames.clear();
 _left=f.x_shift();
 _top=f.y_shift();
 _right=_left+f.width();
 _bottom=_top+f.height();
 add_frame(f);
 _counter=1;
 curframe=0;
}

void Sprite::add_frame(Frame f) {
 frames.push_back(f);
 if(f.x_shift()<_left) _left=f.x_shift();
 if(f.y_shift()<_top) _top=f.y_shift();
 if(f.x_shift()+f.width()>_right) _right=f.x_shift()+f.width();
 if(f.y_shift()+f.height()>_bottom) _bottom=f.y_shift()+f.height();
}

bool Sprite::is_intersected(int mx, int my) {
 if(frames.size()<=curframe) return false;
 return frames[curframe].is_intersected(mx, my);
}

} }
