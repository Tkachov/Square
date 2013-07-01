#include "fade_effect.h"

namespace Engine { namespace Objects {

Fade_Effect::Fade_Effect(Fade_Mode m, int delay, functor* f, int sx, int sy, int pr):
 Object(sx,sy,pr), mode(m), func(f), counter(0), limit(delay), r(0), g(0), b(0) {};

Fade_Effect::~Fade_Effect() {
 if(func) delete func;
}

void Fade_Effect::update(Input*, int xo, int yo) {
 if(counter==limit && func!=0) (*func)();
 ++counter;
}

void Fade_Effect::draw(int x, int y) {
 float alpha = float(counter)/float(limit);
 if(counter>limit) alpha=1.0;
 if(mode==m_FADE_OUT||mode==m_IMAGE_OUT) alpha=1.0-alpha; //invert
 if(mode==m_FADE_IN||mode==m_FADE_OUT) {
  glColor4f(float(r)/255.0, float(g)/255.0, float(b)/255.0, alpha);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  draw_rectangle(x,y,w,h);
 } else {
  Image tex = img.current_image();
  if(tex.img()==0) return;
  glColor4f(1.0, 1.0, 1.0, alpha);
  glBindTexture(GL_TEXTURE_2D,*tex.img());
  draw_texture(tex.pw(),tex.ph(),0,0,tex.w(),tex.h(),x+tex.x(),y+tex.y(),tex.w(),tex.h(),0,false);
 }
}

void Fade_Effect::color_mode(int sr, int sg, int sb, int sw, int sh) {
 r=sr;
 g=sg;
 b=sb;
 w=sw;
 h=sh;
 if(mode==m_IMAGE_IN) mode=m_FADE_IN;
 if(mode==m_IMAGE_OUT) mode=m_FADE_OUT;
}

void Fade_Effect::image_mode() {
 if(mode==m_FADE_IN) mode=m_IMAGE_IN;
 if(mode==m_FADE_OUT) mode=m_IMAGE_OUT;
}

} }
