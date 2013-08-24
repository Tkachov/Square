#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include "Entity.h"
#include "../Data/Frame.h"
using std::vector;
using Engine::Data::Frame;

namespace Engine { namespace Entities {

class Sprite: public Entity
{
 private:
  vector<Frame> frames;
  unsigned int curframe;
  int _counter;
  int animspeed;
  int _left, _top, _right, _bottom;

 public:
  Sprite(Controller* c);//
  Sprite(Controller* c, Frame f);
  Sprite(const Sprite& s);
  virtual ~Sprite();

  void redraw(int x, int y);
  void update(int x, int y);

  void set_frame(Frame);
  void add_frame(Frame);

  GLuint* const texture(unsigned int k = 0) {
   if(frames.size()<=k) return 0;
   return frames[k].texture();
  };
  unsigned int current_index() { return curframe; }
  GLuint* const current_texture() { return texture(curframe); }
  Frame const frame(unsigned int k = 0) {
   if(frames.size()<=k) {
    vector< vector<bool> > mask;
    return Frame(0, 0, 0, 0, 0, 0, 0, mask);
   }
   return frames[k];
  }
  Frame const current_frame() { return frame(curframe); }

  int animation_speed() { return animspeed; }
  int left() { return _left; }
  int top() { return _top; }
  int right() { return _right; }
  int bottom() { return _bottom; }
  int width() { return _right-_left; }
  int height() { return _bottom-_top; }
  unsigned int length() { return frames.size(); }

  void set_index(unsigned int k) { curframe = k; _counter = 1; }
  void set_speed(int s) { animspeed = s; }

  bool is_intersected(int mx, int my);
};

} }

#endif // SPRITE_H
