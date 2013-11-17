#include "Fade.h"

namespace Engine { namespace Entities {

Fade::Fade(Controller* controller, Fade_Mode _mode, int length, SDL_Color _color, int _width, int _height, functor* f, int sx, int sy, int priority):
 Entity(controller)
{
 _x = sx;
 _y = sy;
 _priority = priority;

 color = _color;
 counter = 0;
 func = f;
 limit = length;
 mode = _mode;
 show_color = true;
 width = _width;
 height = _height;
}

Fade::Fade(Controller* controller, Fade_Mode _mode, int length, Sprite* _image, functor* f, int sx, int sy, int priority):
 Entity(controller)
{
 _x = sx;
 _y = sy;
 _priority = priority;

 counter = 0;
 func = f;
 image = _image;
 limit = length;
 mode = _mode;
 show_color = false;
 width = height = 0;
}

Fade::~Fade() {
 if(func) delete func;
}

void Fade::update(int x, int y) {
 if(counter==limit && func!=0) (*func)();
 ++counter;
}

void Fade::redraw(int sx, int sy) {
 float alpha = float(counter)/float(limit);
 if(counter>limit) alpha=1.0;
 if(mode==m_FADE_OUT) alpha=1.0-alpha; //invert
 if(show_color) {
  glColor4f(float(color.r)/255.0, float(color.g)/255.0, float(color.b)/255.0, alpha);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  draw_rectangle(sx+_x, sy+_y, width, height);
 } else {
  if(image) {
   Frame frame = image->current_frame();
   if(frame.texture())
    draw_frame(frame, sx+_x, sy+_y, alpha);
  }
 }
}

} }
