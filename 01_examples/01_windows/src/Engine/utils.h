#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Objects\image.h"
#include <stack>
#include <vector>
#include <string>
#include <fstream>
using std::stack;
using std::vector;
using std::string;
using std::ifstream;
using namespace Engine::Objects;

namespace Engine {

 //SDL Documentation fncs
 Uint32 getpixel(SDL_Surface* surface, int x, int y);
 //useful things
 //SURFACES
 Uint8 get_color_r(SDL_Surface*, int, int);
 Uint8 get_color_g(SDL_Surface*, int, int);
 Uint8 get_color_b(SDL_Surface*, int, int);
 Uint8 get_color_a(SDL_Surface*, int, int);
 float get_color_a(GLuint*, int, int);
 SDL_Surface* create_surface(int flags, int w, int h, int bits = 32);
 SDL_Surface* create_surface(SDL_Surface* to_replace, int flags, int w, int h, int bits = 32);
 void blend_surface(SDL_Surface*, Uint32);
 Image* surface_to_texture(SDL_Surface* src, bool delete_after_transform = true);
 //DRAWING [OpenGL]
 void draw_texture(float x, float y, float w, float h, bool center = false);
 void draw_texture(float x, float y, float w, float h, float nw, float nh, float angle = 0, bool center = false);
 void draw_texture(float W, float H, float t_x, float t_y, float t_dx, float t_dy, float x, float y, float dX, float dY, float angle, bool center = false);
 void draw_rectangle(int x, int y, int w, int h);
 //STUFF
 unsigned int nearest2(unsigned int a);
 bool is_power2(unsigned int a);
 //FILES
 bool file_exists(const char*);
 string read_string(ifstream&);
 //STRINGS and NUMBERS
 string thousands(int);
 int toint(string);
 string unichar(Uint16);
 bool letters_equal(string, string);
 //PATH SEARCH
 stack<int> A_star(int fx, int fy, int tx, int ty, vector< vector<bool> >& obstacles, int usualcost = 10, int diagcost = 14);

}

#endif // UTILS_H
