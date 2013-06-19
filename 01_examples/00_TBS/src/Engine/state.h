#ifndef STATE_H
#define STATE_H

#include "debug.h"
#include "utils.h"
#include <map>
#include <string>
#include <fstream>
using std::map;
using std::string;
using std::ifstream;
using std::ofstream;

namespace Engine {

class State
{
 private:
  //base class to point on
  class the_value {
   private:
    unsigned int id;
   protected:
    char _type;
   public:
    the_value() {
     static unsigned int cnt = 0;
     id = ++cnt;
     _type = 'U';
    }
    virtual ~the_value() {};
    virtual void* pointer() { return 0; }
    char type() { return _type; }
    bool operator<(const the_value& other) const { return (id < other.id); }
  };

  //template derived class to storage function pointers
  template<typename T> class The_Value: public the_value {
   private:
    T* obj;
   public:
    The_Value(T* o): obj(o) { _type = State::get_type(o); }
    virtual ~The_Value() { if(obj!=0) delete obj; };
    virtual void* pointer() { return obj; }
  };

  map< string, map<string, the_value*> > persistents; //oh god...
 public:
  State();
  ~State();

  void save(ofstream&);
  void load(ifstream&);
  //
  template<typename T> struct identity { typedef T type; };
  template<typename T> static char get_type(T*) { return 'U'; }
  static char get_type(int*) { return 'i'; }
  static char get_type(string*) { return 's'; }
  //savings
  void save_value(int*, ofstream&);
  void save_value(string*, ofstream&);
  //loadings
  int* load_value(ifstream&, identity<int>);
  string* load_value(ifstream&, identity<string>);

  void* persistent(string, string);

  template<typename T> void set_persistent(string ck, string vk, T* p) {
   if(persistents[ck].count(vk)!=0) {
    void* p2 = persistents[ck][vk]->pointer();
    if(p2==p) return;
    delete persistents[ck][vk];
   }
   persistents[ck][vk] = new The_Value<T>(p);
  }

  template<typename T> void update_persistent(string ck, string vk, T& value) {
   if(persistents.count(ck)==0) return;
   if(persistents[ck].count(vk)==0) return;
   T* p = static_cast<T*>(persistents[ck][vk]->pointer());
   if(p) *p = value;
   else p = new T(value);
  }
};

}

#endif // STATE_H
