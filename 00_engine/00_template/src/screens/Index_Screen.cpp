#include "Index_Screen.h"
#include "../Engine/Controller.h"
#include "../Engine/Input.h"
#include "../Engine/Resources.h"
#include "../Engine/Data/Frame.h"
#include "../Engine/Data/String_Table.h"
#include "../Engine/Entities/Button.h"
#include "../Engine/Entities/Sprite.h"
using Engine::Input;
using Engine::Resources;
using Engine::Data::Frame;
using Engine::Data::String_Table;
using Engine::Entities::Sprite;

Index_Screen::Index_Screen(Controller* controller): Screen(controller) {
 Frame* f = Resources::load_texture("res/img/GUI/Index_Screen/background.png");
 add_entity(new Sprite(controller, *f));
 add_button(336, 416, String_Table::translate["exit_game"], new Functor<Index_Screen>(this, &Index_Screen::fnc_exit));
 add_button(336, 280, String_Table::translate["translate"], new Functor<Index_Screen>(this, &Index_Screen::fnc_translate));
}

Button* Index_Screen::add_button(int x, int y, string text, functor* f, int pr) {
 ///creating unique designed button in run-time
 Button* b = new Button(controller);
 //provide images for up, over, pressed & disabled states (respectively)
 b->set_states(Resources::make_sprite("res/img/GUI/Index_Screen/button.png"),
               Resources::make_sprite("res/img/GUI/Index_Screen/button_over.png"),
               Resources::make_sprite("res/img/GUI/Index_Screen/button_pressed.png"),
               Resources::make_sprite("res/img/GUI/Index_Screen/button_pressed.png"));
 SDL_Color c;
 c.r=c.g=c.b=255;
 b->set_label(c, Resources::load_font("Tahoma", 14), text); //use white Tahoma 14
 b->set_x(x);
 b->set_y(y);
 if(f) b->set_func(f); //attach function to button's press event
 //now set priority and add object to queue
 b->set_priority(pr);
 add_entity(b);
 return b;
}

void Index_Screen::fnc_exit() {
 controller->stop_loop();
}

void Index_Screen::fnc_translate() {
 controller->set_option("language", (controller->get_option("language")=="Russian"?"English":"Russian")); //swap it
 controller->save_options();
 controller->restart_loop(false);
}

void Index_Screen::update_after_queue(int x, int y) {
 if(Input::quit() || Input::key_release(SDLK_ESCAPE)) controller->stop_loop();
}
