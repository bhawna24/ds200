/*
 * This method open the relation passed in relName
 * it basically search for empty slot in buffer and if it is not available then
 * LRU is used for the replacement
 * it
 * */
#include "../include/defs.h"

int OpenRel(char* relName)
{
    //Checking whether realtion is already open or not
 for(int i=0;i<MAXOPEN;i++){
  if(buffer_in_use[i] && (compString(relName,relCat_buffer[i].relName,EQ)) ){
      cache_time[i]=++cache_current_time;
   return OK;
  }
 }
    Rid startRid,*foundRid;
    startRid.slotnum=0;
    startRid.pid=1;
    char* array;
    int index;
    //Finding whether the realtion exists or not by checking in relation catalog
    //If exits then allocate buffer using LRU
    if(FindRec(RELCAT_CACHE,&startRid,&foundRid,&array,'s',RELNAME,0,relName,EQ)==NOTOK) {
        return ErrorMsgs(REL_NOT_EXIST);
    }else{
        boolean  flag=false;
        //Checking for free buffer
        for(int i=2;i<MAXOPEN;i++){
            if(!buffer_in_use[i]){
                index=i;
                flag=true;
                break;
            }
        }
        //LRU algorithm for replacement in buffer
        if(!flag){
            index=2;
            int min_time=cache_time[2];
            for(int i=3;i<MAXOPEN;i++){
                if(min_time>cache_time[i]){
                    index=i;
                    min_time=cache_time[i];
                }
            }
            CloseRel(index);
        }
        //loading relation cache values from relation cache
        buffer_in_use[index]=true;
        cache_time[index]=++cache_current_time;
        strcpy(relCat_buffer[index].relName,relName);
        relCat_buffer[index].recLength=readintformbytearray(array,20);
        relCat_buffer[index].recsPerPg=readintformbytearray(array,24);
        relCat_buffer[index].numAttrs=readintformbytearray(array,28);
        relCat_buffer[index].numRecs=readintformbytearray(array,32);
        relCat_buffer[index].numPgs=readintformbytearray(array,36);
        relCat_buffer[index].recatRid=*foundRid;
        relCat_buffer[index].dirty=false;
        int x=fopen(relName,"r+");
        relCat_buffer[index].relFile=x;



        startRid.pid=1;
        startRid.slotnum=0;
        boolean first_flag=false;
        //creating attribute list from Attribute catalog file
        if(FindRec(ATTRCAT_CACHE, &startRid, &foundRid, &array, 's', RELNAME, 32,
                   relName, EQ)==NOTOK){
            ErrorMsgs(NO_ATTRIBUTE_FOUND);
        }else{
            struct attrCat *Node,*temp;

            Node=malloc(sizeof(struct attrCat));
            if(!first_flag){
                relCat_buffer[index].attrList=Node;
                temp=Node;
                first_flag=true;
            }else{
                temp->next=Node;
                temp=Node;
            }
            temp->offset=readintformbytearray(array,0);
            temp->length=readintformbytearray(array,4);
            temp->type=readintformbytearray(array,8);
            readstringfrombytearray(array,12,temp->attr_Name,20);
            readstringfrombytearray(array,32,temp->relName,20);
            temp->next=NULL;
            startRid=*foundRid;
            free(foundRid);
            //Creating attribute list
            while(FindRec(ATTRCAT_CACHE, &startRid, &foundRid, &array, 's', RELNAME, 32,
                          relName, EQ)==OK){
                Node=malloc(sizeof(struct attrCat));
                temp->next=Node;
                temp=Node;
                temp->offset=readintformbytearray(array,0);
                temp->length=readintformbytearray(array,4);
                temp->type=readintformbytearray(array,8);
                readstringfrombytearray(array,12,temp->attr_Name,20);
                readstringfrombytearray(array,32,temp->relName,20);
                temp->next=NULL;
                startRid=*foundRid;
                free(foundRid);
            }
        }

        return OK;
    }
 }
