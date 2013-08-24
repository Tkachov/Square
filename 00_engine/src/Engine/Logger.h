#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <string>
using std::cout;
using std::cerr;
using std::ofstream;
using std::ostream;
using std::string;

namespace Engine {

class Logger
{
 private:
  ofstream file;
  string filename;
  bool opened;
  ostream& standard;

  Logger(string fn, ostream& d);

 public:
  static Logger log, err;

  template<class T> Logger& operator<<(const T& p) {
   if(!opened) {
    file.open(filename.c_str());
    opened=true;
   }
   #ifdef DEBUG_MODE
    standard << p;
   #endif
   file << p;
   file.flush();
   return *this;
  }

  static void start_session();
  static void end_session();
};

}
#endif // LOGGER_H
