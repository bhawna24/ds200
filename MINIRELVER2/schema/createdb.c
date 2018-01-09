/*
 * This method creates new database if it already exits then throws and an error
 *
 * CreateCats() from physical layer for creating catalog files
 * */

#include "../include/defs.h"


struct stat st1={0};
 int CreateDB (int argc,char *argv[])
{
    print_error=true;
    if(db_Open)
        return ErrorMsgs(DB_NOT_CLOSE);
    if (stat(argv[1], &st1) == -1) {
    mkdir(argv[1], 0700);
    printf("Database successfully Created\n");
   }else if(stat(argv[1], &st1) == 0){//if database alreay exists
    return ErrorMsgs(DB_ALREADY_EXISTS);
     }
    getcwd(original_directory,200);//saving the start directory
    chdir(argv[1]);
    db_Open=true;
    int value=CreateCats();
    db_Open=false;

    chdir(original_directory);//changing the directory to database directory
    if(value==NOTOK)
        return ErrorMsgs(PROB_CREATE_CATS);
    else
        return OK;
}


