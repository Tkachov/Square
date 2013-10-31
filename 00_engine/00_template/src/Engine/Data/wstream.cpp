#include "wstream.h"

namespace Engine { namespace Data {

wstream::wstream(): filename(""), file(0) {}

wstream::wstream(string fn, bool append) {
 filename = fn;
 file = SDL_RWFromFile(filename.c_str(), (append?"a":"w"));
}

void wstream::open(string fn, bool append) {
 close();

 filename = fn;
 file = SDL_RWFromFile(filename.c_str(), (append?"a":"w"));
}

void wstream::close() {
 filename = "";
 if(file) {
  file->close(file);
  file = 0;
 }
}

bool wstream::write(const char* str) {
 if(file) {
  size_t len = SDL_strlen(str);
  bool result = (SDL_RWwrite(file, str, 1, len)==len);
  return result;
 }
 return false;
}

bool wstream::write(string& str) {
 return write(str.c_str());
}

} }
