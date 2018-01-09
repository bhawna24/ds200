/*
 * This function find the Rid of next record matching the specific criteria
 *
 * GetNextRec from physical layer used
 *
 * return OK if record is found
 * else return NOTOK
 *
 *
*/


#include "../include/defs.h"

int FindRec(int relNum, Rid *startRid, Rid **foundRid, char **recPtr, char attrType,
            int attrSize, int attrOffset, char *valuePtr,int compOp){
 if(relNum<0 || relNum >MAXOPEN)
  return ErrorMsgs(REL_NUM_OUTBOUND);
    //Reading page with required pageid
 if(ReadPage(relNum,startRid->pid)!=OK)
  return NOTOK;
 *foundRid=NULL;
    float a,b;
    int x=0;
    char *str1,*str2;
    //Finding the next Rid of valid record and matching it with corresponding value
 while(GetNextRec(relNum,startRid,foundRid,recPtr)==OK){
     //Matching the records type and reading from recptr pointer according to that
  switch (attrType){
   case INTEGER://for integer datatype
            a=readintformbytearray(valuePtr,0);
          b=readintformbytearray(*recPtr,attrOffset);
          if(compNum(a,b,compOp))
           return OK;
          break;
   case FLOAT://for float datatype
           a=readfloatfrombytearray(valuePtr,0);
           b=readfloatfrombytearray(*recPtr,attrOffset);
          if(compNum(a,b,compOp))
           return OK;
          break;
   case STRING://for string datatype
          str1 = (char *) calloc(sizeof(char) * attrSize,sizeof(char));
          str2 = (char *) calloc(sizeof(char) * attrSize,sizeof(char));
          readstringfrombytearray(valuePtr,0,str1,attrSize);
          readstringfrombytearray(*recPtr,attrOffset,str2,attrSize);
          if(compString(str1,str2,compOp))
           return OK;
          break;
   default:
    return ErrorMsgs(INVALID_ATTRIBUTE_TYPE);
  }
   startRid=*foundRid;

 }
 return NOTOK;
}
