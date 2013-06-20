#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include "..\input.h"

namespace Engine { namespace Objects {

class Object
{
protected:
 int _x, _y;
 int _priority;
 bool _destroy;
 bool _visible;
 bool _enabled;

public:
 Object(int sx = 0, int sy = 0, int pr = 0): _x(sx), _y(sy), _priority(pr), _destroy(false), _visible(true), _enabled(true) {};
 virtual ~Object() {};

 virtual void update(Input*) = 0;
 virtual void draw() { draw(_x, _y); }
 virtual void draw(int, int) = 0;

 int x() { return _x; }
 int y() { return _y; }
 int priority() { return _priority; }
 bool destroy() { return _destroy; }
 bool visible() { return _visible; }
 bool enabled() { return _enabled; }

 void set_x(int v) { _x=v; }
 void set_y(int v) { _y=v; }
 void set_priority(int v) { _priority=v; }
 void set_visible(bool v) { _visible=v; }
 void set_enabled(bool v) { _enabled=v; }
 void destruct() { _destroy = true; }
};

} }

#endif // OBJECT_H
