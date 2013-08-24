#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <GL/gl.h>
using std::vector;

namespace Engine { namespace Data {

class Frame
{
 private:
  GLuint* _texture;
  int _width, _height; //texture real sizes (only powers of 2)
  int _left, _top, _right, _bottom; //an area that contains a frame (may be whole texture or just a piece of it)
  int _x_shift, _y_shift; //drawing shift

  vector< vector<bool> > _mask; //contains true if pixel is not transparent

 public:
  Frame(GLuint* tex, int w, int h, int l, int t, int r, int b, vector< vector<bool> >& m, int xs = 0, int ys = 0);

  GLuint* texture() { return _texture; }
  int texture_width() { return _width; }
  int texture_height() { return _height; }

  int x_shift() { return _x_shift; }
  int y_shift() { return _y_shift; }
  int left() { return _left; }
  int top() { return _top; }
  int right() { return _right; }
  int bottom() { return _bottom; }
  int width() { return _right-_left; }
  int height() { return _bottom-_top; }

  bool is_intersected(int x, int y);

  void set_x_shift(int v) { _x_shift = v; }
  void set_y_shift(int v) { _y_shift = v; }
  void set_shift(int x, int y) {
   _x_shift = x;
   _y_shift = y;
  }

  void set_area(int l, int t, int r, int b) {
   _left = l;
   _top = t;
   _right = r;
   _bottom = b;
  }

};

} }

#endif // FRAME_H
