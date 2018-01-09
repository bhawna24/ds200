/*
 * load()
 * _________________________________________
 *
 *
 * This routine loads the specified relation,
 * which must already have been created, with data
 * from the specified file
 *
 * Arguments passed:
 * ---------------------------
 *  argv[0]      =   "load"
 *  argv[1]      =   relation name
 *  argv[2]      =   data file name
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
 *  RELNOEXIST
 *
 *
 *  ALGORITHM:
 *  ---------------------------------------------------------------------------------
 *  1.  Check if database is open or not
 *  2.  Open the relation file given in argv[1] and check that relation is empty
 *  3.  Open he data file and copy the contents to relation file record-by-record
 *
 *  Implementation notes:
 *  ---------------------------------------------------------------------------------
 *      Physical Layer: OpenRel(), InsertRec(), FindRelNum()
 *
 */


#include "../include/defs.h"


int Load (int argc, char** argv){

    if (!db_Open) {
        return ErrorMsgs(DB_NOT_OPEN);
    }

    int relNum=OpenRel(argv[1]);
    if(relNum==NOTOK){
        return ErrorMsgs(REL_NOT_EXIST);
    }
    relNum=FindRelNum(argv[1]);
    FILE *rel, *data;
    char page[PAGESIZE];
    int i;
    for(i=0;i<PAGESIZE;i++)
        page[i]=0;

    if(relCat_buffer[relNum].numRecs!=0){
        ErrorMsgs(RELATION_NOT_EMPTY);
    }

    data = fopen(argv[2],"rd");

    int recLength = relCat_buffer[relNum].recLength;
    int numAttrs = relCat_buffer[relNum].numAttrs;
    //int offset=0,code[numAttrs];

    char *new = (char *)calloc(recLength,sizeof(char));
    Duplicates=OK;
    while(fread(new, recLength,1, data)==1)
        if(InsertRec(relNum, new)!=OK)
            return NOTOK;

    Duplicates=NOTOK;

    CloseRel(relNum);
    return OK;
    fclose(rel);
}


