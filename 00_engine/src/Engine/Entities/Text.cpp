#include "Text.h"
#include "../utils.h"

namespace Engine { namespace Entities {

//{ CONSTRUCTION/DESTRUCTION

Text::Text(Controller* c, TTF_Font* fnt, string txt, unsigned int w, SDL_Color* clr, int xp, int yp, int pr):
 Entity(c), _antialiasing(true), _font(fnt), _label(0), _text(txt), _width(w)
{
 if(!clr) _color.r=_color.g=_color.b=255;
 else _color = *clr;

 _x = xp;
 _y = yp;
 _priority = pr;
}

Text::Text(const Text& t): Entity(t.controller) { clone(t); }

Text& Text::operator=(const Text& t) {
 if(this!=&t) clone(t);
 return* this;
}

Text::~Text() {
 free_surface();
}

//}

//{ PRIVATE METHODS

void Text::clone(const Text& t) {
 //copy Entity values
 _x = t._x;
 _y = t._y;
 _priority = t._priority;
 _destroy = t._destroy;
 _visible = t._visible;
 _enabled = t._enabled;

 clear_queue();
 children = t.children;

 //copy Text values
 _antialiasing = t._antialiasing;
 _color = t._color;
 _font = t._font;
 _text = t._text;
 _width = t._width;

 //reset pointer
 free_surface();
 refresh();
}

SDL_Surface* Text::draw_text(string txt) {
 return draw_text(txt, _font, _color, _antialiasing);
}

SDL_Surface* Text::draw_text(string txt, TTF_Font* fnt, SDL_Color clr, bool aa) {
 return (aa?TTF_RenderUTF8_Blended(fnt, txt.c_str(), clr)
           :TTF_RenderUTF8_Solid(fnt, txt.c_str(), clr));
}

void Text::free_surface() {
 if(_label) {
  if(_label->texture())
   glDeleteTextures(1, _label->texture());

  delete _label;
  _label = 0;
 }
}

void Text::refresh() {
 if(_font==0) return;
 free_surface();
 SDL_Surface* _surf = 0;
 if(_width>0) {
  string txt = _text;
  vector<string> parts;
  vector<int> y_pos;
  string part = "";
  string word = "";
  int final_h = 0;
  int final_w = 0;
  bool modifer = false;
  for(unsigned int i=0; i<txt.length(); ++i) {
   char c = txt[i];
   if(c=='\\' && !modifer) {modifer=true; continue;}
   string ns = part+(part!=""?" ":"")+word;
   if(modifer) {
    modifer=false;
    bool cont = true;
    switch(c) {
     case 'n':
      int w, h;
      TTF_SizeUTF8(_font, ns.c_str(), &w, &h);
      if((unsigned int)w<_width) {
       part=ns;
       word="";
      } else {
       TTF_SizeUTF8(_font, part.c_str(), &w, &h);
      }
      parts.push_back(part);
      y_pos.push_back(final_h);
      part=word;
      word="";
      final_h+=h;
      if(w>final_w) final_w=w;
     break;
     default: cont=false; //the character will be added to string as usual, but slash-modifer will be ignored
    }
    if(cont) continue;
   }
   if(txt[i]==' ') {
    int w, h;
    TTF_SizeUTF8(_font, ns.c_str(), &w, &h);
    if((unsigned int)w>=_width) {
     TTF_SizeUTF8(_font, part.c_str(), &w, &h);
     parts.push_back(part);
     y_pos.push_back(final_h);
     part=word;
     word="";
     final_h+=h;
     if(w>final_w) final_w=w;
    } else {
     part=ns;
     word="";
    }
   } else word+=c;
  }
  if(word!=""||part!="") {
   string ns = part+(part!=""?" ":"")+word;
   int w, h;
   TTF_SizeUTF8(_font, ns.c_str(), &w, &h);
   if((unsigned int)w<_width) {
    part=ns;
    word="";
   } else {
    TTF_SizeUTF8(_font, part.c_str(), &w, &h);
   }
   parts.push_back(part);
   y_pos.push_back(final_h);
   part=word;
   word="";
   final_h+=h;
   if(w>final_w) final_w=w;
   if(part!="") {
    parts.push_back(part);
    y_pos.push_back(final_h);
    int w, h;
    TTF_SizeUTF8(_font, part.c_str(), &w, &h);
    final_h+=h;
    if(w>final_w) final_w=w;
   }
  }


  //now draw it out
  _surf = create_surface(final_w, final_h);
  if(_surf==0) throw string("Unable to create a new surface to complete a difficult text label.");
  SDL_Rect dstrect;
  dstrect.x = 0;
  dstrect.y = 0;
  for(unsigned int i=0; i<parts.size(); ++i) {
   dstrect.y = y_pos[i];
   SDL_Surface* srf = draw_text(parts[i]);
   if(srf) {
    SDL_SetSurfaceBlendMode(srf, SDL_BLENDMODE_NONE);
    SDL_BlitSurface(srf, NULL, _surf, &dstrect);
    SDL_FreeSurface(srf);
   }
  }
  //SDL_Flip(_surf);
 } else {
  _surf = draw_text(_text);
 }
 if(_surf) _label = surface_to_texture(_surf);
}

//}

//{ PUBLIC METHODS

void Text::redraw(int sx, int sy) {
 if(_label==0) refresh();
 if(_label==0) return;
 draw_frame(*_label, sx+_x, sy+_y);
}

//}

//{ SETTERS

void Text::set_antialiasing(bool aa) {
 if(_antialiasing!=aa) {
  _antialiasing=aa;
  refresh();
 }
}

void Text::set_color(SDL_Color& clr) {
 if(clr.r!=_color.r || clr.g!=_color.g || clr.b!=_color.b) {
  _color=clr;
  refresh();
 }
}

void Text::set_font(TTF_Font* fnt) {
 if(fnt!=0 && fnt!=_font) {
  _font=fnt;
  refresh();
 }
}

void Text::set_text(string txt) {
 if(txt!=_text) {
  _text=txt;
  refresh();
 }
}

void Text::set_width(unsigned int w) {
 if(_width!=w) {
  _width=w;
  refresh();
 }
}

//}

} }
