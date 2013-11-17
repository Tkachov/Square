#include <string>
#include "SDL.h"
#include "Engine/Application.h"
#include "Engine/Logger.h"
using std::string;
using Engine::Application;
using Engine::Logger;

#ifdef ANDROID_NDK
 int SDL_main(int argc, char *argv[]) {
#else
 int main(int argc, char *argv[]) {
#endif
 try {
  Application app;
  app.work(argc, argv);
 } catch(string s) {
  Logger::err << "[error] {" << s << "}\n";
  exit(1);
 } catch(const char* s) {
  Logger::err << "[error] {" << s << "}\n";
  exit(1);
 } catch(...) {
  Logger::err << "[error] {UNKNOWN}\n";
  exit(1);
 }

 exit(0);
 return 0;
}
