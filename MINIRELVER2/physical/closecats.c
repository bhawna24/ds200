
/*
 * This method close the all current open relations and free the buffer
 * It also close relation cache and attribute cache
 * */

#include "../include/defs.h"


int CloseCats(){
    if(buffer_in_use[0] == false || buffer_in_use[1] == false)
        return NOTOK;
// closing all the relation in buffer
    for(int i=2; i<MAXOPEN; i++)
        if(buffer_in_use[i] == true)
            CloseRel(i);
  //closing Attribute cache
    int ret1= CloseRel(ATTRCAT_CACHE);
    //closing Realtion Cache
    int ret2=CloseRel(RELCAT_CACHE);
    if(ret1==NOTOK ||ret2==NOTOK)
        return NOTOK;
    return OK;
}