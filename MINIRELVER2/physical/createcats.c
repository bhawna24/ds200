/*
 * This method create realtion catalogs it is called by createdb method
 * and create Relation catalog and Attribute catalog files
 *
 * */



#include "../include/defs.h"


int CreateCats(){
    if(createRelCat()== OK && createAttrCat()== OK)
        return OK;
    else
        return NOTOK;
}


int createRelCat(){
    FILE *file;
    char page[PAGESIZE];
    for(int i=0;i<PAGESIZE;i++)
        page[i]=0;

    file = fopen(RELCAT, "w");

    //Setting two staring slotmap as used for relation cache table entry and attribute cahe table entry
    //It is predefined
    inttobytearray(0xC0000000,page);
    strncpy(page+SLOTMAPSIZE , RELCAT , 6);

    inttobytearray(40, page+SLOTMAPSIZE+20);
    inttobytearray(12, page+SLOTMAPSIZE+24);
    inttobytearray(6, page+SLOTMAPSIZE+28);
    inttobytearray(2, page+SLOTMAPSIZE+32);
    inttobytearray(1, page+SLOTMAPSIZE+36);

    strncpy(page+40+SLOTMAPSIZE , ATTRCAT, 7);

    inttobytearray(52, page+SLOTMAPSIZE+20+40);
    inttobytearray(9, page+SLOTMAPSIZE+24+40);
    inttobytearray(5, page+SLOTMAPSIZE+28+40);
    inttobytearray(11, page+SLOTMAPSIZE+32+40);
    inttobytearray(2, page+SLOTMAPSIZE+36+40);

    int x=fwrite(page, 1, PAGESIZE, file);

    fclose(file);
    if(x!=PAGESIZE)
        return NOTOK;
    else
        return OK;
}

int createAttrCat(){
    FILE *file;
    char page[PAGESIZE*2];

    for(int i=0;i<PAGESIZE*2;i++)
        page[i]=0;


    file=fopen(ATTRCAT,"w");
    //Setting 11 staring slotmap as used for relation cache table attributes  and attribute cahe table attributes
    //It is predefined
    inttobytearray(0xFF800000,page);

    inttobytearray(0, page+0+SLOTMAPSIZE);
    inttobytearray(20, page+4+SLOTMAPSIZE);
    inttobytearray(STRING, page+8+SLOTMAPSIZE);/**********check***********/
    strncpy(page+12+SLOTMAPSIZE, "relName", 7);
    strncpy(page+32+SLOTMAPSIZE, RELCAT, 6);

    inttobytearray(20, page+0+52+SLOTMAPSIZE);
    inttobytearray(4, page+4+52+SLOTMAPSIZE);
    inttobytearray(INTEGER, page+8+52+SLOTMAPSIZE);
    strncpy(page+12+52+SLOTMAPSIZE, "recLength", 9);
    strncpy(page+32+52+SLOTMAPSIZE, RELCAT, 6);

    inttobytearray(24, page+0+52*2+SLOTMAPSIZE);
    inttobytearray(4, page+4+52*2+SLOTMAPSIZE);
    inttobytearray(INTEGER, page+8+52*2+SLOTMAPSIZE);
    strncpy(page+12+52*2+SLOTMAPSIZE, "recsPerPg", 9);
    strncpy(page+32+52*2+SLOTMAPSIZE, RELCAT, 6);

    inttobytearray(28, page+0+52*3+SLOTMAPSIZE);
    inttobytearray(4, page+4+52*3+SLOTMAPSIZE);
    inttobytearray(INTEGER, page+8+52*3+SLOTMAPSIZE);
    strncpy(page+12+52*3+SLOTMAPSIZE, "numAttrs", 8);
    strncpy(page+32+52*3+SLOTMAPSIZE, RELCAT, 6);

    inttobytearray(32, page+0+52*4+SLOTMAPSIZE);
    inttobytearray(4, page+4+52*4+SLOTMAPSIZE);
    inttobytearray(INTEGER, page+8+52*4+SLOTMAPSIZE);
    strncpy(page+12+52*4+SLOTMAPSIZE, "numRecs", 7);
    strncpy(page+32+52*4+SLOTMAPSIZE, RELCAT, 6);

    inttobytearray(36, page+0+52*5+SLOTMAPSIZE);
    inttobytearray(4, page+4+52*5+SLOTMAPSIZE);
    inttobytearray(INTEGER, page+8+52*5+SLOTMAPSIZE);
    strncpy(page+12+52*5+SLOTMAPSIZE, "numPgs", 6);
    strncpy(page+32+52*5+SLOTMAPSIZE, RELCAT, 6);

    inttobytearray(0, page+0+52*6+SLOTMAPSIZE);
    inttobytearray(4, page+4+52*6+SLOTMAPSIZE);
    inttobytearray(INTEGER, page+8+52*6+SLOTMAPSIZE);
    strncpy(page+12+52*6+SLOTMAPSIZE, "offset", 6);
    strncpy(page+32+52*6+SLOTMAPSIZE, ATTRCAT, 7);

    inttobytearray(4, page+0+52*7+SLOTMAPSIZE);
    inttobytearray(4, page+4+52*7+SLOTMAPSIZE);
    inttobytearray(INTEGER, page+8+52*7+SLOTMAPSIZE);
    strncpy(page+12+52*7+SLOTMAPSIZE, "length", 6);
    strncpy(page+32+52*7+SLOTMAPSIZE, ATTRCAT, 7);

    inttobytearray(8, page+0+52*8+SLOTMAPSIZE);
    inttobytearray(4, page+4+52*8+SLOTMAPSIZE);
    inttobytearray(INTEGER, page+8+52*8+SLOTMAPSIZE);
    strncpy(page+12+52*8+SLOTMAPSIZE, "type", 4);
    strncpy(page+32+52*8+SLOTMAPSIZE, ATTRCAT, 7);


    inttobytearray(0xC0000000, page+PAGESIZE);

    inttobytearray(12, page+PAGESIZE+0+SLOTMAPSIZE);
    inttobytearray(4, page+PAGESIZE+4+SLOTMAPSIZE);
    inttobytearray(STRING, page+PAGESIZE+8+SLOTMAPSIZE);
    strncpy(page+PAGESIZE+12+SLOTMAPSIZE, "attrName", 8);
    strncpy(page+PAGESIZE+32+SLOTMAPSIZE, ATTRCAT, 7);

    inttobytearray(32, page+PAGESIZE+0+52+SLOTMAPSIZE);
    inttobytearray(20, page+PAGESIZE+4+52+SLOTMAPSIZE);
    inttobytearray(STRING, page+PAGESIZE+8+52+SLOTMAPSIZE);
    strncpy(page+PAGESIZE+12+52+SLOTMAPSIZE, "relName", 7);
    strncpy(page+PAGESIZE+32+52+SLOTMAPSIZE, ATTRCAT, 7);

    int x=fwrite(page, 1, PAGESIZE*2, file);

    fclose(file);
    if(x!=(2*PAGESIZE))
        return NOTOK;
    else
        return OK;
}