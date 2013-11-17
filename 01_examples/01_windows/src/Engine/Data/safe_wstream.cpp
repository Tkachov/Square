#include "safe_wstream.h"

namespace Engine { namespace Data {

safe_wstream::safe_wstream(): filename(""), was_opened(false) {}

safe_wstream::safe_wstream(string fn, bool append) {
 filename = fn;
 was_opened = append;
}

void safe_wstream::open(string fn, bool append) {
 if(append) was_opened = true; //"open" the file even if it is the same one
 else if(filename!=fn) was_opened = false; //"close" the file if it's a new one or do nothing if it's the same

 filename = fn;
}

void safe_wstream::close() {
 filename = "";
 was_opened = false;
}

bool safe_wstream::write(const char* str) {
 SDL_RWops* file = SDL_RWFromFile(filename.c_str(), (was_opened?"a":"w"));
 if(file!=NULL) {
  was_opened = true;
  size_t len = SDL_strlen(str);
  bool result = (SDL_RWwrite(file, str, 1, len)==len);
  file->close(file);
  return result;
 }
 return false;
}

bool safe_wstream::write(string& str) {
 return write(str.c_str());
}

} }
