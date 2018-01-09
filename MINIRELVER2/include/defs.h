    /* 
	This is the basic definition file.
    */
/*************************************************************
		CONSTANTS
*************************************************************/

#include "../include/error.h"
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>




#define PAGESIZE	512   /*number of bytes in a page */
#define	MAXRECORD	508   /* PAGESIZE minus number of bytes taken up*/
#define SLOTMAPSIZE 4     /*SLOTMAPSIZE do not change!!*/

#define RELNAME		20	 /* max length of a relation name */
#define MAXOPEN		20  	/* max number of files that can be open
                                   at the same time */

#define	OK		0	/* return codes */
#define NOTOK	-1

#define RELCAT		"relcat"   /* name of the relation catalog file */
#define ATTRCAT		"attrcat"  /* name of the attribute catalog file */

#define RELCAT_CACHE    0
#define ATTRCAT_CACHE   1



/*************************************************************
		TYPE DEFINITIONS 
*************************************************************/


typedef enum {false= 0, true=1} boolean;


	boolean print_error;

/* Rid structure */
typedef struct recid {
	short	pid;
	short	slotnum;
} Rid;


/* Page Structure */
typedef struct ps {
	unsigned int slotmap;
	char contents[MAXRECORD];
	} Page;

//Buffer Structure
typedef struct bf{
    short pid;
    boolean  dirty;
    Page p;
}Buffer;


/*************************************************************
        COMPARISON OPERATORS
*************************************************************/

#define EQ  501     //=
#define GEQ 502     //>=
#define GT  503     //>
#define LEQ 504     //<=
#define NEQ 505     //<>
#define LT  506     //<


/*****************************************************************/
/* Data types */
    typedef enum type{
        INTEGER='i',
        FLOAT='f',
        STRING='s'
    }datatype;

/*****************************************************************/

	//Structure for Relation Cache
	typedef struct relCache{
		char relName[RELNAME];
		int recLength;
		int recsPerPg;
		int numAttrs;
		int numRecs;
		int numPgs;
		Rid recatRid;
		int relFile;
		boolean dirty;
		struct attrCat* attrList;
	}RelCat;

//Structure for Attribute Catalog
	struct attrCat{
		int offset;
		int length;
		datatype type;
		char attr_Name[RELNAME];
		char relName[RELNAME];
		struct attrCat *next;
	};


	//CacheEntry	catcache[MAXOPEN];	/* catalog cache */
//Buffer		buffer[MAXOPEN];        /* buffer pool */
	boolean buffer_in_use[MAXOPEN]; //For tracking buffer pool

	RelCat relCat_buffer[MAXOPEN]; //For relation Catalog_buffer

	Buffer page_buffer[MAXOPEN];

	boolean Duplicates;
	boolean db_Open;

	int cache_time[MAXOPEN];
	int cache_current_time;
	char original_directory[200];


	int CloseCats();
	int CloseDB(int argc, char **argv);
	int CloseRel(int relNum);
	int Create (int argc, char **argv);
	int CreateCats();
	int createRelCat();
	int createAttrCat();
	int CreateDB (int argc,char *argv[]);
	int Delete (int argc,char **argv);
	int DeleteRec(int relNum,Rid *recRid);
	int Destroy (int argc,char **argv);
	int DestroyDB(int argc,char *argv[]);
	int FindRec(int relNum, Rid *startRid, Rid **foundRid, char **recPtr, char attrType,
				int attrSize, int attrOffset, char *valuePtr,int compOp);
	int FindRelNum(char *relName);
	int FlushPage(int relNum);
	int GetNextRec( int relNum,Rid *startRid, Rid **foundRid, char **recPtr);
	Rid nextRid(Rid startRid,int recPerPages,Rid lastRid);
	Rid getLastRid(int relNum);
	int Insert (int argc,char **argv);
	struct attrCat* getAttribute(struct attrCat* list,char *attribute);
	int InsertRec(int relNum,char* recPtr);
	int getFreeSlot(int relNum, Rid startRid, Rid *foundRid);
	int isSameRecord(char *rec1,char *rec2,int size);
	Rid getLastRid(int relNum);
	int Load (int argc, char **argv);
	int OpenCats();
	struct attrCat* newNode( int offset, int length, int type, char attrName[], char relName[], struct attrCat* next);
	struct attrCat* createAttrListAC();
	struct attrCat* createAttrListRC();
	int OpenDB (int argc, char **argv);
	int OpenRel(char* relName);
	int Project (int argc,char **argv);
	void Quit (int argc,char **argv);
	int Print (int argc,char **argv);
	int ReadPage(int relNum,short pid);
	int Select (int argc,char **argv);
	int WriteRec(int relNum, char *recPtr, Rid *recRid);

	void inttobytearray(int value, char *array);
	void floattobytearray(float value, char *array);
	int readstringfrombytearray(char *array,int offset,char *string,int size);
	int readintformbytearray(char *array,int offset);

	float readfloatfrombytearray(char *array,int offset);
	boolean compNum(float num1,float num2,int operator);
	boolean compString(char *s1,char *s2,int operator);

