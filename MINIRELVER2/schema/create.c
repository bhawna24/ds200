

/*
 * Create()
 * _________________________________________
 *
 *
 * This routine creates a new relation with the specified name and attributes
 *
 * Arguments passed:
 * ---------------------------
 *  argv[0]      =   "create"
 *  argv[1]      =   relation name
 *  argv[2]      =   first attribute name
 *  argv[3]      =   first attribute format
 *      ...
 *  argv[argc-2] =   Nth attribute name
 *  argv[argc-1] =   Nth attribute format
 *  argv[argc]   =   NIL
 *
 * return
 * -----------------------
 *  OK: if successful
 *  NOTOK: otherwise
 *
 * Global Variables modified:
 * -------------------------
 *  <none>
 *
 * ERRORS REPORTED:
 * --------------------
 *  DB_NOT_OPEN
 *  INVALID_ATTR_TYPE
 *  MAX_STRING_EXCEEDED
 *  PAGE_OVERFLOW
 *
 *  ALGORITHM:
 *  ---------------------------------------------------------------------------------
 *  1.  Check for the errors
 *  2.  Prepare the argument list according to the parameters of Insert() Insert()
 *      For each attribute
 *      - add all the variable arguments for attribute catalog
 *      - check that record size doesnt exceed MAXRECORD
 *      - insert into attrCat relation through Insert()
 *  3.  Similarly, insert a new record in relCat
 *  4.  create a new file and setup the empty slot use map for the empty file
 *
 *  Implementation notes:
 *  ---------------------------------------------------------------------------------
 *      Physical Layer: OpenRel()
 *      Schema Layer:   Destroy()
 *      Algera Layer:   Insert()
 *
 */


#include "../include/defs.h"

void template(int index, char ***argv, char *relName, int *argc){

    struct attrCat *attrList = relCat_buffer[index].attrList;
    *argc = (2* relCat_buffer[index].numAttrs+2);

    *argv = (char**)calloc(*argc * sizeof(char *),sizeof(char*));
    (*argv)[0] = (char *)calloc(RELNAME* sizeof(char),sizeof(char*));
    strcpy((*argv)[0], "insert");
    (*argv)[1] = (char *) calloc(RELNAME * sizeof(char),sizeof(char*));
    strcpy((*argv)[1], relName);

    for(int i=2; attrList != NULL; i+=2){
        (*argv)[i] = (char *)calloc(RELNAME*sizeof(char),sizeof(char*));
        (*argv)[i+1] = (char *)calloc(RELNAME*sizeof(char),sizeof(char*));
        strcpy((*argv)[i], attrList->attr_Name);
        attrList = attrList->next;
    }
}


int Create(int argc, char **argv){

  /*  printf("\n");

    printf("%d \n",argc);
    fflush(stdout);
    for(int i=0;i<argc;i++)
        printf("%s\n",argv[i]);

    fflush(stdout);
*/    if(!db_Open)
        return ErrorMsgs(DB_NOT_OPEN);


    int offset, length, i;
    char type, attrName[RELNAME], relName[RELNAME], attrFormat[4];


    strcpy(relName, argv[1]);

    print_error=false;
    if(OpenRel(relName)==OK){
        print_error=true;
        return ErrorMsgs(RELATION_ALREADY_EXISTS);
    }
    print_error=true;


    int numAttrs;

    for(i= 2, numAttrs= 0, offset= 0;i<argc; i = i+2, numAttrs++){

        char **ACargv;
        int ACargc;
        template(ATTRCAT_CACHE, &ACargv, ATTRCAT, &ACargc);
        strncpy(attrName, argv[i], RELNAME);

        strcpy(attrFormat, argv[i + 1]);
        type = attrFormat[0];
        //printf("\n %s \n",&type);
        if (type != INTEGER && type != STRING && type != FLOAT) {
            print_error=false;
            deleteACEntries(relName);
            print_error=true;
            return ErrorMsgs(INVALID_ATTRIBUTE_TYPE);
        }

        length = getSize(attrFormat);

        if(length > 200){
            deleteACEntries(relName);
            return ErrorMsgs(T00_LONG_ARGUMENTS);
        }

        int j;

        for(j = 2; j < ACargc; j+=2){
            if (strcmp(ACargv[j], "offset") == 0)
                sprintf(ACargv[j + 1], "%d", offset);
            else
                if (strcmp(ACargv[j], "type") == 0)
                    sprintf(ACargv[j + 1], "%d", type);
                else
                    if (strcmp(ACargv[j], "length") == 0)
                        sprintf(ACargv[j + 1], "%d", length);
                    else
                        if (strcmp(ACargv[j], "attrName") == 0)
                            strcpy(ACargv[j + 1], attrName);
                        else
                            sprintf(ACargv[j + 1], "%s", relName);

        }
        offset =offset+length;

        if (offset > MAXRECORD) {
            char **argvDes = (char **) calloc(sizeof(char*) * 2,sizeof(char*));
            argvDes[0] = (char *) calloc(sizeof(char) * strlen("destroy"),sizeof(char*));
            argvDes[1] = (char *) calloc(sizeof(char) * strlen(relName),sizeof(char*));
            sprintf(argvDes[0], "%s", "destroy");
            sprintf(argvDes[1], "%s", relName);
            Destroy(2, (char **) argvDes);
            free(argvDes[0]);
            free(argvDes[1]);
            free(argvDes);
            return ErrorMsgs(PAGE_OVERFLOW);
        }
        Insert(ACargc, ACargv);
        freeMem(ACargv, ACargc);
    }



    char **RCargv;
    int RCargc;
    template(RELCAT_CACHE, &RCargv, RELCAT, &RCargc);

    //Fill the template
    int j, recsPerPg;
    recsPerPg = (MAXRECORD / offset) < 32 ? (MAXRECORD / offset) : 32;

    for (j = 2; j < RCargc; j += 2) {
        if (strcmp(RCargv[j], "recLength") == 0)
            sprintf(RCargv[j + 1], "%d", offset);
        else
            if (strcmp(RCargv[j], "recsPerPg") == 0)
                sprintf(RCargv[j + 1], "%d", recsPerPg);
            else
                if (strcmp(RCargv[j], "numAttrs") == 0)
                    sprintf(RCargv[j + 1], "%d", numAttrs);
                else
                    if (strcmp(RCargv[j], "numRecs") == 0)
                        sprintf(RCargv[j + 1], "%d", 0);
                    else
                        if (strcmp(RCargv[j], "numPgs") == 0)
                            sprintf(RCargv[j + 1], "%d", 1);
                        else
                            sprintf(RCargv[j + 1], "%s", relName);

    }
    Insert(RCargc, RCargv);

    freeMem(RCargv, RCargc);

    int fd = fopen(relName,"w+");
    char *slotMap = (char *) calloc((SLOTMAPSIZE) * sizeof(char),sizeof(char*));
    inttobytearray(0, slotMap);
    write(fd, slotMap, (SLOTMAPSIZE));
    close(fd);
    free(slotMap);

  /*  int x=FindRelNum(argv[1]);
    if(x!=NOTOK)
        CloseRel(x);
*/
    return OK;
}

int getSize(char *attrType ){
    int size=0;
    switch(attrType[0]){
        case INTEGER:
            size=sizeof(size);
            break;
        case FLOAT:
            size=sizeof(size);
            break;
        case STRING:
            size= findLength(attrType);
            break;
    }
    return size;
}

int findLength(char *type){
    char *ch;
    ch=(char *) malloc(4);
    strcpy(ch,type+1);
    return (atoi(ch));
}

void freeMem(char **args, int arraySize) {
    int i;
    for (i = 0; i < arraySize; ++i) {
        free(args[i]);
    }
    free(args);
}

void deleteACEntries(char *relName) {
    int deleteArgCount = 5;
    char **deleteArgs=(char **) malloc(deleteArgCount * sizeof(char *));
    int i=0;
    for (i = 0; i < deleteArgCount; i++)
        deleteArgs[i] = (char *) malloc(200);
    strcpy(deleteArgs[0], "delete");
    strcpy(deleteArgs[1], ATTRCAT);
    strcpy(deleteArgs[2], "relName");
    inttobytearray(EQ, deleteArgs[3]);
    strcpy(deleteArgs[4], relName);

    Delete(deleteArgCount, deleteArgs);
}
