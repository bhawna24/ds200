
/*
 * This method close the relation which is currently opened in buffer
 * It flushes the page store in the page buffer
 * and the check whether its relation cache entries are dirty or not
 * if dirty then update them in relation catalog
 *
 * FlushPage() for flushing the buffer page
 *
 * */
 #include "../include/defs.h"

int CloseRel(int relNum)
{
    //Flushing the current page in buffer
    FlushPage(relNum);
    if(!(relCat_buffer->dirty))
        return OK;
    char *recPtr;
    Rid start={1,0};
    Rid *found;
    //Finding the corresponding Relation cahe entry
    if (FindRec(RELCAT_CACHE, &start, &found, &recPtr, STRING, RELNAME, 0,
                relCat_buffer[relNum].relName, EQ) == NOTOK){
        return ErrorMsgs(REL_NOT_EXIST);
    }else{
        inttobytearray(relCat_buffer[relNum].numRecs,recPtr+32);
        inttobytearray(relCat_buffer[relNum].numPgs,recPtr+36);
        //Writing updated record in Relation Cache
        WriteRec(RELCAT_CACHE,recPtr,found);
        //Flushing the updated page
        FlushPage(RELCAT_CACHE);
        close((int) relCat_buffer[relNum].relFile);
        buffer_in_use[relNum]=false;
        relCat_buffer[relNum].dirty=false;

        struct attrCat *attr_List=relCat_buffer[relNum].attrList;
        struct attrCat *temp=attr_List;

        return OK;
    }
}