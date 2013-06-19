#include <windows.h>
#include "logger.h"
#include "utils.h"

namespace Engine {

Logger Logger::log("log.txt", cout);
Logger Logger::err("errors.txt", cerr);

Logger::Logger(string fn, ostream& d):
 filename(fn), opened(false), def(d) {};

void Logger::start_session() {
 end_session(); //in case it was started and wasn't ended properly
 if(file_exists(log.filename.c_str())) DeleteFile(log.filename.c_str());
 if(file_exists(err.filename.c_str())) DeleteFile(err.filename.c_str());
}

void Logger::end_session() {
 if(log.opened) {
  log.file.close();
  log.opened=false;
 }
 if(err.opened) {
  err.file.close();
  err.opened=false;
 }
}

}
