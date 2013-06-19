#include "Engine\logger.h"
#include "Engine\game.h"
#include <windows.h>
#include <string>
using Engine::Logger;
using Engine::Game;
using std::string;

int main(int argc, char** argv) {
 try {
  for(int s=0; s>=0;) {
   Game game;
   switch(s) {
    case 1: game.load(".restart.save"); DeleteFile("saves\\.restart.save"); break;
   }
   try {
    game.loop();
    break;
   } catch (int v) {
    s=v;
    switch(v) {
     case 0: game.stop(); break;//just relaunch
     case 1: game.save(".restart.save"); game.stop(); break;
     default:
      Logger::err << "[error] {" << v << "}\n";
      return 1;
    }
   }
  }
 } catch (string s) {
  Logger::err << "[error] {" << s << "}\n";
  return 1;
 } catch (...) {
  Logger::err << "[error] {UNKNOWN}\n";
  return 1;
 }
 return 0;
}
