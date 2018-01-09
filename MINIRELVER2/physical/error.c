
#include "../include/defs.h"

int ErrorMsgs(int error)
{
    if(!print_error)
        return NOTOK;
 printf("\nError:    %d    ",error);
 switch (error) {
     case RELATION_NOT_EMPTY:
         printf("RELATION NOT EMPTY");
         break;
     case REL_NOT_EXIST:
         printf("RELATION  DOES NOT EXISTS");
         break;
     case ATTR_NOT_EXIST:
         printf("ATTRIBUTE DOES NOT EXISTS");
         break;
     case REL_NUM_OUTBOUND:
         printf("RELATION NO. OUT OF BOUND");
         break;
     case UNABLETOWRITEPROPERLY:
         printf("UNABLE TO WRITE TO FILE");
         break;
     case UNABLETOMAOVEFILEPOINTER:
         printf("UNABLE TO MOVE FILE POINTER.. ERROR IN FILE POINTER");
         break;
     case NULLPOINTEREXCEPTION:
         printf("NULL POINTER EXCEPTION");
         break;
     case PID_OUT_OF_BOUND:
         printf("PAGE ID OUT OF BOUND");
         break;
     case FILE_READ_ERROR:
         printf("ERROR IN FILE READING");
         break;
     case NULLARGUMENT:
         printf("NULL ARGUMENT PASSED");
         break;
     case RECORD_POINTER_ARRAY_MISMATCH:
         printf("RECORD POINTER MISMATCH...");
         break;
     case INVALID_COMPARATOR_OPERATOR:
         printf("INVALID COMPARATOR OPERATOR");
         break;
     case INVALID_ATTRIBUTE_TYPE:
         printf("INVALID ATTRIBUTE TYPE");
         break;
     case DUPLICATES_TUPPLE_FOUND:
         printf("DUPLICATES TUPPLE FOUND");
         break;
     case NO_ATTRIBUTE_FOUND:
         printf("N0 ATTRIBUTE FOUND");
         break;
     case DB_NOT_CLOSE:
         printf("DATABASE NOT CLOSED");
         break;
     case DB_ALREADY_EXISTS:
         printf("DATABASE ALREADY EXISTS");
         break;
     case DB_NOT_OPEN:
         printf("DATABASE NOT OPEN");
         break;
     case PROB_CLOSING_CATS:
         printf("ERROR IN CLOSING CATALOGS");
         break;
     case PROB_CREATE_CATS:
         printf("ERROR IN CREATING CATALOGS");
         break;
     case DB_NOT_EXIST:
         printf("DATABASE DOES NOT EXISTS");
         break;
     case METADATA_SECURITY:
         printf("DO NOT PLAY WITH METADATA ");
         break;
     case UNABLE_T0_DELETE_FILE:
         printf("UNABLE TO DELETE RELATION");
         break;
     case INSUFFICIENT_ARGUMENTS:
         printf("INSUFFICIENT ARGUMENTS PASSED");
         break;
     case DUPLICATE_ATTRIBUTE:
         printf("DUPLICATE ATTRIBUTE FOUND");
         break;
     case UNABLE_TO_OPEN_NEWLY_CREATED_RELATION:
         printf("PROBLEM IN OPENING NEWLY CREATED RELATION");
         break;
     case NO_CATALOG_FOUND:
         printf("NO METADATA EXISTS");
         break;
     case RELATION_ALREADY_EXISTS:
         printf("RELATION ALREADY EXISTS");
         break;
     case DATABASE_DOES_NOT_EXISTS:
         printf("DATABASE DOES NOT EXITS");
         break;
     case T00_LONG_ARGUMENTS:
         printf("TOO LONG ARGUMENTS");
         break;
 }
    printf("\n");
    fflush(stdout);
 return NOTOK;
}
