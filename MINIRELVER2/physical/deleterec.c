/*
 * This method set the slotmap of passed Rid to zero i.e invalidating that record
 *
 * ReadPage() for reading the page
 * */
#include "../include/defs.h"

int DeleteRec(int relNum,Rid *recRid)
{
 if(relNum<0 || relNum >=MAXOPEN)
  return ErrorMsgs(REL_NUM_OUTBOUND);
 if(recRid==NULL)
  return ErrorMsgs(NULLPOINTEREXCEPTION);

 //Reading page with particular pageId
 int flag=ReadPage(relNum,recRid->pid);
 if(flag==OK){
  //setting up the buffers dirty
  page_buffer[relNum].dirty=true;
  page_buffer[relNum].p.slotmap=(page_buffer[relNum].p.slotmap & ~(1<<(32-recRid->slotnum)));
  relCat_buffer[relNum].numRecs=relCat_buffer[relNum].numRecs-1;
  relCat_buffer[relNum].dirty=true;
  return OK;
 }else{
  return NOTOK;
 }
}
