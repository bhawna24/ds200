#include "../include/defs.h"

/*
 * This method implements the select command which create
 * new relation with the tuples matching according to the
 * selection criteria.
 *
 * Create() function is used to create new relation in which matching tuples will be loaded
 *
 * FindRec() from physical layer used to find the matching tuples
 *
 * */

int Select (int argc,char **argv){

    int operator;
    memcpy(&operator,argv[4],2);

    if(operator==GT)
        operator=LT;
    else if(operator==LT)
        operator=GT;
    else if(operator=GEQ)
        operator=LEQ;
    else if(operator==LEQ)
        operator=GEQ;

    if(!db_Open)
        ErrorMsgs(DB_NOT_OPEN);
    if(OpenRel(argv[2])==NOTOK)
        ErrorMsgs(REL_NOT_EXIST);

// Preparing attribute for Create() function
    int oldRelNum=FindRelNum(argv[2]);
    char **argumentList;
    int noAttrs=relCat_buffer[oldRelNum].numAttrs;
    argumentList=malloc(sizeof(char*)*((noAttrs+1)*2));
    argumentList[0]=malloc(sizeof(char*)*RELNAME);
    argumentList[1]=malloc(sizeof(char*)*RELNAME);
    strcpy(argumentList[0],"create");
    strcpy(argumentList[1],argv[1]);
    for(int i=2;i<(noAttrs+1)*2;i=i+2){
        argumentList[i]=malloc(sizeof(char*)*RELNAME);
        argumentList[i+1]=malloc(sizeof(char*)*4);
    }

    struct attrCat* head;
    head=relCat_buffer[oldRelNum].attrList;
    int count=2;
    while(head!=NULL){
        strcpy(argumentList[count],head->attr_Name);
        if(head->type==INTEGER){
            strcpy(argumentList[count+1],"i");
        }else if(head->type==FLOAT){
            strcpy(argumentList[count+1],"f");
        }else{
            sprintf(argumentList[count + 1], "s%d", head->length);
        }
         count+=2;
        head=head->next;
    }

    //checking whether the specific attribute exits or not
    head=relCat_buffer[oldRelNum].attrList;
    boolean flag=false;
    while(head!=NULL){
        if(strcmp(head->attr_Name,argv[3])==0){
            flag=true;
            break;
        }
        head=head->next;
    }
    if(!flag)
        ErrorMsgs(ATTR_NOT_EXIST);
//Creating the result relation
    if(Create((noAttrs+1)*2,argumentList)==NOTOK){
        for(int i=0;i<(noAttrs+1)*2;i++){
            free(argumentList[i]);
        }
        free(argumentList);
        return NOTOK;
    }
    //Freeing the memory
    for(int i=0;i<(noAttrs+1)*2-1;i++){
        free(argumentList[i]);
    }
    free(argumentList);


    if(head->type==INTEGER){
        int value=atoi(argv[5]);
        inttobytearray(value,argv[5]);
    }else if(head->type==FLOAT){
        float value=atof(argv[5]);
        floattobytearray(value,argv[5]);
    }

    if(OpenRel(argv[1])==NOTOK)
        ErrorMsgs(UNABLE_TO_OPEN_NEWLY_CREATED_RELATION);
//loading new relation in buffer
   OpenRel(argv[2]);
    oldRelNum=FindRelNum(argv[2]);

    int newRelnum=FindRelNum(argv[1]);
    Rid startRid = { 1, 0 }, *foundRid;
    char *recPtr;
   //Finding the tuples and then inserting in the new relation
    while (FindRec(oldRelNum,&startRid,&foundRid,&recPtr,head->type,head->length,
                head->offset,argv[5],operator)==OK){
        InsertRec(newRelnum,recPtr);
        startRid=(*foundRid);
        free(foundRid);
    }
    return OK;
}


