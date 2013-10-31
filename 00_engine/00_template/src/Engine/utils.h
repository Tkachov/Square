#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
#include <SDL.h>
#include "../importgl.h"
using std::istream;
using std::stack;
using std::string;
using std::stringstream;
using std::vector;

namespace Engine {

 namespace Data { class Frame; }
 using Engine::Data::Frame;

 //SURFACES
 Uint32 getpixel(SDL_Surface* surface, int x, int y);
 Uint8 get_color_r(SDL_Surface*, int, int);
 Uint8 get_color_g(SDL_Surface*, int, int);
 Uint8 get_color_b(SDL_Surface*, int, int);
 Uint8 get_color_a(SDL_Surface*, int, int);
 float get_color_a(GLuint*, int, int);

 SDL_Surface* create_surface(int w, int h, int bits = 32);
 SDL_Surface* create_surface(SDL_Surface* to_replace, int w, int h, int bits = 32);

 Frame* surface_to_texture(SDL_Surface* src, bool delete_after_transform = true);

 //DRAWING [OpenGL]
 void draw_frame(Frame& frame, float x, float y, float alpha = 1.0f, float angle = 0, bool center = false);
 void draw_frame(Frame& frame, float x, float y, SDL_Color blend, float alpha = 1.0f, float angle = 0, bool center = false);
 void draw_frame(Frame& frame, float x, float y, float w, float h, float alpha = 1.0f, float angle = 0, bool center = false);
 void draw_frame(Frame& frame, float x, float y, float w, float h, SDL_Color blend, float alpha = 1.0f, float angle = 0, bool center = false);

 void draw_texture(float x, float y, float w, float h, bool center = false);
 void draw_texture(float x, float y, float w, float h, float nw, float nh, float angle = 0, bool center = false);
 void draw_texture(float W, float H, float t_x, float t_y, float t_dx, float t_dy, float x, float y, float dX, float dY, float angle, bool center = false);

 void draw_rectangle(int x, int y, int w, int h);

 //MATH
 unsigned int nearest2(unsigned int a);
 bool is_power2(unsigned int a);

 //FILES
 bool file_exists(const char* name);
 bool file_exists(string& name);
 void read_file(stringstream& destination, const char* name);
 void read_file(stringstream& destination, string& name);
 string read_string(istream& fin);
 bool delete_file(const char* name);
 bool delete_file(string& name);

 //STRINGS and NUMBERS
 void itoa(int i, char* buf, int base = 10);
 int atoi(const char* buf);

 int to_int(string s);
 string to_string(int v, int base = 10);

 string unichar(Uint16);
 bool letters_equal(string, string);

 string thousands(int);

 //PATH SEARCH
 stack<int> A_star(int fx, int fy, int tx, int ty, vector< vector<bool> >& obstacles, int usualcost = 10, int diagcost = 14);

}

#endif // UTILS_H
