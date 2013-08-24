#include "load_string_tables.h"
#include "../Logger.h"
#include "../settings.h"
#include "../utils.h"
#include "../Data/String_Table.h"
using Engine::Data::String_Table;

namespace Engine { namespace Global {

namespace {

void load_string_table(string lang, string filename) {
 string path = "res\\txt\\"; path+=lang; path+="\\"; path+=filename; path+=".txt";
 if(!file_exists(path)) {
  path = "res\\txt\\"; path+=LANGUAGE; path+="\\"; path+=filename; path+=".txt";
  Logger::err << "Chosen localization files not found. [language=\"" << lang << "\"]\n";
 }
 if(!file_exists(path)) throw string("No localization files.");
 String_Table::translate.push_table(path);
}

void load_unicode_table(string lang, string filename) {
 string path = "res\\txt\\"; path+=lang; path+="\\"; path+=filename; path+=".txt";
 if(!file_exists(path.c_str())) {
  path = "res\\txt\\"; path+=LANGUAGE; path+="\\"; path+=filename; path+=".txt";
  Logger::err << "Chosen localizaition unicode table not found. [language=\"" << lang << "\"]\n";
 }
 if(!file_exists(path)) Logger::err << "Default (" << LANGUAGE << ") unicode-table not found.\n";
 String_Table::unicode.push_table(path);
}

}

void load_string_tables(string lang) {
 String_Table::translate.clear();
 load_string_table(lang, "general");

 String_Table::unicode.clear();
 load_unicode_table(lang, "unicode");
}

} }
