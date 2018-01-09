

#include "../include/defs.h"

int GetNextRec( int relNum,Rid *startRid, Rid **foundRid, char **recPtr)
{
 *recPtr=NULL;
 *foundRid=NULL;
 int recPerPages=relCat_buffer[relNum].recsPerPg;
 Rid lastRid=getLastRid(relNum);
 Rid current=nextRid(*startRid,recPerPages,lastRid);
 boolean flag=false;
 Rid previous=current;
//int numrecs=relCat_buffer[relNum].numRecs;

    //iterating over all pages staring from page id of start Rid
 while(current.pid<=relCat_buffer[relNum].numPgs && flag==false){
     if(current.pid==0)
        break;
  ReadPage(relNum,current.pid);
     //Iterating over whole page
  while(current.slotnum >= previous.slotnum ){
    //checking for valid Rid
       if(page_buffer[relNum].p.slotmap & (1<<(32-current.slotnum))){
        *foundRid=(Rid *) malloc(sizeof(Rid));
        **foundRid=current;
        *recPtr=page_buffer[relNum].p.contents + relCat_buffer[relNum].recLength*(current.slotnum-1);
        flag=true;
        break;
       }
      int x=page_buffer[relNum].p.slotmap;
      int y=(1<<(32-current.slotnum));
       previous=current;
       current=nextRid(current,recPerPages,lastRid);
       if(current.slotnum==0){
        break;
       }
      }
     }
     if(flag)
      return OK;
     else
      return NOTOK;
}

//For getting nextRid useful in case of page change
Rid nextRid(Rid startRid,int recPerPages,Rid lastRid){
    Rid next={0,0};
    if(startRid.pid==lastRid.pid && startRid.slotnum==lastRid.slotnum)
        return next;
    else if(startRid.slotnum==recPerPages){
    next.slotnum=1;
    next.pid=startRid.pid+1;
     }else{
      next.slotnum=startRid.slotnum+1;
       if(startRid.pid==0) {
       next.pid =1;
        }else {
        next.pid = startRid.pid;
       }
      }
 return next;
}

//calculating last Rid useful in parsing.. upto howmany rid we should go
Rid getLastRid(int relNum) {
 int numRecs=relCat_buffer[relNum].numRecs;
 int recPerPg=relCat_buffer[relNum].recsPerPg;
 Rid last;
    if(recPerPg==0) {
        last.pid = 0;
    }else {
        last.pid = numRecs / recPerPg + 1;
    }
    if(recPerPg==0){
        last.slotnum=0;
    }else {
        last.slotnum = numRecs % recPerPg + 1;
    }
 return last;
}