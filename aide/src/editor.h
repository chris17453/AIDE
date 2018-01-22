#ifndef EDITOR_H
#define EDITOR_H

#include <gtkmm/drawingarea.h>
#include "document.h"


class editor : public Gtk::DrawingArea
{
public:
    editor();
    virtual   ~editor();
    void      load(char *);

    int masterLine=50;
    document doc;
    protected:
  //Override default signal handler:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    void draw_text(const Cairo::RefPtr<Cairo::Context>&,int,int,char*);
    void draw_rectangle(const Cairo::RefPtr<Cairo::Context>&,int,int,int,int);

  bool on_timeout();

  
};

#endif // EDITOR_H