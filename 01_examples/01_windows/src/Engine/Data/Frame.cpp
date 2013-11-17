#include "Frame.h"
#include "../Logger.h"
#include "../settings.h"

namespace Engine { namespace Data {

Frame::Frame(GLuint* tex, int w, int h, int l, int t, int r, int b, vector< vector<char> >& m, int xs, int ys) {
 _texture = tex;
 _width = w;
 _height = h;
 _left = l;
 _top = t;
 _right = r;
 _bottom = b;
 _x_shift = xs;
 _y_shift = ys;

 #if DEBUG_LOG_SPRITE_LOADING == 1
  Logger::log << "Creating frame...\n";
  Logger::log << " Texture index:  " << tex << "\n";
  Logger::log << " Texture width:  " << w << "\n";
  Logger::log << " Texture height: " << h << "\n";
  Logger::log << " Frame left:     " << l << "\n";
  Logger::log << " Frame top:      " << t << "\n";
  Logger::log << " Frame right:    " << r << "\n";
  Logger::log << " Frame bottom:   " << b << "\n";
 #endif

 w = r-l;
 h = b-t;

 #if DEBUG_LOG_SPRITE_LOADING == 1
  Logger::log << " Frame size:     " << w << "*" << h << "\n";
 #endif

 _mask.resize(w);
 for(int i=0; i<w; ++i)
  _mask[i].resize(h);

 #if DEBUG_LOG_SPRITE_LOADING == 1
  bool has_true = false;
  bool has_false = false;
 #endif
 for(int i=0; i<w; ++i)
  for(int j=0; j<h; ++j) {
   _mask[i][j] = m[i][j];
   #if DEBUG_LOG_SPRITE_LOADING == 1
    if(m[i][j]) has_true=true;
    else has_false=true;
   #endif
  }

 #if DEBUG_LOG_SPRITE_LOADING == 1
  Logger::log << " Mask has ";
  if(has_true) Logger::log << (has_false?"both transparent and non-transparent":"only non-transparent");
  else Logger::log << (has_false?"only transparent":"neither transparent nor non-transparent");
  Logger::log << "pixels\n";
  Logger::log << "Frame constructed.\n";
 #endif
}

bool Frame::is_intersected(int x, int y) {
 x-=_x_shift;
 y-=_y_shift;
 if(x<0||y<0||x>=width()||y>=height()) return false;
 return _mask[_left+x][_top+y];
}

} }
