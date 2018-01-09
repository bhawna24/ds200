/*
 * THis method print the relation
 *
 * GetNextRec() from physical layer for iterating over each tuple
 * */

#include "../include/defs.h"


int Print(int argc, char **argv) {
    if (!db_Open) {
        return ErrorMsgs(DB_NOT_OPEN);
    }
    if(CloseCats()==NOTOK){
        return NOTOK;
    }
   if( OpenCats()==NOTOK){
       return NOTOK;
   }


    if (OpenRel(argv[1]) == NOTOK) {
        return NOTOK;
    }
    //finding the relation no. to be printed
    int relNum = FindRelNum(argv[1]);
    if (relNum == NOTOK)
        return ErrorMsgs(REL_NOT_EXIST);

    struct attrCat *list, *attrList = relCat_buffer[relNum].attrList;
    list = attrList;
    int tableRowLength = 2;

    if(relCat_buffer[relNum].numRecs==0){
        printf("Empty relation");
        return OK;
    }

    //Printing the header of the table
    printf("| ");
    while (list != NULL) {
        int width = list->type == STRING ? list->length : 100;
        printf("%*s | ", max(strlen(list->attr_Name), width), list->attr_Name);
        tableRowLength += (3 + max(strlen(list->attr_Name), width));
        list = list->next;
    }

    printUnderScores(tableRowLength - 1);

    Rid *foundRid, startRid = { 1, 0 };
    char *recPtr = (char *)malloc(relCat_buffer[relNum].recLength);
    int intval;
    float floatval;
    char string[20];
    //Printing records
    while (GetNextRec(relNum, &startRid, &foundRid, &recPtr) == OK) { //Fetch each record
        list = attrList;
        printf("| ");
        while (list != NULL) {
            int width = list->type == STRING ? list->length : 100;
            switch (list->type) {
                case INTEGER:
                    intval = readintformbytearray(recPtr, list->offset);
                    printf("%*d | ", max(strlen(list->attr_Name), width), intval);
                    break;
                case FLOAT:
                    floatval = readfloatfrombytearray(recPtr, list->offset);
                    printf("%*g | ", max(strlen(list->attr_Name), width), floatval);
                    break;
                case STRING:
                    readstringfrombytearray( recPtr, list->offset,string, list->length);
                    string[list->length] = '\0';      //For strings stored without '\0'
                    printf("%*s | ", max(strlen(list->attr_Name), list->length), string);
                    break;
            }
            list = list->next;
        }
        printUnderScores(tableRowLength - 1); //Printing a line to separate rows
        startRid = *foundRid;

    }

    free(recPtr);
    return OK; /* all's fine */
}


int max(int a, int b) {
    if(a<b)
        return a;
    else
        return b;
}



void printUnderScores(int count) {
    printf("\n");
    for(int i=1;i<=count;i++) {
        printf("_");
    }
    printf("\n");
}
