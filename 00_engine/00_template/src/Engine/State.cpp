#include "State.h"
#include "settings.h"
#include "utils.h" //read_string()

namespace Engine {

State* State::state = 0;

State::State() {
 if(state) throw "Unable to create State: State is a singletone.";
 state = this;
}

State::~State() {
 clear();
}

void State::save(ofstream& fout) {
 for(map<string, map<string, the_value*> >::iterator i = persistents.begin(); i!=persistents.end(); ++i)
  for(map<string, the_value*>::iterator j = (i->second).begin(); j!=(i->second).end(); ++j) {
   fout << i->first << " " << j->first << " ";
   char t = j->second->type();
   fout << t << " ";
   switch(t) {
    case 'i': save_value(static_cast<int*>(j->second->pointer()), fout); break;
    case 's': save_value(static_cast<string*>(j->second->pointer()), fout); break;
   }
   fout << "\n";
  }
 fout << "-1\n";
}

void State::load(ifstream& fin) {
 string group;
 string vname;
 string vtype;
 fin >> group;
 while(group!="-1") {
  fin >> vname >> vtype;
  if(vtype=="i") set_persistent(group, vname, load_value(fin, identity<int>()));
  else if(vtype=="s") set_persistent(group, vname, load_value(fin, identity<string>()));
  else /*do nothing - we don't know typename to proceed*/;
  fin >> group;
 }
}

void State::clear() {
 for(map<string, map<string, the_value*> >::iterator i = persistents.begin(); i!=persistents.end(); ++i)
  for(map<string, the_value*>::iterator j = (i->second).begin(); j!=(i->second).end(); ++j)
   delete j->second;
}

//{ PRIVATE save/load functions for types

void State::save_value(int* v, ofstream& fout) {
 fout << *static_cast<int*>(v);
}

void State::save_value(string* v, ofstream& fout) {
 fout << "\"" << *static_cast<string*>(v) << "\"";
}

int* State::load_value(ifstream& fin, identity<int>) {
 int v;
 fin >> v;
 return new int(v);
}

string* State::load_value(ifstream& fin, identity<string>) {
 return new string( read_string(fin) );
}

//}

void* State::_persistent(string container_key, string variable_key) {
 if(persistents.count(container_key)==0 || persistents[container_key].count(variable_key)==0) {
  #if DEBUG_EXCEPTION_ON_UNALLOCATED_VARIABLE == 1
   throw string("Unallocated \"")+container_key+string(".")+variable_key+string("\" variable.");
  #endif
  return 0;
 }
 return persistents[container_key][variable_key]->pointer();
}

}
