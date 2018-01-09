/*
 * This funtion delete all records from relation which matches the
 * condition specified.
 *
 * FindRec() from physical layer to find the record according to condition
 *
 * */
#include "../include/defs.h"


int Delete (int argc,char **argv){
    if(!db_Open)
        ErrorMsgs(DB_NOT_OPEN);
    if(OpenRel(argv[1])!=OK)
        ErrorMsgs(REL_NOT_EXIST);
    int relNum=FindRelNum(argv[1]);
    boolean flag=false;
    struct attrCat* head;
    struct attrCat* found;
    head=relCat_buffer[relNum].attrList;
    //checking whether particular attribte exists or not.
    while(head!=NULL){
        if(strcmp(head->attr_Name,argv[2])==0){
            found=head;
            flag=true;
            break;
        }
        head=head->next;
    }
    if(!flag)
        ErrorMsgs(ATTR_NOT_EXIST);
    //reading matching value
    if(found->type==INTEGER){
       int intVal = atoi(argv[4]);
        inttobytearray(intVal, argv[4]);
    }else if(found->type==FLOAT){
        float floatVal = atof(argv[4]);
        floattobytearray(floatVal, argv[4]);
    }
    Rid startRid = { 1, 0 }, *foundRid;
    char *recPtr;
    //Finding the matching tuple
    while(FindRec(relNum,&startRid,&foundRid,&recPtr,found->type,found->length,
                  found->offset,argv[4],readintformbytearray(argv[3],0))==OK){
        DeleteRec(relNum,foundRid);
        startRid=(*foundRid);
        free(foundRid);
    }
    return OK;
}



