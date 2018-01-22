/* 
 * File:   editorWidget.cc
 * Author: nd
 * 
 * Created on June 23, 2014, 4:27 PM
 */

#include "editorWidget.h"

editorWidget::editorWidget()  {
   //char * fileName     ="C:\\Downloads\\kjv.txt"; 
   //char * fileName     ="/cygdrive/c/Downloads/kjv.txt"; 
   //char * fileName     ="/home/nd/kjv.txt";
   char * fileName     ="/home/nd/House of Suns - Alastair Reynolds.txt";
   e.load(fileName);

   Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
   refBuilder->add_from_file("ide.glade");
   
      
  
  
  refBuilder->get_widget("mainGrid"        , mainGrid);
  refBuilder->get_widget("ideGrid"         , ideGrid);
  refBuilder->get_widget("verticalScroll"  , verScroll);
  
  this->set_has_resize_grip(true);
      
  if(ideGrid){
      
      mainGrid->set_halign(Gtk::ALIGN_FILL);
      mainGrid->set_valign(Gtk::ALIGN_FILL);
      mainGrid->set_hexpand(true);
      mainGrid->set_vexpand(true);
      mainGrid->set_size_request(400,400);

      
      ideGrid->set_halign(Gtk::ALIGN_FILL);
      ideGrid->set_valign(Gtk::ALIGN_FILL);
      ideGrid->set_hexpand(true);
      ideGrid->set_vexpand(true);
      ideGrid->set_size_request(400,400);

      e.set_size_request(600,600);
      e.set_valign(Gtk::ALIGN_FILL);
      e.set_vexpand(true);
      
     
        adjv=adjv->create(0.0, 0.0, (double)e.doc.lines, 0.1, 1.0, 1.0);
  
        
      verScroll->set_adjustment(adjv);
      verScroll->signal_value_changed().connect(sigc::mem_fun(*this, &editorWidget::on_vertical_scroll_value_changed));
    
      e.show();
      ideGrid->attach(e, 0, 0, 1, 1);
      ideGrid->show();
      mainGrid->show();
      this->add(*mainGrid);
  }
      //e.show();
      
  
        
}



void editorWidget::on_vertical_scroll_value_changed(){
    e.masterLine=verScroll->get_value();
    e.queue_draw();
}

editorWidget::editorWidget(const editorWidget& orig) {
}

editorWidget::~editorWidget() {
}

