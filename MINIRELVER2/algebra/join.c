

#include "../include/defs.h"


Join (argc, argv)
int	argc;
char	**argv;

{
    /* print command line arguments */
    short	k;		/* iteration counter	    */
    printf ("%s:\n", argv[0]);
    for (k = 1 ; k < argc; ++k)
	printf ("\targv[%d] = %s\n", k, argv[k]);

     printf("Join \n");
     return (OK);  /* all's fine */
}


