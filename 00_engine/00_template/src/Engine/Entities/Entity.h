#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
using std::vector;

namespace Engine { class Controller; }

namespace Engine { namespace Entities {

class Entity {
 protected:
  int _x, _y;
  int _priority;
  bool _destroy;
  bool _visible;
  bool _enabled;

  class queued_entity {
   public:
    queued_entity(Entity* e): entity(e) {};
    Entity* entity;
    bool operator<(const queued_entity& other) const { return (entity->priority() < other.entity->priority()); }
  };

  typedef vector<queued_entity> enqueue;
  enqueue children;

  Controller* controller;

  void add_entity(Entity* entity, bool reorder = true);
  void clear_queue();
  void redraw_queue(int x, int y);
  void reorder_queue();
  void update_queue(int x, int y);

  virtual void draw_before_queue(int x, int y);
  virtual void draw_after_queue(int x, int y);
  virtual void update_before_queue(int x, int y);
  virtual void update_after_queue(int x, int y);

 public:
  Entity(Controller* controller);
  virtual ~Entity();

  virtual void redraw(int x, int y);
  virtual void update(int x, int y);

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
  void destruct() { _destroy=true; }

};

} }

#endif //ENTITY_H
