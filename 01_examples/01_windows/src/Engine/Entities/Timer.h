#ifndef TIMER_H
#define TIMER_H

#include "Entity.h"
#include "../Functor.h"

namespace Engine { namespace Entities {

class Timer: public Entity
{
protected:
 int _timer;
 int _limit;
 int _count; //repeats
 int _time; //how many repeats is done
 functor* fnc;

public:
 Timer(Controller* controller, int time, int repeats, functor* f): Entity(controller), _timer(0), _limit(time), _count(repeats), _time(0), fnc(f) {};
 virtual ~Timer() { if(fnc) delete fnc; };

 virtual void redraw(int x, int y) {};
 virtual void update(int x, int y) {
  if(_time == _count && _count!=0) return;
  if(_timer==_limit) {
   if(fnc!=0) (*fnc)();
   if(_count>0) ++_time;
   _timer=0;
  }
  ++_timer;
 };
};

} }

#endif // TIMER_H
