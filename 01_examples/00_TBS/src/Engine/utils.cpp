#include "utils.h"
#include "logger.h"
#include "Data\string_table.h"
#include <fstream>
using std::ifstream;
using Engine::Logger;
using Engine::Data::String_Table;

namespace Engine {

 Uint32 getpixel(SDL_Surface* surface, int x, int y) {
  int bpp = surface->format->BytesPerPixel;
  /* Here p is the address to the pixel we want to retrieve */
  Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

  switch(bpp) {
   case 1: return *p; break;
   case 2: return *(Uint16*)p; break;
   case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) return p[0] << 16 | p[1] << 8 | p[2];
    else return p[0] | p[1] << 8 | p[2] << 16;
   break;
   case 4: return *(Uint32*)p; break;
   default: return 0; /* shouldn't happen, but avoids warnings */
  }
 }

 Uint8 get_color_r(SDL_Surface* surface, int x, int y) {
  Uint8 r,t;
  SDL_LockSurface(surface);
  SDL_GetRGBA(getpixel(surface,x,y), surface->format, &r, &t,&t,&t);
  SDL_UnlockSurface(surface);
  return r;
 }

 Uint8 get_color_g(SDL_Surface* surface, int x, int y) {
  Uint8 r,t;
  SDL_LockSurface(surface);
  SDL_GetRGBA(getpixel(surface,x,y), surface->format, &t, &r, &t,&t);
  SDL_UnlockSurface(surface);
  return r;
 }

 Uint8 get_color_b(SDL_Surface* surface, int x, int y) {
  Uint8 r,t;
  SDL_LockSurface(surface);
  SDL_GetRGBA(getpixel(surface,x,y), surface->format, &t,&t, &r, &t);
  SDL_UnlockSurface(surface);
  return r;
 }

 Uint8 get_color_a(SDL_Surface* surface, int x, int y) {
  Uint8 r,t;
  SDL_LockSurface(surface);
  SDL_GetRGBA(getpixel(surface,x,y), surface->format, &t,&t,&t, &r);
  SDL_UnlockSurface(surface);
  return r;
 }

 float get_color_a(GLuint* tex, int x, int y) {
  //IT'S FUCKING SLOW.
  glBindTexture(GL_TEXTURE_2D, *tex);
  int w,h;
  glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH, &w);
  glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_HEIGHT, &h);
  float unit_tex[w][h];
  glGetTexImage(GL_TEXTURE_2D, 0, GL_ALPHA, GL_FLOAT, unit_tex);
  return unit_tex[x][y];
 }

 SDL_Surface* create_surface(int flags, int w, int h, int bits) {
  Uint32 rmask, gmask, bmask, amask;
  #if SDL_BYTEORDER == SDL_BIG_ENDIAN
   rmask = 0xff000000;
   gmask = 0x00ff0000;
   bmask = 0x0000ff00;
   amask = 0x000000ff;
  #else
   rmask = 0x000000ff;
   gmask = 0x0000ff00;
   bmask = 0x00ff0000;
   amask = 0xff000000;
  #endif
  return SDL_CreateRGBSurface(flags, w, h, bits, rmask, gmask, bmask, amask);
 }

 SDL_Surface* create_surface(SDL_Surface* to_replace, int flags, int w, int h, int bits) {
  if(to_replace!=0) SDL_FreeSurface(to_replace);
  to_replace = create_surface(flags, w, h, bits);
  return to_replace;
 }

 void blend_surface(SDL_Surface* surface, Uint32 alpha) {
  //do not repeat this trick at home (it may be slow & dangerous)
  if(alpha<0||alpha>255) alpha=255;
  Uint32 bpp = surface->format->BytesPerPixel;
  if(bpp!=4) return;
  SDL_LockSurface(surface);
  Uint8 r,g,b,a;
  Uint8 *p = (Uint8*)surface->pixels;
  Uint32 sz = surface->w * surface->h;
  for(Uint32 c=0; c<sz; ++c, p+=bpp) {
   SDL_GetRGBA(*(Uint32*)p, surface->format, &r,&g,&b, &a);
   Uint32 np = 0;
   Uint32 al = ((Uint32)a)*alpha/255;
   #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    np += (r<<24) + (g<<16) + (b<<8) + (al);
   #else
    np += (al<<24) + (b<<16) + (g<<8) + (r);
   #endif
   *(Uint32*)p = np;
  }
  SDL_UnlockSurface(surface);
 }

 Image* surface_to_texture(SDL_Surface* src, bool delete_after_transform) {
  int _w, _h, nw, nh;
  _w = src->w;
  _h = src->h;
  nw = nearest2(_w);
  nh = nearest2(_h);
  SDL_Surface* temp = create_surface(SDL_SWSURFACE, nw, nh);
  SDL_SetAlpha(src, 0, 0);
  SDL_Rect dstrect;
  dstrect.x = dstrect.y = 0;
  SDL_BlitSurface(src, 0, temp, &dstrect);
  SDL_Flip(temp);
  if(delete_after_transform) {SDL_FreeSurface(src); src=0;}

  int format = GL_RGBA;
  if(temp->format->BitsPerPixel == 24) format = GL_RGB;

  GLuint* p = new GLuint();
  glGenTextures(1, p);
  glBindTexture(GL_TEXTURE_2D, *p);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//GL_NEAREST - without filtration
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//GL_LINEAR - causes border bugs
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

  glTexImage2D(GL_TEXTURE_2D, 0, format, nw, nh, 0, format, GL_UNSIGNED_BYTE, temp->pixels);
  SDL_FreeSurface(temp);
  return new Image(p,src,_w,_h,nw,nh);
 }

 /*DRAWING [OpenGL]*/

void draw_texture(float x, float y, float w, float h, bool center) {
 draw_texture(w,h,0,0,w,h,x,y,w,h,0,center);
}

void draw_texture(float x, float y, float w, float h, float nw, float nh, float angle, bool center) {
 draw_texture(w,h,0,0,w,h,x,y,nw,nh,angle,center);
}

void draw_texture(float W,//whole texture sizes
               float H,
               float t_x,//piece coordinates
               float t_y,
               float t_dx,//piece size
               float t_dy,

               float x,//screen position
               float y,
               float dX, //new size
               float dY,
               float angle, //rotation
               bool center)
 {
  glEnable(GL_TEXTURE_2D);

  glTranslatef(x,y,0);
  glRotatef(angle,0,0,-1);

  if(center) {glTranslatef(-dX/2,-dY/2,0);}

  glBegin(GL_QUADS);

   glTexCoord2f((t_x/W),(t_y/H));               glVertex2f(0, 0); //top-left
   glTexCoord2f((t_x/W),((t_y+t_dy)/H));        glVertex2f(0, dY);//bottom-left
   glTexCoord2f(((t_x+t_dx)/W),((t_y+t_dy)/H)); glVertex2f(dX,dY);//bottom-right
   glTexCoord2f(((t_x+t_dx)/W),(t_y/H));        glVertex2f(dX, 0);//top-right

  glEnd();
  glTranslatef(-x,-y,0);
  if(center) {glTranslatef(dX/2,dY/2,0);}
 }

 void draw_rectangle(int x, int y, int w, int h) {
  glDisable(GL_TEXTURE_2D);
  glTranslatef(x,y,0);
  glBegin(GL_POLYGON);
   glVertex2f(0,0);
   glVertex2f(0,h);
   glVertex2f(w,h);
   glVertex2f(w,0);
  glEnd();
  glTranslatef(-x,-y,0);
 }

 /*STUFF*/
 unsigned int nearest2(unsigned int a) {
  if(!is_power2(a)) {
   unsigned int p = 1;
   while(p<a) p*=2;
   a=p;
  }
  return a;
 }
 bool is_power2(unsigned int v) { return ((v&(v-1))==0); }

 /*FILES*/

 bool file_exists(const char* fn) {
  ifstream f(fn);
  return f;
 }

 string read_string(ifstream& file) {
  string s = "";
  char buf[80];
  while(s=="" && !file.eof()) {
   file.get(buf,80,'\n');
   s+=buf;
   for(string::iterator i = s.begin(); i!=s.end(); ++i)
    if(*i!=' ') {s.erase(s.begin(), i); break;}
  }
  while(!file.eof() && s[0]=='\"' && s[s.length()-1]!='\"') {
   file.get(buf,80,'\n');
   s+=buf;
  }
  if(s.length()>0 && s[0]=='\"') s.erase(0,1);
  if(s.length()>0 && s[s.length()-1]=='\"') s.erase(s.length()-1,1);
  return s;
 }

 /*STRINGS and NUMBERS*/

string thousands(int n) {
 string sign = "";
 if(n<0) {sign="-"; n*=-1;}
 if(n<1000) {
  char buf[4];
  itoa(n, buf, 10);
  string res = sign;
  res+=buf;
  return res;
 }

 double delimiter = 1000.0f;
 if(n>=1000000) delimiter*=1000;
 double frac = double(n)/delimiter;
 int fr = frac; frac-=fr;
 string frc = "";
 string e = "";
 if(frac>=0.09) {
  if(frac<0.45) sign='~'+sign;
  else if(frac<=0.55) frc=".5";
  else {frc=".5"; e="+";}
 }
 string res = sign;
 char buf[10];
 int r = n/delimiter;
 itoa(r, buf, 10);
 res+=buf;
 res+=frc;
 while(delimiter>1) {res+='K'; delimiter/=1000;}
 res+=e;
 return res;
}

int toint(string s) {
 int res = 0;
 unsigned int md = 1;
 for(int i=s.length()-1; i>=0; --i) {
  char c = s[i];
  if(i==0) {
   if(c=='+') break;
   if(c=='-') {res*=-1; break;}
  }
  if('0'<=c && c<='9') {
   res+=(int(c)-int('0'))*md;
   md*=10;
  }
 }
 return res;
}

string unichar(Uint16 v) {
 if((v&0xFF80)==0) {
  char c = char(v&0x7F);
  string s = ""; s+=c;
  return s;
 } else {
  char buf[20];
  itoa(v,buf,10);
  string k = buf;
  string c = String_Table::unicode[k];
  if(c.length()) return c;
  else Logger::log << "unknown char " << v << "\n";
 }
 return "";
}

bool letters_equal(string a, string b) {
 if(a.length()!=b.length()) return false;
 for(unsigned int i=0; i<a.length(); ++i) {
  char ca = a[i];
  char cb = b[i];
  if(ca>='A'&&ca<='Z') ca=char(int(ca)-int('A')+int('a'));
  if(cb>='A'&&cb<='Z') cb=char(int(cb)-int('A')+int('a'));
  if(ca!=cb) return false;
 }
 return true;
}

 /*PATH SEARCH*/

stack<int> A_star(int fx, int fy, int tx, int ty, vector< vector<bool> >& obstacles, int usualcost, int diagcost) {
 int tw = obstacles.size();
 int th = obstacles[0].size();
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

 vector<int> work_with;
 work_with.push_back(fx+fy*tw);

 for(int i=0; i<tw; ++i)
  for(int j=0; j<th; ++j) {
   visited[i][j]=0;
   M[i][j] = (abs(tx-i)+abs(ty-j))*usualcost;
   P[i][j] = -1;
  }

 G[fx][fy]=0;
 T[fx][fy]=M[fx][fy];

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
     } else if(G[cx][cy]+((abs(cx-wx)+abs(cy-wy))==1?usualcost:diagcost) < G[wx][wy]) update_cell = true;
     if(update_cell) {
      G[wx][wy] = G[cx][cy]+((abs(cx-wx)+abs(cy-wy))==1?usualcost:diagcost);
      T[wx][wy] = G[wx][wy] + M[wx][wy];
      P[wx][wy] = cx+cy*tw;
     }
     if(wx==tx && wy==ty) stop=true;
    }
   }
  }
  if(stop) work_with.clear();
 }

 stack<int> path;
 if(P[tx][ty] != -1) {
  int bx, by;
  bx = tx;
  by = ty;
  while(bx!=fx || by!=fy) {
   path.push(bx+by*tw);
   int prt = P[bx][by];
   if(prt<0) break;
   bx = prt%tw;
   if(bx<0||bx>=tw) break;
   by = prt/tw;
   if(by<0||by>=th) break;
  }
  if(bx!=fx||by!=fy) while(!path.empty()) path.pop();
 }

 return path;
}

}
