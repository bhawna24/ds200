/*
 * this method write record int page buffer byte by byte
 * it first read the required page in buffer and then write data in it
 *
 * ReadPage() for reading required page
 * */
#include "../include/defs.h"

int WriteRec(int relNum, char *recPtr, Rid *recRid)
{
 if(relNum<0 || relNum>=MAXOPEN)
   ErrorMsgs(REL_NUM_OUTBOUND);

 if(recPtr==NULL || recRid==NULL)
   ErrorMsgs(NULLARGUMENT);
//Reading the required page
 ReadPage(relNum,recRid->pid);

 int recLength=relCat_buffer[relNum].recLength;
    //setting the required offset
 int offset=(recRid->slotnum-1)*recLength;
    //Writing byte by byte
    for(int i=0,j=offset;i<recLength;i++,j++){
        page_buffer[relNum].p.contents[j]=recPtr[i];
    }
    
    page_buffer[relNum].dirty=true;
    return OK;
}

