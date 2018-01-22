/* 
 * File:   editorWidget.h
 * Author: nd
 *
 * Created on June 23, 2014, 4:27 PM
 */

#ifndef EDITORWIDGET_H
#define	EDITORWIDGET_H
#include    "editor.h"

#include    <gtkmm/application.h>
#include    <gtkmm/window.h>
#include    <gtkmm/scrollbar.h>
#include    <gtkmm/adjustment.h>
#include    <gtkmm.h>
#include    <iostream>

class editorWidget : public Gtk::Window {
    private:
        editor e;
        void on_horiz_scroll_value_changed();
        void on_vertical_scroll_value_changed();
         
    public:
        editorWidget();
        editorWidget(const editorWidget& orig);
        virtual ~editorWidget();

    protected:
        Gtk::Grid       *mainGrid=0;
        Gtk::Grid       *ideGrid=0;
        Gtk::Scrollbar  *horScroll=0;
        Gtk::Scrollbar  *verScroll=0;
        Glib::RefPtr<Gtk::Adjustment> adjv;
};


#endif	/* EDITORWIDGET_H */

