/*
 * OpenDB()
 * _________________________________________
 *
 *
 * This routine opens a database for subsequent use.
 *
 * Arguments passed:
 * ---------------------------
 *  argv[0] = "join"
 *  argv[1] = database name
 *  argv[argc] = NIL
 *
 * return
 * -----------------------
 *  OK: on success
 *  NOTOK: otherwise
 *
 * Global Variables modified:
 * -------------------------
 *  path
 *  db_Open
 *
 * ERRORS REPORTED:
 * --------------------
 *  DB_ALREADY_EXIST
 *  DB_NOT_CREATED
 *
 *  ALGORITHM:
 *  ---------------------------------------------------------------------------------
 *  1.  Check if database is already open
 *  2.  Changes the current working directory to be database directory
 *  3.  Calls OpenCats(), for catalogs
 *
 *
 *  Implementation notes:
 *  ---------------------------------------------------------------------------------
 *      Physical Layer: OpenCats()
 *
 */


#include "../include/defs.h"

struct stat st={0};
int OpenDB (int argc, char **argv)
{
    print_error=true;
    if(db_Open)
        return ErrorMsgs(DB_NOT_CLOSE);
    if(stat(argv[1],&st)==-1) {
    ErrorMsgs(DATABASE_DOES_NOT_EXISTS);
    }else{
        db_Open=true;
        getcwd(original_directory,200);
        chdir(argv[1]);//changing directory to database directory
        if(OpenCats() == NOTOK){
            return NOTOK;
        }else{
            printf("DATABASE SUCESSFULLY OPEN \n");
        }
    }
}


