/*This method project attributes from source relation to the result relation
 * it first create result relation and then insert particular attribute of source relation
 *
 * Create() for creating new result relation
 * InsertRec() for inserting reords
 * */


#include "../include/defs.h"

int Project (int argc,char **argv){
    if(!db_Open)
        ErrorMsgs(DB_NOT_OPEN);
    if(OpenRel(argv[2])==NOTOK)
        ErrorMsgs(REL_NOT_EXIST);
    int sourceRelnum=FindRelNum(argv[2]);
    struct attrCat *attrList=relCat_buffer[sourceRelnum].attrList;
   //No. of attribute required for create function
    int numAttr=(argc-3)*2+2;
    char **arguments=(char **)malloc(numAttr*sizeof(char *));
    arguments[0]=malloc(sizeof(char*)*RELNAME);
    arguments[1]=malloc(sizeof(char*)*RELNAME);
    strcpy(arguments[0],"create");
    strcpy(arguments[1],argv[1]);
    struct attrCat **newattr=(struct attrCat**)malloc(sizeof(struct attrCat*)*(argc-3));
    int i,j;

//Preparing arguments for create function
    for( i=2,j=3;i<=(argc-3)*2;i+=2,j+=1){
        arguments[j]=(char *)malloc(sizeof(char)*RELNAME);
        struct attrCat *head=relCat_buffer[sourceRelnum].attrList;
        boolean flag=false;
        while(head!=NULL){
            if(strcmp(head->attr_Name,argv[j])==0){
                flag=true;
                break;
            }
            head=head->next;
        }
        if(!flag)
            ErrorMsgs(ATTR_NOT_EXIST);

        newattr[j-3]=head;
        arguments[i]=malloc(sizeof(char*)*RELNAME);
        strcpy(arguments[i],head->attr_Name);
        arguments[i+1]=(char *)calloc(4,sizeof(char));
        if(head->type==INTEGER || head->type==FLOAT)
            arguments[i+1][0]=head->type;
        else
            sprintf(arguments[i+1],"s%d",head->length);

    }
    //Creating result relation
    int ret=Create(numAttr,arguments);
//Freeing memory
    for(int i=0;i<numAttr;i++){
        free(arguments[i]);
    }
    free(arguments);

    if(ret==NOTOK)
        return NOTOK;

    if(OpenRel(argv[1])==NOTOK)
        return ErrorMsgs(UNABLE_TO_OPEN_NEWLY_CREATED_RELATION);

    int newRelnum=FindRelNum(argv[1]);
    Rid startRid={0,0},*foundRid;
    char *recPtr;
//Iterating through each tuple and inserting the required tuples
    while(GetNextRec(sourceRelnum,&startRid,&foundRid,&recPtr)==OK){
        char *output=(char *)calloc(relCat_buffer[newRelnum].recLength,sizeof(char));
        int offset=0;
        for(int i=0;i<j-3;i++){
            memcpy(output+offset,recPtr+newattr[i]->offset,newattr[i]->length);
            offset+=newattr[i]->length;
        }
        InsertRec(newRelnum,output);
        startRid=(*foundRid);
        free(foundRid);
    }
    return OK;
}

