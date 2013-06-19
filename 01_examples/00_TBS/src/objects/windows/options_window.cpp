#include "..\..\Engine\utils.h"
#include "options_window.h"
#include <windows.h>

Options_Window::Options_Window(Game* g, Loader* l, int pr, bool nosave):
 Window(g,l,0,0,pr), no_restart(nosave) {
  tx_language=0;
  sc_language=0;
  sw_restart=0;
  bt_apply=bt_cancel=0;
  load();
 }

Options_Window::~Options_Window() {};

void Options_Window::fnc_apply() {
 bool updated = false;
 if(sc_language&&!letters_equal(game->option("language"),sc_language->selected())) {game->set_option("language", sc_language->selected()); updated=true;}
 bool restart = (updated&&sw_restart&&sw_restart->selected());
 if(updated) game->save_options();
 if(restart) game->restart();
 disappear();
}
void Options_Window::fnc_cancel() { disappear(); }

void Options_Window::find_languages() {
 HANDLE hFind = INVALID_HANDLE_VALUE;
 WIN32_FIND_DATA ffd;
 hFind = FindFirstFile("res\\txt\\*", &ffd);
 if(INVALID_HANDLE_VALUE == hFind) return;
 int cnt = 0;
 int ind = 0;
 do {
  if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
   string key = ffd.cFileName;
   if(key=="."||key=="..") continue;
   string loc = "lng"+key;
   sc_language->push(key, String_Table::translate[loc]);
   if(letters_equal(game->option("language"),key)) ind=cnt;
   ++cnt;
  }
 } while(FindNextFile(hFind, &ffd) != 0);
 sc_language->select(ind);

 DWORD dwError = GetLastError();
 if(dwError != ERROR_NO_MORE_FILES) /*fuck*/;
 FindClose(hFind);
}

void Options_Window::load() {
 int sw = game->w();
 int sh = game->h();
 Image* img = new Image(*loader->load_texture("res\\img\\GUI\\message_box.png"));
 int pw = img->w();
 int ph = img->h();
 int px = (sw - pw)/2;
 int py = (sh - ph)/2;
 img->set_x(px);
 img->set_y(py);
 add_object(img);

 SDL_Color c; c.r=c.g=c.b=255;
 add_object(tx_language = new Text(loader->load_font("Tahoma",16), String_Table::translate["mm_opt_language"], 0, c, px+10, py+10, 2));
 add_object(sc_language = new Options_Scroller(loader, pw/2-10-32, px+10, py+34, 2));
 find_languages();

 //buttons
 int by = py+ph-50+6;
 add_object(bt_apply = new Blue_Button(String_Table::translate["mm_opt_apply"], new Functor<Options_Window>(this, &Options_Window::fnc_apply), loader, px+10, by, 120, 2));
 add_object(bt_cancel = new Blue_Button(String_Table::translate["mm_opt_cancel"], new Functor<Options_Window>(this, &Options_Window::fnc_cancel), loader, px+pw-120-10, by, 120, 2));
 add_object(sw_restart = new Switcher(new Text(loader->load_font("Tahoma",12), "", 0, c, 17, -1, 3), String_Table::translate["mm_opt_rightnow"], String_Table::translate["mm_opt_relaunch"], !no_restart, px+11, by-21, 2));
 sw_restart->set_icon(
  loader->load_sprite("res\\img\\GUI\\buttons\\switcher\\up.sprite"),
  loader->load_sprite("res\\img\\GUI\\buttons\\switcher\\over.sprite"),
  loader->load_sprite("res\\img\\GUI\\buttons\\switcher\\press.sprite"),
  loader->load_sprite("res\\img\\GUI\\buttons\\switcher\\off.sprite")
 );
 if(no_restart) sw_restart->set_disabled(true);
}

void Options_Window::update() {
 if(_destroy||input==0) return;
 input->unpause();
 update_queue();
 input->pause();
}

void Options_Window::update(Input* _input) {
 input = _input;
 update();
 if(input->key_release(SDLK_ESCAPE, true)) disappear();
 if(_destroy) input->unpause(); //in case when the object was destroyed inside this function
}
