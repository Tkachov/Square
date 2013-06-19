#include "loadgame_window.h"
#include "..\..\Engine\Data\string_table.h"
#include "..\..\Engine\utils.h"
#include "message.h"
#include <windows.h>

LoadGame_Window::LoadGame_Window(bool loading, Game* g, Loader* l, int pr):
 Window(g,l,0,0,pr), loading_window(loading), bt_delete(0), bt_load(0), bt_save(0), bt_cancel(0), bt_scroll_up(0), bt_scroll_dn(0), tx_savename(0), tx_savedate(0), ed_savename(0), mvup_delay(0), mvdn_delay(0) {
  //add background
  int sw = game->w();
  int sh = game->h();
  Image* img = new Image(*loader->load_texture("res\\img\\GUI\\windows\\loading_box.png"));
  pw = img->w();
  ph = img->h();
  px = (sw - pw)/2;
  py = (sh - ph)/2;
  img->set_x(px);
  img->set_y(py);
  add_object(img);

  HANDLE hFind = INVALID_HANDLE_VALUE;
  WIN32_FIND_DATA ffd;
  hFind = FindFirstFile("saves\\*", &ffd);
  if(INVALID_HANDLE_VALUE == hFind) throw string("LoadGame_Window - failed to find saves.");

  string fn;
  do {
   if(!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
    fn = ffd.cFileName;
    if(fn.length()>4&&fn.substr(fn.length()-5,5)==".save") {
     string svnm = fn.substr(0,fn.length()-5);
     if(svnm==""||svnm.length()>20) continue;
     bool invalid_save = false;
     for(unsigned int i=0; i<svnm.length(); ++i)
      if(!valid_ASCII(svnm[i])) {invalid_save=true; break;}
     if(invalid_save) continue;
 int phase=0;
 string nm = "";
     string sfn="saves\\"+fn;
     ifstream fin(sfn.c_str());
     for(int i=0;!fin.eof();++i) {
      string str = "";
      while(!fin.eof()) {
       char ch=fin.get();
       str+=ch;
       if(ch=='\n') break;
      }
      if(phase==0&&(str=="-1"||str=="-1\n")) phase=5;
     }
     fin.close();
     if(invalid_save||phase!=5) continue;
     SaveGame_Button* bt = new SaveGame_Button(svnm,new Functor<LoadGame_Window>(this, &LoadGame_Window::fnc_selection),new Functor<LoadGame_Window>(this, &LoadGame_Window::fnc_runchosen),loader,px+11,0,1);
     FILETIME ft;
     SYSTEMTIME tm;
     FileTimeToLocalFileTime(&ffd.ftLastWriteTime, &ft);
     FileTimeToSystemTime(&ft, &tm);
     char buf[10];
     itoa(tm.wDay,buf,10);
     string dt = buf; dt+=".";
     itoa(tm.wMonth,buf,10);
     dt+=buf; dt+=".";
     itoa(tm.wYear,buf,10);
     dt+=buf; dt+=" ";
     itoa(tm.wHour,buf,10);
     dt+=buf; dt+=":";
     itoa(tm.wMinute,buf,10);
     if(tm.wMinute<10) dt+='0';
     dt+=buf;
     bt->set_date(dt);
     bt->slotname = svnm;
     long long unsigned int t = 0;
     t+=tm.wSecond;
     t+=tm.wMinute*60;
     t+=tm.wHour*60*60;
     t+=tm.wDay*60*60*24;
     t+=tm.wMonth*60*60*24*31; //some timeholes there
     t+=(tm.wYear-1500)*60*60*24*366; //but let it be - we need just some value to compare to
     slots.push_back(slot(t, bt));
     saves[svnm]=bt;
     add_object(bt);
    }
   }
  } while(FindNextFile(hFind, &ffd) != 0);

  sort(slots.begin(), slots.end());
  int ypos = 0;
  for(slotlist::iterator i=slots.begin();i!=slots.end();++i) {
   i->button->set_y(ypos+py+67);
   if(ypos>=270) i->button->set_enabled(false);
   ypos+=45;
  }

  load();
 }

LoadGame_Window::~LoadGame_Window() {
 if(ed_savename&&input&&ed_savename->is_selected()) input->repeating(false);
}

string LoadGame_Window::loc_name(int n) {
 switch(n) {
  case s_THE_FOREST: return String_Table::translate["loc_the_forest"];
 }
 return "";
}

bool LoadGame_Window::valid_ASCII(char c) {
 if('a'<=c&&c<='z') return true;
 if('A'<=c&&c<='Z') return true;
 if('0'<=c&&c<='9') return true;
 if(c=='-'||c=='_'||c=='('||c==')'||c=='#'||c=='!'||c=='.'||c==' ') return true;
 //the following 're invalid in windows:
 //if(c=='\\'||c=='/'||c==':'||c=='*'||c=='?'||c=='"'||c=='<'||c=='>'||c=='|'||c=='\'') return false;
 return false;
}

bool LoadGame_Window::key_hold_or_pressed(int delay, int key) {
 if(input==0) return false;
 return (delay==0 && (input->key_release(key) || input->key_hold(key)));
}

void LoadGame_Window::load() {
 //header&message
 SDL_Color c; c.r=c.g=c.b=255;
 add_object(tx_savename = new Text(loader->load_font("Tahoma",16), (loading_window?String_Table::translate["loadbox_no_saves_found"]:""), 0, c, px+10, py+10, 2));
 add_object(tx_savedate = new Text(loader->load_font("Tahoma",10), "", 0, c, px+10, py+34, 1));

 if(!loading_window) {
  add_object(ed_savename = new Edit(tx_savename, 0, loader, px+14, py+10, 252, 1));
  ed_savename->set_checker(new Functor<LoadGame_Window>(this, &LoadGame_Window::fnc_update_name));
  tx_savename->set_x(px+14);

  SYSTEMTIME tm;
  GetLocalTime(&tm);
  char buf[10];
  itoa(tm.wDay,buf,10);
  string dt = buf; dt+=".";
  itoa(tm.wMonth,buf,10);
  dt+=buf; dt+=".";
  itoa(tm.wYear,buf,10);
  dt+=buf; dt+=" ";
  itoa(tm.wHour,buf,10);
  dt+=buf; dt+=":";
  itoa(tm.wMinute,buf,10);
  if(tm.wMinute<10) dt+='0';
  dt+=buf;
  tx_savedate->set_text(dt);
 }

 //buttons
 int bx = px+10;
 int by = py+ph-50+6;
 add_object(bt_delete = new Blue_Button(String_Table::translate["loadbox_delete"], new Functor<LoadGame_Window>(this, &LoadGame_Window::fnc_delete), loader, bx, by, 120, 2));
 bx = px+10+120+10;
 if(loading_window)
  add_object(bt_load = new Blue_Button(String_Table::translate["loadbox_load"], new Functor<LoadGame_Window>(this, &LoadGame_Window::fnc_load), loader, bx, by, 120, 2));
 else
  add_object(bt_save = new Blue_Button(String_Table::translate["loadbox_save"], new Functor<LoadGame_Window>(this, &LoadGame_Window::fnc_save), loader, bx, by, 120, 2));
 bx = px+pw-120-10;
 add_object(bt_cancel = new Blue_Button(String_Table::translate["loadbox_cancel"], new Functor<LoadGame_Window>(this, &LoadGame_Window::fnc_cancel), loader, bx, by, 120, 2));

 //scroll buttons
 Button* bt = new Button(new Functor<LoadGame_Window>(this, &LoadGame_Window::fnc_scroll_up));
 bt->set_states(
  loader->load_sprite("res\\img\\GUI\\buttons\\scroll\\up.sprite"),
  loader->load_sprite("res\\img\\GUI\\buttons\\scroll\\up_over.sprite"),
  loader->load_sprite("res\\img\\GUI\\buttons\\scroll\\up_press.sprite"),
  loader->load_sprite("res\\img\\GUI\\buttons\\scroll\\up_off.sprite")
 );
 bt->set_x(px+pw-16-10);
 bt->set_y(py+67-1);
 bt->set_priority(2);
 bt->set_holding_click_delay(15);
 add_object(bt_scroll_up = bt);

 bt = new Button(new Functor<LoadGame_Window>(this, &LoadGame_Window::fnc_scroll_dn));
 bt->set_states(
  loader->load_sprite("res\\img\\GUI\\buttons\\scroll\\down.sprite"),
  loader->load_sprite("res\\img\\GUI\\buttons\\scroll\\down_over.sprite"),
  loader->load_sprite("res\\img\\GUI\\buttons\\scroll\\down_press.sprite"),
  loader->load_sprite("res\\img\\GUI\\buttons\\scroll\\down_off.sprite")
 );
 bt->set_x(px+pw-16-10);
 bt->set_y(py+67+270-16);
 bt->set_priority(2);
 bt->set_holding_click_delay(15);
 add_object(bt_scroll_dn = bt);

 if(loading_window) select_slot("");
 else {
  if(bt_save) bt_save->set_disabled((!tx_savename||tx_savename->text()==""));
  if(bt_delete) bt_delete->set_disabled(true);
  labels_update();
 }
}

void LoadGame_Window::update() {
 if(_destroy||input==0) return;
 input->unpause();
 update_queue();
 input->pause();
}

void LoadGame_Window::update(Input* _input) {
 if(mvup_delay) --mvup_delay;
 if(mvdn_delay) --mvdn_delay;
 input = _input;
 if(slots.size()&&(!ed_savename||!ed_savename->is_selected())) {
  if(key_hold_or_pressed(mvup_delay,SDLK_UP)) {fnc_move_up(); mvup_delay=9;}
  else if(key_hold_or_pressed(mvdn_delay,SDLK_DOWN)) {fnc_move_dn(); mvdn_delay=9;}
  else if(input->key_release(SDLK_RETURN, true)) fnc_runchosen();
 }
 update();
 if(input->key_release(SDLK_ESCAPE, true)) disappear();
 if(_destroy) input->unpause(); //in case when the object was destroyed inside this function
}

void LoadGame_Window::fnc_cancel() { disappear(); }
void LoadGame_Window::fnc_load() {
 for(slotlist::iterator i=slots.begin();i!=slots.end();++i)
  if(i->button->selected) {
   string s = i->button->slotname + ".save";
   game->load(s);
   break;
  }
}
void LoadGame_Window::fnc_save() {
 string fn = tx_savename->text();
 string s = "saves\\" + fn + ".save";
 if(file_exists(s.c_str())) add_object(new Message(Message::MSG_SMALL, game, loader, String_Table::translate("loadbox_rewrite",&fn), new Functor<LoadGame_Window>(this, &LoadGame_Window::fnc_complete_save), 0, 10));
 else fnc_complete_save();
}
void LoadGame_Window::fnc_complete_save() {
 string s = tx_savename->text() + ".save";
 game->save(s);
 disappear();
}
void LoadGame_Window::fnc_delete() {
 string first;
 SaveGame_Button* second;
 slotlist::iterator slut; //:D
 string nextslot = "";
 bool found = false;
 for(slotlist::iterator i=slots.begin();i!=slots.end();++i) {
  if(found&&nextslot=="") nextslot = i->button->slotname;
  if(i->button->selected==2&&!found) {
   first = i->button->slotname;
   second = i->button;
   slut = i;
   found = true;
  }
  if(found) {
   i->button->set_y(i->button->y()-45);
   i->button->set_enabled((i->button->y()<py+67+270));
  }
  i->button->selected = 0;
 }
 if(found) {
  string s = "saves\\" + first + ".save";
  DeleteFile(s.c_str());
  slots.erase(slut);
  second->destruct();
  saves.erase(first);
 }
 select_slot(nextslot);
}

void LoadGame_Window::fnc_move_up() {
 string nm = "";
 bool found = false;
 for(slotlist::iterator i=slots.begin();i!=slots.end();++i) {
  if(i->button->selected) {
   if(i==slots.begin()) return; //first in list - don't move
   i->button->selected=0;
   found=true;
   break;
  }
  nm=i->button->slotname;
 }
 if(!found) {
  nm="";
  if(slots.size()) slots[0].button->selected = 1;
 }
 select_slot(nm);
}
void LoadGame_Window::fnc_move_dn() {
 string nm = "";
 bool found = false;
 SaveGame_Button* bt;
 for(slotlist::iterator i=slots.begin();i!=slots.end();++i) {
  if(found) {nm=i->button->slotname; break;}
  if(i->button->selected) {found=true; bt=i->button; bt->selected=0;}
 }
 if(!found) {
  nm="";
  if(slots.size()) slots[0].button->selected = 1;
 }
 if(found&&nm=="") {bt->selected=2; return;} //the last in list - don't move
 select_slot(nm);
}

void LoadGame_Window::fnc_selection() {
 bool selected = false;
 for(slotlist::iterator i=slots.begin();i!=slots.end();++i) {
  if(i->button->selected!=1||selected) i->button->selected=0;
  else selected=select_slot(i->button->slotname);
 }
 if(!selected) select_slot("");
}

void LoadGame_Window::fnc_runchosen() {
 if(loading_window) {
  if(bt_load&&!bt_load->is_disabled()) fnc_load();
 } else {
  if(bt_save&&!bt_save->is_disabled()) fnc_save();
 }
}

void LoadGame_Window::fnc_scroll_up() {
 if(slots.size()==0 || slots[0].button->y()>=py+67) return;
 string slt = "";
 SaveGame_Button* bt = 0;
 bool found = false;
 for(slotlist::iterator i=slots.begin();i!=slots.end();++i) {
  if(i->button->selected) {found=true; bt=i->button;}
  if(!found) slt=i->button->slotname;
  i->button->set_y(i->button->y()+45);
  i->button->set_enabled((i->button->y()>=py+67 && i->button->y()<py+67+270));
  i->button->selected=0;
 }
 if(bt&&bt->enabled()) slt=bt->slotname;
 select_slot(slt);
}

void LoadGame_Window::fnc_scroll_dn() {
 if(slots.size()==0 || slots.back().button->y()<py+67+270) return;
 string slt = "";
 SaveGame_Button* bt = 0;
 bool found = false;
 for(slotlist::iterator i=slots.begin();i!=slots.end();++i) {
  if(found) {slt=i->button->slotname; found=false;}
  if(i->button->selected) {found=true; bt=i->button;}
  i->button->set_y(i->button->y()-45);
  i->button->set_enabled((i->button->y()>=py+67 && i->button->y()<py+67+270));
  i->button->selected=0;
 }
 if(bt&&bt->enabled()) slt=bt->slotname;
 select_slot(slt);
}

void LoadGame_Window::fnc_update_name() {
 Text* txt = tx_savename;
 if(input->key_press(SDLK_BACKSPACE)) {
  if(txt->text().length()>0) txt->set_text(txt->text().substr(0,txt->text().length()-1));
 } else if(input->key_press(SDLK_RETURN)||input->key_press(SDLK_KP_ENTER)||input->key_press(SDLK_TAB)||input->key_press(SDLK_ESCAPE)) {
  /*ignore these, they throw ugly characters*/
 } else {
  for(unsigned int i=0; i<input->keyboard_string.size(); ++i) {
   Input::keychar kc = input->keyboard_string[i];
   char c = '\0';
   if(kc.unicode.length()==1) c = kc.unicode[0];
   else if(kc.keycode >= SDLK_a && kc.keycode <= SDLK_z) c = char(int('a') + kc.keycode-SDLK_a); //back-convert non-latin character
   if(!valid_ASCII(c)) c='\0';
   if(c!='\0') txt->set_text(txt->text()+c);
  }
 }

 if(tx_savename&&tx_savename->text().length()>20) tx_savename->set_text(tx_savename->text().substr(0,20));
 if(bt_save) bt_save->set_disabled((!tx_savename||tx_savename->text()==""));
}

bool LoadGame_Window::select_slot(string s) {
 if(s=="") {
  if(slots.size()==0) {
   if(bt_delete) bt_delete->set_disabled(true);
   if(loading_window) {
    if(tx_savename) tx_savename->set_text(String_Table::translate["loadbox_no_saves_found"]);
    if(tx_savedate) tx_savedate->set_text("");
    if(bt_load) bt_load->set_disabled(true);
   } else {
    if(bt_save) bt_save->set_disabled((!tx_savename||tx_savename->text()==""));
   }
   labels_update();
  } else return select_slot(slots.begin()->button->slotname);
  return true;
 }
 if(saves.count(s)==0) return false;
 if(!loading_window&&tx_savename->text()=="") {
  bool found = false;
  for(slotlist::iterator i=slots.begin();i!=slots.end();++i)
   if(i->button->selected) found=true;
  if(!found) {
   labels_update();
   return false;
  }
 }
 if(bt_delete) bt_delete->set_disabled(false);
 if(bt_load) bt_load->set_disabled(false);
 if(bt_save) bt_save->set_disabled(false);
 SaveGame_Button* b = saves[s];
 b->selected=2;
 if(tx_savename) tx_savename->set_text(b->savename());
 if(loading_window) {
  if(tx_savedate) tx_savedate->set_text(b->savedate());
 }

 if(b->y()<py+67) {
  int diff = py+67 - b->y();
  for(slotlist::iterator i=slots.begin();i!=slots.end();++i) {
   i->button->set_y(i->button->y()+diff);
   i->button->set_enabled((i->button->y()>=py+67 && i->button->y()<py+67+270));
   i->button->selected = (i->button==b?2:0);
  }
 }
 if(b->y()>=py+67+270-45 || (slots.size()>=6 && b == slots[slots.size()-1].button && b->y()!=py+67+270-45)) {
  int diff = b->y() - (py+67+270-45);
  for(slotlist::iterator i=slots.begin();i!=slots.end();++i) {
   i->button->set_y(i->button->y()-diff);
   i->button->set_enabled((i->button->y()>=py+67 && i->button->y()<py+67+270));
   i->button->selected = (i->button==b?2:0);
  }
 }

 labels_update();
 return true;
}

void LoadGame_Window::labels_update() {
 if(bt_scroll_up) bt_scroll_up->set_disabled((slots.size()==0 || slots[0].button->y()>=py+67));
 if(bt_scroll_dn) bt_scroll_dn->set_disabled((slots.size()==0 || slots.back().button->y()<py+67+270));
}
