/*
 * this method destroy the database
 * */
#include "../include/defs.h"


int DestroyDB(int argc,char *argv[])
{
    //checking whether it is closed or not
    if(db_Open){
           return ErrorMsgs(DB_NOT_CLOSE);
    }
    char array[200];
    strcpy(array,original_directory);

   DIR *d = opendir(argv[1]);
   size_t path_len = strlen(argv[1]);
   int r = -1;

   if (d)
   {
      struct dirent *p;
      r = 0;
      while (!r && (p=readdir(d)))
      {
          int r2 = -1;
          char *buf;
          size_t len;
          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
          {
             continue;
          }
          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);
          if (buf)
          {
             struct stat statbuf;
             snprintf(buf, len, "%s/%s",argv[1], p->d_name);
             if (!stat(buf, &statbuf))
             {
                   r2 = unlink(buf);
                }
             free(buf);
          }
          r = r2;
      }
      closedir(d);
      if (!r)
   {
      r = rmdir(argv[1]);
   }
       //changing directory to original start directory
       chdir(original_directory);
   printf("\nDatabase sucessufully deleted \n");
   }	
else{
       return ErrorMsgs(DB_NOT_EXIST);
}
     return OK;  /* all's fine */
}


