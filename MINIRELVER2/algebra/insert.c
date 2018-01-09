/*
 *
 * _________________________________________
 * This routine implements the relational insert command, adding the tuple given in argv to the named relation
 *
 *  ALGORITHM:
 *  ---------------------------------------------------------------------------------
 *      1. Check for possible errors
 *      2. Create a char Array of size recLength
 *      3. Read each value from argv and convert it to a byte array
 *      4. Check if any attribute is repeated in the arguments using "hashing"
 *      5. Copy the byte array to correct location (using offset from attrList)
 *      6. Call InsertRec()
 *
 *  ---------------------------------------------------------------------------------
 *      Physical Layer: OpenRel(), InsertRec()
 *
 */


#include "../include/defs.h"


int Insert (int argc,char **argv)
{
    if(!db_Open)
        ErrorMsgs(DB_NOT_OPEN);
    int relNum=OpenRel(argv[1]);
    if(relNum==NOTOK)
        return NOTOK;
    relNum=FindRelNum(argv[1]);
    if(relCat_buffer[relNum].numAttrs!=(argc-2)/2)
        ErrorMsgs(INSUFFICIENT_ARGUMENTS);

    //checking for attribute dublicates
    boolean flag=false;
    for(int i=2;i<argc;i=i+2){
        for(int j=i+2;j<argc;j=j+2){
            if(strcmp(argv[i],argv[j])==0){
                flag=true;
                break;
            }
        }
    }
    if(flag)
        ErrorMsgs(DUPLICATE_ATTRIBUTE);

    char *recPtr = (char *)calloc(relCat_buffer[relNum].recLength, sizeof(char));
    struct attrCat *attr = NULL;
//Adding value to record pointer
    for(int i=2;i<argc;i=i+2){
        attr=getAttribute(relCat_buffer[relNum].attrList,argv[i]);
        if(attr==NULL)
            ErrorMsgs(ATTR_NOT_EXIST);
        char *nptr;
        int intvalue;
        float floatvalue;
        if(attr->type==INTEGER){
            intvalue = strtol(argv[i + 1], &nptr, 10);
            inttobytearray(intvalue,recPtr+attr->offset);
        }else if(attr->type==FLOAT){
            floatvalue=strtof(argv[i + 1], &nptr);
            floattobytearray(floatvalue,recPtr+attr->offset);
        }else if(attr->type==STRING){
            strncpy(recPtr + attr->offset, argv[i + 1], attr->length);
        }else{
            break;
        }
    }
//Inserting record pointed by record pointer
     int x= InsertRec(relNum, recPtr);
    free(recPtr);
    return x;
}


struct attrCat* getAttribute(struct attrCat* list,char *attribute){
    while(list!=NULL){
        if(strcmp(attribute,list->attr_Name)==0) {
            break;
        }
        list=list->next;
    }
    return list;
}