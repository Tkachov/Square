#include "image.h"
#include "..\utils.h"

namespace Engine { namespace Objects {

Image::Image(GLuint* img, SDL_Surface* bmp, int w, int h, int nw, int nh, int x, int y, int pr): Object(x,y,pr), image(img), bitmap(bmp), _w(w), _h(h), tw(nw), th(nh) {};

void Image::draw(int x, int y) {
 if(image) {
  glColor4f(1,1,1,1);
  glBindTexture(GL_TEXTURE_2D,*image);
  draw_texture(tw,th,0,0,_w,_h,x,y,_w,_h,0,false);
 }
}

void Image::update(Input* input, int xo, int yo) {
 if(!input->paused() && !input->mouse_eaten(0)) {
  int mx = input->mouse_x()-xo;
  int my = input->mouse_y()-yo;
  bool intersects = ((mx > _x && mx < _x + _w) && (my > _y && my < _y + _h));
  if(intersects) intersects = is_intersected(mx-_x,my-_y);
  if(intersects) {
   input->mouse_eat(0);
   if(input->mouse_release(1)) input->mouse_eat(1);
  }
 }
}

bool Image::is_intersected(int mx, int my) {
 //not completely transparent == intersected
 if(bitmap) return (get_color_a(bitmap,mx,my)!=0);
 if(image) return (get_color_a(image,mx,my)>0.0);
 return false;
}

} }
