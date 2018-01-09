/*This method is called form Opendb()
 * it loads relcat and attrcat in buffer
 *
 * */

#include "../include/defs.h"

int OpenCats(){
    char* recPtr;
    int relCatNumRecs, relCatNumPgs;
    int i, rtrn;

    Rid startRid={1,0}, *foundRid;

    buffer_in_use[0]=buffer_in_use[1]=true; //catcahe
    for(int i=2;i<MAXOPEN;i++)
        buffer_in_use[i]=false;

    for (i = 0; i < MAXOPEN; i++)
        cache_time[i] = 0;    //cachetime
//loading relcat cache in buffer
    strcpy(relCat_buffer[0].relName, RELCAT);
    relCat_buffer[0].recLength = 40;
    relCat_buffer[0].recsPerPg = 12;
    relCat_buffer[0].numAttrs = 6;

    relCat_buffer[0].numRecs = 2;
    relCat_buffer[0].numPgs = 1;

    relCat_buffer[0].recatRid.pid = 1;
    relCat_buffer[0].recatRid.slotnum = 1;
    relCat_buffer[0].relFile = fopen(RELCAT,"r+");
    relCat_buffer[0].dirty = false;
    relCat_buffer[0].attrList = createAttrListRC();

    rtrn = FindRec(0, &startRid, &foundRid, &recPtr, STRING, RELNAME, 0, RELCAT, EQ);
    if(rtrn == NOTOK){
        return ErrorMsgs(NO_CATALOG_FOUND );
    }

    relCatNumRecs = readintformbytearray(recPtr, 32);
    relCatNumPgs = readintformbytearray(recPtr, 36);

    relCat_buffer[0].numRecs = relCatNumRecs;
    relCat_buffer[0].numPgs = relCatNumPgs;
//Loading attrcat in buffer
    strcpy(relCat_buffer[1].relName, ATTRCAT);
    relCat_buffer[1].recLength = 52;
    relCat_buffer[1].recsPerPg = 9;
    relCat_buffer[1].numAttrs = 5;

    relCat_buffer[1].numRecs = 11;
    relCat_buffer[1].numPgs = 2;
    relCat_buffer[1].recatRid.pid = 1;
    relCat_buffer[1].recatRid.slotnum = 2;
    relCat_buffer[1].relFile = (FILE *) fopen(ATTRCAT,"r+");
    relCat_buffer[1].dirty = false;
    relCat_buffer[1].attrList = createAttrListAC();

    rtrn = FindRec(0, &startRid, &foundRid, &recPtr, STRING, RELNAME, 0, ATTRCAT, EQ);
    if(rtrn == NOTOK){
        return ErrorMsgs(NO_CATALOG_FOUND );
    }


    relCatNumRecs = readintformbytearray(recPtr, 32);
    relCatNumPgs = readintformbytearray(recPtr, 36);

    relCat_buffer[1].numRecs = relCatNumRecs;
    relCat_buffer[1].numPgs = relCatNumPgs;

    return OK;
}

struct attrCat* newNode( int offset, int length, int type, char attrName[], char relName[], struct attrCat* next)
{
    struct attrCat* node = malloc(sizeof(struct attrCat));

    node->offset=offset;
    node->length=length;
    node->type=type;
    strcpy(node->attr_Name,attrName);
    strcpy(node->relName,relName);
    node->next=next;

    return node;
}

struct attrCat* createAttrListAC(){
    struct attrCat *temp;

    temp = newNode(32,20,STRING,"relName",ATTRCAT,NULL);
    temp = newNode(12,20,STRING,"attrName",ATTRCAT,temp);
    temp = newNode(8,4,INTEGER,"type",ATTRCAT,temp);
    temp = newNode(4,4,INTEGER,"length",ATTRCAT,temp);
    temp = newNode(0,4,INTEGER,"offset",ATTRCAT,temp);

    return temp;
}

struct attrCat* createAttrListRC(){
    struct attrCat *temp;

    temp = newNode(36,4,INTEGER,"numPgs",RELCAT,NULL);
    temp = newNode(32,4,INTEGER,"numRecs",RELCAT,temp);
    temp = newNode(28,4,INTEGER,"numAttrs",RELCAT,temp);
    temp = newNode(24,4,INTEGER,"recsPerPg",RELCAT,temp);
    temp = newNode(20,4,INTEGER,"recLength",RELCAT,temp);
    temp = newNode(0,20,STRING,"relName",RELCAT,temp);

    return temp;
}