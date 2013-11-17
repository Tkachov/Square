#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <string>
#include "settings.h"
#include "Data/safe_wstream.h"
using std::cout;
using std::cerr;
using std::ofstream;
using std::ostream;
using std::string;
using Engine::Data::safe_wstream;

namespace Engine {

class Logger
{
 private:
  safe_wstream file;
  string filename;
  bool opened;
  ostream& standard;

  Logger(string fn, ostream& d);

  #if DEBUG_SAFE_LOG_COPY == 1
   static safe_wstream common_file;
  #endif

 public:
  static Logger log, err;

  template<class T> Logger& operator<<(const T& p) {
   #if DEBUG_SAFE_LOG_COPY == 1
    Logger::common_file << p;
   #endif
   if(!opened) {
    file.open(filename.c_str());
    opened=true;
   }
   #ifdef DEBUG_MODE
    standard << p;
   #endif
   file << p;
   return *this;
  }

  static void start_session();
  static void end_session();
};

}
#endif // LOGGER_H
