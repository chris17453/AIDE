/* 
 * File:   dictonary.cpp
 * Author: nd
 * 
 * Created on June 19, 2014, 4:34 PM
 */

#include "dictonary.h"

dictonary::dictonary(){
    int index;
    
    wordSize=sizeof(word);
    totalWords  =0;
    uniqueWords =0;
    loops       =0;
    
    
    for(index=0;index<27*27*27*27;index++) nodeHash[index]=NULL;
    nodeStart=this->newNode("!",1);                     //root element. //just anything to get it goin.
    nodeEnd  =this->newNode(".",1);                     //root element.
    
    nodeStart->right=nodeEnd;
    nodeStart->left=NULL;
    nodeEnd  ->left=nodeStart;
    nodeEnd  ->right=NULL;
   
    nodeHash[0]=nodeStart;                              //set default hash.
}
dictonary::~dictonary(){
    
}

long dictonary::loadRawFile(char *fileName,void **buffer){
    FILE *fp=fopen(fileName,"r+b");
    if(fp) {
        fseek(fp, 0L, SEEK_END);
        long file_size= ftell(fp);
        *buffer=malloc(file_size);
        fseek(fp, 0L, SEEK_SET);
        fread(*buffer,file_size,1,fp);
        fclose(fp);
        return file_size;
    }
    error_exit("Cannot open File");
    return 0;
}

    
void dictonary::setHashIndex(char *data,char len,word *node){
    int m=0;
    long final=0;

    int i=0;
    for(i=0;i<4;i++) {
        if(len>=i+1) {
            m=tolower(data[i]);
            if(m<'a' || m>'z') m=0; else { m-='a';  ++m; }
        }
        final=final*DICTONARY_HASH_BASE+m;
    }
    nodeHash[final]=node;
}

dictonary::word* dictonary::newNode(char *data,char len){
    word *newWord=(word*)malloc(wordSize);
    newWord->length =len;
    newWord->text   =strtolower(data);
    newWord->count  =1;
    newWord->passed =0;
    newWord->left=NULL;
    newWord->right=NULL;

    return newWord;
}

dictonary::word  *dictonary::add(char * data,char len){
    word *foundWord;
    word *newWord,*nodePath;
    int firstInZone=0;
    char *compare= strtolower(data);
    int m=0;
    int i=0;
    long final=0;
    
    for(i=0;i<4;i++) {
        if(len>=i+1) {
            m=compare[i];
            if(m<'a' || m>'z') m=0; else { m-='a';  ++m; }
        }
        final=final*DICTONARY_HASH_BASE+m;
    }

    if(NULL==nodeHash[final]) {
        while(NULL==nodeHash[final] && final>=0) final--;					//if exact hash is empty.. reverse till you get something... worst case you hit root.
        if(NULL==nodeHash[final])   nodePath=(word*)nodeStart;					//ok nothing worked out.. go with nodeStart...
        else                        nodePath=(word*)nodeHash[final];				//zone not poplated.. get closest zone above it
        firstInZone=-1;
    } else {
        nodePath=(word*)nodeHash[final];							//get exact hash zone
    }
    ++totalWords;

    foundWord=nodePath;
    while (NULL!=nodePath) {
        ++loops;
        if(nodePath->length==len) {
            if(memcmp(compare,nodePath->text, len)==0) {
                nodePath->count++;
                free(compare);
                return nodePath;
            }
        }
        nodePath=nodePath->right;
    }

    nodePath=foundWord;
    
    newWord=(word*)malloc(wordSize);
    newWord->length  =len;
    newWord->text    =compare;
    newWord->count   =1;
    newWord->passed  =0;
    newWord->left   =NULL;
    newWord->right  =NULL;


    while(NULL!=nodePath && memcmp(nodePath->text,newWord->text,len)<0){
        nodePath=nodePath->right;
        firstInZone=(firstInZone!=-1)?1:firstInZone;
    }

    if(NULL==nodePath) {        //its the end...
        word *left=nodeEnd;
        word *right=NULL;
        if(NULL!=nodeEnd->right) right=nodeEnd->right;

        if(NULL==right){
            newWord->right=NULL;
            newWord->left=nodeEnd;
            nodeEnd->right=newWord;
            nodeEnd          =newWord;
        } else {
            left->right   =nodeEnd;
            right->left  =nodeEnd;
            newWord->right=right;
            newWord->left=left;
        }
    } else {

        word *left=nodePath->left;
        word *right=nodePath;

        if(NULL==left) {
            nodePath->left=newWord;
            newWord->left=NULL;
            newWord->right=nodePath;
            nodeStart=newWord;
        } else {
            left->right=newWord;
            right->left=newWord;
            newWord->right=right;
            newWord->left=left;
        }
        ++uniqueWords;
    }

    if(1>firstInZone) this->setHashIndex(newWord->text,len,newWord);

    return newWord;
}

void dictonary::fromFile(char *fileName){
    long begin=0;
    long end=0;
    long len=0;
    long a=0;
    char compare;
    int index=0;
    char temp[500];
    
    long bufferSize =NULL;
    void *buffer    =NULL;
    
    bufferSize=this->loadRawFile(fileName,&buffer);          //load a file
    
    
    for(a=bufferSize;a!=0;--a) {
       compare=((char *)buffer)[index];
       if(!(compare>='A' && compare<='Z') && !(compare>='a' && compare<='z')){
            len=end-begin;
            memset(temp,0,1+len);
            if(len==0) {
                temp[0]=compare;
                temp[1]=0;
                this->add(temp,1);
            } else {
                memcpy2(temp, (char*)buffer+begin, len);
                this->add((char*)temp,(char)len);
            }
            begin=index+1;
            end=index;
        }
        ++index;
        ++end;
    }
    free(buffer);
}

void dictonary::print(){
    word *pos=nodeStart;
    int index=0;
    while (NULL!=pos) {
        printf("%d  - %s,Count: %d \r\n",index,pos->text,pos->count);
        pos=pos->right;
        index++;
    }
    printf("Total Words %f "    ,this->totalWords);
    printf("Unique Words %f "   ,this->uniqueWords);
    printf("Loops %f "          ,this->loops);
       
}
