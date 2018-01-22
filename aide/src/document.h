/* 
 * File:   document.h
 * Author: nd
 *
 * Created on June 19, 2014, 5:49 PM
 */

#ifndef DOCUMENT_H
#define	DOCUMENT_H

#include "dictonary.h"


class document {
public:
    dictonary   dict;
    struct contentObject{
        //int x;
        //int y;
        //int width;
        //int height;
        //int page;
        int line;
        int column;
        char contentType;
        bool capitalized;
        bool uppercase;
        void *baseObject;
        contentObject *left;
        contentObject *right;
    };
    int nodes=0;
    int lines;
    enum  { WORD,Character,Event,Place,Time,Note };
    
    contentObject *head=NULL,*tail=NULL;
    
    document();
    document(const document& orig);
    virtual ~document();
    void loadTextFile(char *);                                                  //Load a plain text file
    void appendNode(int,int,void *,int,bool,bool);
    void print();                                                               //echo out document

    
private:

};

#endif	/* DOCUMENT_H */

