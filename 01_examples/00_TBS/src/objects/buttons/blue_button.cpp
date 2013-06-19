#include "blue_button.h"
#include "..\..\Engine\utils.h"

Blue_Button::Blue_Button(string text, functor* f, Loader* loader, int x, int y, int wd, int pr):
 Button(f), _width(wd), surf(0), surf_img(0) {
  _x=x;
  _y=y;
  _priority=pr;

  set_states(
   loader->load_sprite("res\\img\\GUI\\buttons\\blue_button\\blue_button_up.sprite"),
   loader->load_sprite("res\\img\\GUI\\buttons\\blue_button\\blue_button_over.sprite"),
   loader->load_sprite("res\\img\\GUI\\buttons\\blue_button\\blue_button_up.sprite"),
   loader->load_sprite("res\\img\\GUI\\buttons\\blue_button\\blue_button_off.sprite")
  );
  label = Text(loader->load_font("Calibri",15), text);
  SDL_Color c; c.r=c.g=c.b=255;
  label.set_color(c);

  redraw();
 }
Blue_Button::~Blue_Button() {
 if(surf_img) {
  if(surf_img->img()) glDeleteTextures(1, surf_img->img());
  delete surf_img;
 }
 if(surf) SDL_FreeSurface(surf);
}

void Blue_Button::update(Input* input) {
 if(surf==0) redraw();
 if(surf==0) return;
 int mx = input->mouse_x();
 int my = input->mouse_y();
 int ns = 0;
 if(disabled) ns=3;
 else {
  if(!input->paused() && !input->mouse_eaten(0)) {
   bool intersects = ((mx > _x && mx < _x + surf->w) && (my > _y && my < _y + surf->h));
   if(intersects && pixel_perfect_intersection) intersects = (get_color_a(surf,mx-_x,my-_y)!=0);
   //check pixel-perfect only if mouse is inside

   if(intersects) {
    input->mouse_eat(0);
    if(input->mouse_release(1, true) && func!=0) (*func)();
    ns = (input->mouse_hold(1, true)?2:1);
   }
  }
 }
 bool rd = (current_state!=ns);
 current_state = ns;
 if(rd) redraw();
}

void Blue_Button::update_label() {
 if(label.img()) {
  label.set_x((surf->w - label.img()->w())/2);
  label.set_y((surf->h - label.img()->h())/2);
 }
}

void Blue_Button::redraw() {
 if(states[current_state].bitmap(0)==0
 || states[current_state].bitmap(1)==0
 || states[current_state].bitmap(2)==0) return;
 int w = _width;
 if(w==0) {
  const SDL_Surface* m = (label.img()?label.img()->bmp():0);
  if(m) w=m->w;
  m = states[current_state].bitmap(0);
  if(m) w=m->w;
  m=states[current_state].bitmap(2);
  if(m) w=m->w;
 }
 if(surf==0 || surf->w!=w) {
  if(surf) {SDL_FreeSurface(surf); surf=0;}
  surf = create_surface(SDL_SWSURFACE, w, states[current_state].h());
 }
 if(surf==0) return; //something fails
 SDL_FillRect(surf, 0, SDL_MapRGBA(surf->format, 0, 0, 0, 255));
 SDL_Flip(surf);
 int full_w = w;
 //draw left piece
 SDL_Surface* fr = states[current_state].bitmap(0);
 SDL_SetAlpha(fr, 0, 0);
 SDL_Rect dstrect;
 dstrect.x = dstrect.y = 0;
 SDL_BlitSurface(fr, 0, surf, &dstrect);
 dstrect.x+=fr->w;
 w-=fr->w+states[current_state].bitmap(2)->w;
 //draw center
 fr=states[current_state].bitmap(1);
 SDL_SetAlpha(fr, 0, 0);
 while(w>0&&fr->w>0) {
  SDL_BlitSurface(fr, 0, surf, &dstrect);
  dstrect.x+=fr->w;
  w-=fr->w;
 }
 //draw right piece
 fr=states[current_state].bitmap(2);
 SDL_SetAlpha(fr, 0, 0);
 dstrect.x = full_w-fr->w;
 SDL_BlitSurface(fr, 0, surf, &dstrect);
 //now text label
 update_label();
 SDL_Flip(surf);
 if(surf_img) {
  glDeleteTextures(1, surf_img->img());
  delete surf_img;
  surf_img = 0;
 }
 surf_img = surface_to_texture(surf, false);
}

void Blue_Button::draw(SDL_Surface* s) {
 if(surf_img==0) redraw();
 if(surf_img==0) return;
 surf_img->draw(_x,_y,s);
 label.draw(_x+label.x(),_y+label.y(),s);
}
