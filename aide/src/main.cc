
#include "editorWidget.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include <iostream>

int main(int argc, char** argv){
   Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "com.datamoderated.aide");

   editorWidget e;
   e.show();
   app->run(e);

}  

