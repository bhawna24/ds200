/*
 *This method close the current open Database
 *
 * If dataase is not open it throws an error of Databse being not open
 *
 * CloseCats() from physical layer is used
 *
 * */

#include "../include/defs.h"

int CloseDB(int argc, char **argv) {
    if(!db_Open)
        return ErrorMsgs(DB_NOT_OPEN);
    if(CloseCats()==OK){
        //changing the directory to start dirctory
        chdir(original_directory);
        db_Open=false;
        printf("DATABASE SUCCESSFULLY CLOSED\n");
        return OK;
    }else{
        return ErrorMsgs(PROB_CLOSING_CATS);
    }
}


