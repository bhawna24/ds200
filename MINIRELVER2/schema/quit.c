#include "../include/defs.h"


void Quit (int argc,char **argv)
{
    if(db_Open)
        CloseDB(1,"closedb");
}


