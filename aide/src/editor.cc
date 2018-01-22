
#include <ctime>
#include <cmath>
#include <cairomm/context.h>
#include <glibmm/main.h>
#include "editor.h"

editor::editor()
{
  Glib::signal_timeout().connect( sigc::mem_fun(*this, &editor::on_timeout), 1000 );

  #ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
  //Connect the signal handler if it isn't already a virtual method override:
  signal_draw().connect(sigc::mem_fun(*this, &Clock::on_draw), false);
  #endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
}

editor::~editor(){
}
bool editor::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    int index=0;
    int lineHeight=20;
    double x=0,y=0;
    int text_width;
    int text_height;
    char compare;
        

    //Set Background of window.....
    cr->set_source_rgb(18.0/255.0,30.0/255.0,49.0/255.0);
    draw_rectangle(cr,0,0,width,height);
    cr->set_source_rgb(0.5, 1.0, 0.5);

    document::contentObject  *pos=doc.head;
  
    
    Pango::FontDescription font;
    font.set_family("Monospaced");
    font.set_weight(Pango::WEIGHT_NORMAL);
    //font.set_size((13);

    Cairo::TextExtents    extents;
    
    while(NULL!=pos){   
        if(pos->line>=masterLine) break;
        pos=pos->right;
    }
    
   while(NULL!=pos){
    
     if(index>2000) break;
        dictonary::word* word=(dictonary::word*)pos->baseObject;
        char *text=((dictonary::word*)pos->baseObject)->text;

        compare=((char *)text)[0];
       
    
        cr->get_text_extents(text,extents);	
    
   
        Glib::RefPtr<Pango::Layout> layout = create_pango_layout(text);
        layout->set_font_description(font);
        layout->get_pixel_size(text_width, text_height);
    
        cr->move_to(x,y);
        layout->show_in_cairo_context(cr);

        if(word->length==1 && compare=='\n') {
            x=0;
            y+=lineHeight;
        }  else {
            x+=text_width;
        }
        pos=pos->right;
        index++;
    }
  return true;
}

void editor::draw_rectangle(const Cairo::RefPtr<Cairo::Context>& cr,int x,int y,int width, int height){
  cr->rectangle(x, y, width, height);
  cr->fill();
}

void editor::draw_text(const Cairo::RefPtr<Cairo::Context>& cr,int left,int top,char *text){
  Pango::FontDescription font;

  font.set_family("Monospace");
  font.set_weight(Pango::WEIGHT_NORMAL);

  Glib::RefPtr<Pango::Layout> layout = create_pango_layout(text);

  layout->set_font_description(font);

  int text_width;
  int text_height;

  layout->get_pixel_size(text_width, text_height);

  cr->move_to(left,top);

  layout->show_in_cairo_context(cr);
}

bool editor::on_timeout(){
    // force our program to redraw the entire clock.
    Glib::RefPtr<Gdk::Window> win = get_window();
    if (win)
    {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    return true;
}

void editor::load(char *fileName){
    doc.loadTextFile(fileName);
    doc.dict.print();
   
}