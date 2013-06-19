#include "text.h"

namespace Engine { namespace Objects {

/*CONSTRUCTORS & DESTRUCTOR*/

Text::Text(TTF_Font* fnt, string txt, int wdth, SDL_Color clr, int x, int y, int pr): Object(x,y,pr), _font(fnt), _text(txt), _color(clr), _image(0), _antialiased(true), _width(wdth) {
 if(_width<0) _width=0;
 redraw();
}

Text::Text(const Text& t) { clone(t); }

Text& Text::operator=(const Text& t) {
 if(this!=&t) clone(t);
 return* this;
}

Text::~Text() {
 free_surface();
};

/*PRIVATE METHODS*/

void Text::redraw() {
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
      if(w<_width) {
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
    if(w>=_width) {
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
   if(w<_width) {
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
  _surf = create_surface(SDL_SWSURFACE, final_w, final_h);
  if(_surf==0) throw string("Failed creating new surface while drawed difficult text label.");
  SDL_Rect dstrect;
  dstrect.x = 0;
  dstrect.y = 0;
  for(unsigned int i=0; i<parts.size(); ++i) {
   dstrect.y = y_pos[i];
   SDL_Surface* srf = draw_text(parts[i]);
   if(srf) {
    SDL_SetAlpha(srf, 0, 0);
    SDL_BlitSurface(srf, 0, _surf, &dstrect);
    SDL_FreeSurface(srf);
   }
  }
  SDL_Flip(_surf);
 } else {
  _surf = draw_text(_text);
 }
 if(_surf) _image = surface_to_texture(_surf, false);
}

void Text::free_surface() {
 if(_image) {
  if(_image->img()) {
   glDeleteTextures(1, _image->img());
   _image->set_img(0);
  }
  if(_image->bmp()) {
   SDL_FreeSurface(_image->bmp());
   _image->set_bmp(0);
  }
  delete _image;
  _image = 0;
 }
}

void Text::clone(const Text& t) {
 //copy Object
 _x = t._x;
 _y = t._y;
 _priority = t._priority;
 _destroy = t._destroy;
 _visible = t._visible;
 _enabled = t._enabled;
 //copy Text
 _font = t._font;
 _text = t._text;
 _color = t._color;
 _antialiased = t._antialiased;
 _width = t._width;

 //reset pointer
 free_surface();
 redraw();
}

SDL_Surface* Text::draw_text(string txt) {
 return draw_text(txt, _font, _color, _antialiased);
}

SDL_Surface* Text::draw_text(string txt, TTF_Font* fnt, SDL_Color clr, bool aa) {
 return (aa?TTF_RenderUTF8_Blended(fnt, txt.c_str(), clr)
           :TTF_RenderUTF8_Solid(fnt, txt.c_str(), clr));
}

/*PUBLIC METHODS*/

void Text::draw(SDL_Surface* surface) {
 if(_image==0) redraw();
 if(_image==0) return;
 _image->draw(_x,_y,surface);
}

void Text::draw(int x, int y, SDL_Surface* surface) {
 if(_image==0) redraw();
 if(_image==0) return;
 _image->draw(x,y,surface);
}

/*SETTERS*/

void Text::set_font(TTF_Font* fnt) {
 if(fnt!=0 && fnt!=_font) {
  _font=fnt;
  redraw();
 }
}

void Text::set_text(string txt) {
 if(txt!=_text) {
  _text=txt;
  redraw();
 }
}

void Text::set_color(SDL_Color& clr) {
 if(clr.r!=_color.r || clr.g!=_color.g || clr.b!=_color.b) {
  _color=clr;
  redraw();
 }
}

void Text::set_antialias(bool aa) {
 if(_antialiased!=aa) {
  _antialiased=aa;
  redraw();
 }
}

void Text::set_width(int w) {
 if(w<0) w=0; //0 - no width, more - have width, smaller - equals to 0
 if(_width!=w) {
  _width=w;
  redraw();
 }
}

} }
