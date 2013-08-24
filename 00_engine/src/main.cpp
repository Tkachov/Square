#include <string>
#include "Engine\Application.h"
#include "Engine\Logger.h"
using std::string;
using Engine::Application;
using Engine::Logger;

int main(int argc, char** argv) {
 try {
  Application app;
  app.work(argc, argv);
 } catch(string s) {
  Logger::err << "[error] {" << s << "}\n";
  return 1;
 } catch(const char* s) {
  Logger::err << "[error] {" << s << "}\n";
  return 1;
 } catch(...) {
  Logger::err << "[error] {UNKNOWN}\n";
  return 1;
 }
 return 0;
}
