/*
 *This method destroy particular relation and also delete its corresponding relcat and attrcat values
 * */

#include "../include/defs.h"

int Destroy (int argc,char **argv)
{
    if(!db_Open)
        return ErrorMsgs(DB_NOT_OPEN);
    if(remove(argv[1])!=0)
        return ErrorMsgs(UNABLE_T0_DELETE_FILE);
    //Preparing arguments for destroy
    char **arguments;
    arguments=malloc(sizeof(char*) *5);
    int i=0;
    while(i<5){
        arguments[i]=malloc(sizeof(char) *20);
        i++;
    }

    strcpy(arguments[0],"delete");
    strcpy(arguments[1],RELCAT);
    strcpy(arguments[2],"relName");
    inttobytearray(EQ,arguments[3]);
    strcpy(arguments[4],argv[1]);
    //deleting relcat entries
    Delete(5,arguments);

    strcpy(arguments[1],ATTRCAT);
    //deleting attrcat values
    Delete(5,arguments);
    //freeing the buffer
    i=FindRelNum(arguments[1]);
    if(i==OK)
        buffer_in_use[i]=false;
    i=0;
    //freeing memory
    while(i<5){
        free(arguments[i]);
        i++;
    }
    free(arguments);

    return OK;
}


