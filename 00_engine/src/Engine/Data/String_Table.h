#ifndef STRING_TABLE_H
#define STRING_TABLE_H

#include <string>
#include <map>
using std::string;
using std::map;

namespace Engine { namespace Data {

class String_Table
{
 private:
  map<string,string> table;

 public:
  String_Table();
  String_Table(string filename);

  static String_Table unicode;
  static String_Table translate;
  void push_table(string table);
  string operator[](string key);
  string operator()(string key, string* s0 = 0, string* s1 = 0, string* s2 = 0, string* s3 = 0, string* ss = 0);
  void clear() {table.clear();};
  void displace(string, string);
  void save_table(string table);
};

} }

#endif // STRING_TABLE_H
