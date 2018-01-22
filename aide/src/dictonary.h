/* 
 * File:   dictonary.h
 * Author: nd
 *
 * Created on June 19, 2014, 4:34 PM
 */
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>

#include "helper.h"

#ifndef DICTONARY_H
#define	DICTONARY_H

class dictonary {
    public:
    struct word{                                            //base structure for dictonary word
        char *text;
        int length;
        int count;
        int passed;
        word *left;
        word *right;
    };

    int   wordSize;                                         //static size of struct word
    word *nodeStart,*nodeEnd;                               //pointers to linked list head/tail

    double  totalWords;                                     //statistic vars
    double  uniqueWords;
    double  loops;
    
    void    *nodeHash[27*27*27*27];                         //Hash array
    static const int DICTONARY_HASH_DEPTH=    3;            //Hash depth
    static const int DICTONARY_HASH_BASE =    27;           //hash width (alpha plus other)
    
    dictonary();                                            //Constructor
    dictonary(const dictonary& orig);
    virtual ~dictonary();                                   //Destructor
    
    word* newNode(char *,char);
    word *add(char *,char);
    void  fromFile(char*);
    void  print();
private:
    void setHashIndex(char*,char,word*);
    long loadRawFile(char *fileName,void **buffer);
    
};


#endif  /* dictonary.h */