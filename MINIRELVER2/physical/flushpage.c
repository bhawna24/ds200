#include "../include/defs.h"

int FlushPage(int relNum)
{
 if(relNum<0 || relNum>MAXOPEN){

  return ErrorMsgs(REL_NUM_OUTBOUND );

 }else{
//checking whether the page in buffer is dirty or not
    if(page_buffer[relNum].dirty==true && page_buffer[relNum].pid!=0){

        char newSlotmap[SLOTMAPSIZE]={ 0 };

        char newPage[PAGESIZE]= {0};

        int offset=(page_buffer[relNum].pid-1)*PAGESIZE;

        unsigned int slotmap=page_buffer[relNum].p.slotmap;

        inttobytearray(slotmap,newSlotmap);

        memcpy(newPage,newSlotmap,SLOTMAPSIZE);

        memcpy(newPage+SLOTMAPSIZE,page_buffer[relNum].p.contents,PAGESIZE);

        if(fseek(relCat_buffer[relNum].relFile,offset,SEEK_SET)!=0)
            return ErrorMsgs(UNABLETOMAOVEFILEPOINTER);
       fwrite(newPage,PAGESIZE,1,relCat_buffer[relNum].relFile);
        fflush(relCat_buffer[relNum].relFile);

    }
     //setting the things undirty
     page_buffer[relNum].dirty=false;
     page_buffer[relNum].pid=0;
     page_buffer[relNum].p.slotmap=0;
     page_buffer[relNum].p.contents[0]='\0';
     return OK;
 }
}
