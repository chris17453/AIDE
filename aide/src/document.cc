/* 
 * File:   document.cpp
 * Author: nd
 * 
 * Created on June 19, 2014, 5:49 PM
 */

#include "document.h"

document::document() {
    lines=0;
}

document::document(const document& orig) {
}

document::~document() {
}

void document::appendNode(int line,int column,void *objectBase,int type,bool capitol,bool uppercase){
    
    contentObject *object=(contentObject*)malloc(sizeof(struct contentObject));
    nodes++;
    object->baseObject  =objectBase;
    object->contentType =type;
    object->line        =line;
    object->column      =column;
   // object->page        =0;
   // object->x           =0;
   // object->y           =0;
    //object->width       =10;
    //object->height      =10;
    object->capitalized =capitol;
    object->uppercase   =uppercase;
    object->left        =NULL;
    object->right       =NULL;
    if(head==NULL) {
        head=object;
        
    } else if(tail==NULL){
        tail=object;
        head->right=tail;
        tail->left =head;
    } else {
        object->left=tail;
        tail->right=object;
        tail=object;
    }
}

void document::loadTextFile(char *fileName){
    void *buffer    =NULL;
    long fileSize   =0;
    
    FILE *fp=fopen(fileName,"r+b");
    if(fp) {
        fseek(fp, 0L, SEEK_END);
        fileSize= ftell(fp);
        buffer=malloc(fileSize);
        fseek(fp, 0L, SEEK_SET);
        fread(buffer,fileSize,1,fp);
        fclose(fp);
        
    } else {
        error_exit("Cannot open File");
        return;
    }
    
    
    long begin=0;
    long end=0;
    long len=0;
    long a=0;
    char compare;
    int index=0;
    char temp[50];
    int line=0,column=0;
    dictonary::word *word;
    
    for(a=fileSize;a!=0;--a) {
       compare=((char *)buffer)[index];
         
       bool capitol=(compare>='A' && compare<='Z');
       bool lower  =(compare>='a' && compare<='z');
       if(!capitol && !lower){
            len=end-begin;
            memset(temp,0,1+len);
            
            
            if(len!=0) {
                memcpy2(temp, (char*)buffer+begin, len);
                bool capitolized=false; 
                bool uppercase=true;
                for(int a=0;a<len;a++) if(temp[a]<'A' || temp[a]>'Z') uppercase=false;
                if(!uppercase && (temp[0]>='A' && temp[0]<='Z')) capitolized=true;
                
                word=this->dict.add((char*)temp,(char)len);
                this->appendNode(line,column-len,word,WORD,capitolized,uppercase);
            } 
            temp[0]=compare;
            temp[1]=0;

            word=this->dict.add(temp,1);
            this->appendNode(line,column-len,word,WORD,capitol,false);
            
            begin=index+1;
            end=index;
        }
        if(compare=='\n') {
           line++; 
           column=0; 
       }
       ++column;
        ++index;
        ++end;
    }
    lines=line;
    free(buffer);
}

void document::print(){
    contentObject *pos=head;
    //int index=0;
    while(NULL!=pos) {
        //++index;
        //if(index==500) return;
        if(pos->contentType==WORD) {
            dictonary::word* word=(dictonary::word*)pos->baseObject;
            if(pos->uppercase) {
                char *text=strtoupper(word->text); printf("%s",text); free(text); 
            } else 
            if(pos->capitalized) {
                if(word->length==1) printf("%c",toupper(word->text[0]));
                else                { char *text=strtolower(word->text); text[0]=toupper(text[0]); printf("%s",text); free(text); }
            } else {
                if(word->length==1) printf("%c",word->text[0]);
                else                printf("%s",word->text);
            }
        }
        pos=pos->right;
    }
    
}