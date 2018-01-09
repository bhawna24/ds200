/*
 * This method insert the record in relation which is open in buffer
 * it basically write in page buffer of that relation
 * */

#include "../include/defs.h"

int InsertRec(int relNum,char* recPtr)
{
    if(relNum<0 || relNum>=MAXOPEN)
        ErrorMsgs(REL_NUM_OUTBOUND);
    if(recPtr==NULL)
        ErrorMsgs(NULLPOINTEREXCEPTION);

    int recLength=relCat_buffer[relNum].recLength;
    char *record;
    Rid *next,current={0,0};

//Checking for duplicates tuples iterationg over whole file
    while(GetNextRec(relNum,&current,&next,&record)==OK && Duplicates==NOTOK){
        if(isSameRecord(recPtr,next,recLength)==OK)
            return ErrorMsgs(DUPLICATES_TUPPLE_FOUND);
        else{
            current=*next;
            free(next);
        }
    }


    Rid startRid={1,0};
    Rid foundRid;
//finding free slot for insertion
    getFreeSlot(relNum,startRid,&foundRid);
    //reading required page
    ReadPage(relNum, foundRid.pid);
    //setting offset from where we have to start writing
    int offset=(foundRid.slotnum-1)*recLength;
//writing data byte by byte
    for(int i=0,j=offset;i<recLength;++i,j++)
        page_buffer[relNum].p.contents[j]=recPtr[i];
//validating the slotmap of that record
    page_buffer[relNum].p.slotmap=page_buffer[relNum].p.slotmap | (1<<(32-foundRid.slotnum));
    page_buffer[relNum].dirty=true;
//increasing the record count
    relCat_buffer[relNum].numRecs=relCat_buffer[relNum].numRecs+1;
    relCat_buffer[relNum].dirty=true;

    if(foundRid.pid>relCat_buffer[relNum].numPgs)
        relCat_buffer[relNum].numPgs=foundRid.pid;

    return OK;
}
//useful in founding the free slot where data can be inserted
int getFreeSlot(int relNum, Rid startRid, Rid *foundRid){

    int recPerPg=relCat_buffer[relNum].recsPerPg;
    int numpgs=relCat_buffer[relNum].numPgs;
    int flag=NOTOK;
    Rid curRid=nextRid(startRid,recPerPg,getLastRid(relNum));
    Rid prevRid=curRid;

    while(curRid.pid<=numpgs && flag!=OK){
        ReadPage(relNum,curRid.pid);
            prevRid=curRid;
        while(prevRid.slotnum<=curRid.slotnum){
            if(!(page_buffer[relNum].p.slotmap & (1<<(32-curRid.slotnum)))){
                flag=OK;
                break;
            }
            prevRid=curRid;
            curRid=nextRid(prevRid,recPerPg,getLastRid(relNum));
        }
        if(flag==OK)
            break;
    }

    (*foundRid)=curRid;
    return OK;
}

//checking whether two records are same or not
int isSameRecord(char *rec1,char *rec2,int size){

    for(int i=0;i<size;i++){
        if(rec1[i]!=rec2[i]){
            return NOTOK;
        }
    }
    return OK;
}

