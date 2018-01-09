/************************************************************
   This file contains the error constants that are
   used by the routine that reports error messages.
   As you find error conditions to report, 
   make additions to this file. 
************************************************************/

int ErrorMsgs(int error);

#define REL_NOT_EXIST  101   /* Relation does not exist */
#define ATTR_NOT_EXIST 102   /* Attribute does not exist */
#define REL_NUM_OUTBOUND 103
#define NULLPOINTEREXCEPTION 104
#define UNABLETOMAOVEFILEPOINTER 105
#define UNABLETOWRITEPROPERLY    106
#define PID_OUT_OF_BOUND   107
#define FILE_READ_ERROR    108
#define NULLARGUMENT       109
#define RECORD_POINTER_ARRAY_MISMATCH 110
#define INVALID_COMPARATOR_OPERATOR  111
#define INVALID_ATTRIBUTE_TYPE 112
#define DUPLICATES_TUPPLE_FOUND 113
#define NO_ATTRIBUTE_FOUND 114
#define DB_NOT_CLOSE 115
#define DB_ALREADY_EXISTS 116
#define DB_NOT_OPEN 117
#define PROB_CLOSING_CATS 118
#define PROB_CREATE_CATS 119
#define DB_NOT_EXIST 120
#define METADATA_SECURITY 121
#define UNABLE_T0_DELETE_FILE 122
#define INSUFFICIENT_ARGUMENTS 123
#define DUPLICATE_ATTRIBUTE 124
#define UNABLE_TO_OPEN_NEWLY_CREATED_RELATION 125
#define NO_CATALOG_FOUND 126
#define RELATION_ALREADY_EXISTS 127
#define DATABASE_DOES_NOT_EXISTS 128
#define RELATION_NOT_EMPTY 129
#define PAGE_OVERFLOW 131
#define T00_LONG_ARGUMENTS 132

