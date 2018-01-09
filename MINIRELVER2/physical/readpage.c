/*
 * This function basically read data from data file
 *
 * FlushPage() for flushing the dirty page
 * */
#include "../include/defs.h"


int ReadPage(int relNum,short pid)
{
    if(pid<0 || pid>(relCat_buffer[relNum].numPgs+1)){
        return ErrorMsgs(PID_OUT_OF_BOUND);
    }

    if(relNum<0 || relNum>MAXOPEN){
        return ErrorMsgs(REL_NUM_OUTBOUND);
    }
    //if different page id is requested other than which is currently present in buffer
    if(page_buffer[relNum].pid!=pid){
        if(FlushPage(relNum)==NOTOK)
            return NOTOK;
        // If New page is Requested
        if(pid==relCat_buffer[relNum].numPgs+1){
            //setting fields for new buffer fileds for new page
            page_buffer[relNum].dirty=false;
            page_buffer[relNum].pid=pid;
            page_buffer[relNum].p.slotmap=0;
            page_buffer[relNum].p.contents[0]='/0';
            return OK;
        }
            //Reading old page
        else{
            char page[PAGESIZE];
            //if realtion is newly created
            if(pid==0)
                pid=1;
            //Setting offset
            int offset=(pid-1)*PAGESIZE;
            //Moving file pointer to desired location
            int x=relCat_buffer[relNum].relFile;

            if(fseek(relCat_buffer[relNum].relFile,offset,SEEK_SET)!=0)
                return ErrorMsgs(UNABLETOMAOVEFILEPOINTER);
            //Reading from desired loaction
            fread(page,PAGESIZE,1,relCat_buffer[relNum].relFile);
               // return ErrorMsgs(FILE_READ_ERROR);
            //setting up buffer value
            memcpy(page_buffer[relNum].p.contents,page+SLOTMAPSIZE,PAGESIZE-SLOTMAPSIZE);
            int slotmap=readintformbytearray(page,0);
            page_buffer[relNum].dirty=false;
            page_buffer[relNum].pid=pid;
            page_buffer[relNum].p.slotmap=slotmap;

            return OK;
        }
    }
    return OK;
}
