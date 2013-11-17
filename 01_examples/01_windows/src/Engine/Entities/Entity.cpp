#include <algorithm>
#include "Entity.h"
#include "../utils.h"
using std::sort;

namespace Engine { namespace Entities {

Entity::Entity(Controller* _controller) {
 if(!_controller) throw "Unable to create entity.";
 controller = _controller;

 _x = _y = _priority = 0;
 _destroy = false;
 _visible = true;
 _enabled = true;
}

Entity::~Entity() {
 clear_queue();
}

//{ protected methods

void Entity::add_entity(Entity* e, bool reorder) {
 if(!e) return;
 children.push_back(queued_entity(e));
 if(reorder) reorder_queue();
}

void Entity::clear_queue() {
 for(enqueue::iterator i=children.begin(); i!=children.end(); ++i)
  delete i->entity;
 children.clear();
}

void Entity::redraw_queue(int x, int y) {
 for(enqueue::iterator i=children.begin(); i!=children.end(); ++i)
  if(i->entity->visible()) i->entity->redraw(_x+x, _y+y);
}

void Entity::reorder_queue() {
 sort(children.begin(), children.end());
}

void Entity::update_queue(int x, int y) {
 enqueue clone;
 clone.reserve(children.size());

 bool removed = false;
 for(enqueue::iterator i=children.begin(); i!=children.end(); ++i)
  if(!i->entity->destroy()) clone.push_back(*i);
  else {
   delete i->entity;
   removed=true;
  }

 if(removed) {
  children.clear();
  children = clone;
 }

 for(enqueue::reverse_iterator i=clone.rbegin(); i!=clone.rend(); ++i)
  if(i->entity->enabled()) i->entity->update(_x+x, _y+y);
}

void Entity::draw_before_queue(int x, int y) {};

void Entity::draw_after_queue(int x, int y) {};

void Entity::update_before_queue(int x, int y) {};

void Entity::update_after_queue(int x, int y) {};

//}

void Entity::redraw(int x, int y) {
 draw_before_queue(x, y);
 redraw_queue(x, y);
 draw_after_queue(x, y);
}

void Entity::update(int x, int y) {
 update_before_queue(x, y);
 update_queue(x, y);
 update_after_queue(x, y);
}

} }
