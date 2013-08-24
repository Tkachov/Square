#include <fstream>
#include "String_Table.h"
#include "..\Logger.h"
#include "..\settings.h"
#include "..\utils.h"
using std::ifstream;
using std::ofstream;
using Engine::Logger;

namespace Engine { namespace Data {

String_Table String_Table::translate;
String_Table String_Table::unicode;

String_Table::String_Table() {};
String_Table::String_Table(string filename) {
 push_table(filename);
}

void String_Table::push_table(string fname) {
 if(!file_exists(fname)) {
  #if DEBUG_LOG_WARNINGS == 1
   Logger::log << "String_Table: not found \"" << fname << "\"\n";
  #endif
  return;
 }
 ifstream fin(fname.c_str());
 fin.get(); fin.get(); fin.get(); //first trash symbols (that's why first line should be empty)
 while(!fin.eof()) {
  string k = "";
  fin >> k;
  if(k.length()>1&&k[0]=='/'&&k[1]=='/') {//comment
   while(!fin.eof()) {
    char ch=fin.get();
    if(ch=='\n') break;
   }
   continue;
  }
  while(!fin.eof()) {
   char ch=fin.get();
   if(ch!='=') k+=ch;
   else break;
  }
  string v = "";
  while(!fin.eof()) {
   char ch=fin.get();
   if(ch!='\n') v+=ch;
   else break;
  }
  int f,l;
  f=l=-1;
  for(unsigned int i=0;i<k.length();++i) {
   char c = k[i];
   if(c!=' '&&c!='\n'&&c!='\t') {
    if(f==-1) f=i;
    l=i;
   }
  }
  if(f!=-1&&l!=-1) k = k.substr(f,l-f+1);
  else continue; //empty key
  f=l=-1;
  for(unsigned int i=0;i<v.length();++i) {
   char c = v[i];
   if(c!=' '&&c!='\n'&&c!='\t') {
    if(f==-1) f=i;
    l=i;
   }
  }
  if(f!=-1&&l!=-1) v = v.substr(f,l-f+1);
  else v="";
  if(v.length()>2&&v[0]=='\"'&&v[v.length()-1]=='\"') v = v.substr(1,v.length()-2);
  table[k]=v;
 }
 fin.close();

 map<string,int> invalid;
 for(map<string,string>::iterator it=table.begin();it!=table.end();++it) {
  string value = it->second;
  map<string,bool> visited;
  visited[it->first]=true;
  while(value.length()&&value[0]=='@') {
   string nkey = value.substr(1,value.length()-1);
   if(table.count(nkey)==0) {
    invalid[it->first] = 1;
    #if DEBUG_LOG_WARNINGS == 1
     Logger::log << it->first << " is invalid key (to " << value << ")\n";
    #endif
    break;
   } else {
    if(visited.count(nkey)==0) {
     value = table[nkey];
     visited[nkey]=true;
    } else {
     invalid[it->first] = 2;
     #if DEBUG_LOG_WARNINGS == 1
      Logger::log << it->first << " is recursive key (to " << value << ")\n";
     #endif
     break;
    }
   }
  }
  table[it->first] = value;
 }
 for(map<string,int>::iterator itr=invalid.begin();itr!=invalid.end();++itr) {
  switch(itr->second) {
   case 1: table[itr->first]+=" [invalid key]"; break;
   case 2: table[itr->first]+=" [recursive]"; break;
  }
 }
 #if DEBUG_LOG_STRING_TABLES == 1
  for(map<string,string>::iterator it=table.begin();it!=table.end();++it) {
   Logger::log << it->first << "\t\t\t=\t" << it->second << "\n";
  }
 #endif
}

string String_Table::operator[](string key) {
 if(table.count(key)!=0) return table[key];
 return "";
}

string String_Table::operator()(string key, string* s0, string* s1, string* s2, string* s3, string* ss) {
 string st = operator[](key);
 string res = "";
 string n = "";
 bool ignore_p = false;
 bool got_p = false;
 for(unsigned int i=0; i<st.length(); ++i) {
  bool add = true;
  switch(st[i]) {
   case '\\': ignore_p=true; break;
   case '%':
    add = false;
    if(got_p) {
     got_p=false;
     int ind = to_int(n);
     n="";
     switch(ind) {
      case 0: if(s0) res+=*s0; break;
      case 1: if(s1) res+=*s1; break;
      case 2: if(s2) res+=*s2; break;
      case 3: if(s3) res+=*s3; break;
      default: if(ss) res+=ss[ind-4]; break;
     }
    } else if(!ignore_p) got_p=true;
    else {add = true; ignore_p=false;}
   break;
   default:
    if(ignore_p) ignore_p=false;
    if(got_p) {n+=st[i]; add=false;}
  }
  if(add) res+=st[i];
 }
 return res;
}

void String_Table::displace(string k, string v) { table[k]=v; }

void String_Table::save_table(string fname) {
 ofstream fout(fname.c_str());
 fout << char(239) << char(187) << char(191) << "\n"; //utf-8 bytes
 for(map<string,string>::iterator it=table.begin();it!=table.end();++it)
  fout << it->first << "\t=\t" << it->second << "\n";
 fout << "\n";
 fout.close();
}

} }
