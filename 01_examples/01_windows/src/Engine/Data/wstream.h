#ifndef WSTREAM_H
#define WSTREAM_H

#include <string>
#include <sstream>
#include <SDL.h>
using std::streamsize;
using std::string;
using std::stringstream;

namespace Engine { namespace Data {

class wstream {
 private:
  string filename;  
  SDL_RWops* file;

 public:
  wstream();
  wstream(string fn, bool append = false);

  void open(string fn, bool append = false);
  void close();

  bool write(const char* str);
  bool write(string& str);
  template<class T> wstream& operator<<(const T& p) {
   stringstream ss;
   ss << p;
   string res = "";
   char block[4096];
   for(streamsize n = 0; ;) {
    ss.readsome(block, 4095);
    n=ss.gcount();
    if(n==0) break;
    block[n]='\0';
    res+=block;   
   }
   write(res);
   return *this;
  }
};

} }

#endif //WSTREAM_H
