#ifndef FUNCTOR_H
#define FUNCTOR_H

namespace Engine {
 //base class to point on
 class functor {
  public:
   functor() {};
   virtual ~functor() {};
   virtual void operator()() {};
 };

 //template derived class to storage function pointers
 template<class T> class Functor: public functor {
  private:
   T* master;
   void (T::* func)();

  public:
   Functor(T* m, void (T::* f)()): master(m), func(f) {};
   virtual ~Functor() {};
   void operator()() { (master->*func)(); }
 };
}

#endif // FUNCTOR_H
