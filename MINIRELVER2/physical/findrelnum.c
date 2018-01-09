
//This method find the relation number i.e. the position in buffer at which it is stored

#include "../include/defs.h"
int FindRelNum(char *relName)
{
    boolean flag=false;
    int num;
    for(int i=0;i<MAXOPEN;i++){
        if(buffer_in_use[i] && compString(relName,relCat_buffer[i].relName,EQ)){
            num=i;
            flag=true;
            break;
        }
    }
    if(flag)
        return num;
    else
        return NOTOK;
}
