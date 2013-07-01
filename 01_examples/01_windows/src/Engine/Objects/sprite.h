#ifndef SPRITE_H
#define SPRITE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "object.h"
#include "image.h"
#include <vector>
using std::vector;

namespace Engine { namespace Objects {

class Sprite: public Object
{
 vector<Image> frames;
 unsigned int curframe;
 int _counter;
 int animspeed;
 int _w, _h;

public:
 Sprite(): Object(), curframe(0), _counter(1), animspeed(1), _w(0), _h(0) {};
 Sprite(Image i): Object(), curframe(0), _counter(1), animspeed(1), _w(0), _h(0) { set_frame(i); }
 Sprite(const Sprite& t);

 virtual void draw(int, int);
 virtual void update(Input*, int = 0, int = 0);
 void set_frame(GLuint*,SDL_Surface*,int,int,int,int);
 void add_frame(GLuint*,SDL_Surface*,int,int,int,int);
 void set_frame(Image);
 void add_frame(Image);

 GLuint* const frame(unsigned int k = 0) {
  if(frames.size()<=k) return 0;
  return frames[k].img();
 };
 unsigned int current_index() { return curframe; }
 GLuint* const current_frame() { return frame(curframe); }
 Image const image(unsigned int k = 0) {
  if(frames.size()<=k) return Image(0,0,0,0,0,0);
  return frames[k];
 }
 Image const current_image() { return image(curframe); }
 SDL_Surface* const bitmap(unsigned int k = 0) {
  if(frames.size()<=k) return 0;
  return frames[k].bmp();
 }
 SDL_Surface* const current_bitmap() { return bitmap(curframe); }
 int animation_speed() { return animspeed; }
 int w() { return _w; }
 int h() { return _h; }
 unsigned int length() { return frames.size(); }

 void set_index(unsigned int k) { curframe = k; _counter = 1; }
 void set_speed(int s) { animspeed = s; }
 bool is_intersected(int mx, int my);
};

} }

#endif // SPRITE_H
