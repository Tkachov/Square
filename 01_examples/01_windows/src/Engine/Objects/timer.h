#ifndef TIMER_H
#define TIMER_H

#include "object.h"
#include "..\functor.h"

namespace Engine { namespace Objects {

class Timer: public Object
{
protected:
 int _timer;
 int _limit;
 int _count; //repeats
 int _time; //how many repeats is done
 functor* fnc;

public:
 Timer(int time, int repeats, functor* f): _timer(0), _limit(time), _count(repeats), _time(0), fnc(f) {};
 virtual ~Timer() {};

 virtual void draw(int, int) {};
 virtual void update(Input*, int xo = 0, int yo = 0) {
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
