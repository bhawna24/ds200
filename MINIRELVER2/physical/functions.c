//
// Created by shivank on 21/10/17.
//

#include "../include/defs.h"


/*
 * This file conatin useful functions used through out the project
 *
 */


//This function converts integer into byte array
void inttobytearray(int value, char *array){
    memcpy(array,(void *)&value,sizeof(int));
}

//This function converts float into byte array
 void floattobytearray(float value, char *array){
     memcpy(array,(void *)&value,sizeof(int));
 }

//This function read string of from byte array of specified size
int readstringfrombytearray(char *array,int offset,char *string,int size){
    if((array==NULL)||(string==NULL))
        return ErrorMsgs(NULLPOINTEREXCEPTION);
    strncpy(string,(array+offset),size);
    return OK;
}

//This function read int from byte array
int readintformbytearray(char *array,int offset){
    int value;
    if(array==NULL)
        return ErrorMsgs(NULLPOINTEREXCEPTION);
    else{
        memcpy(&value,(void *)(array+offset),sizeof(int));
    }
    return value;
}

//This function read float from byte array
float readfloatfrombytearray(char *array,int offset){
    if(array==NULL)
        return ErrorMsgs(NULLPOINTEREXCEPTION);
    else {
        float value;
        memcpy(&value, (array + offset), sizeof(float));
        return value;
    }
}

//This function compare two numbers
boolean compNum(float num1,float num2,int operator){
    switch (operator){
        case EQ:
            if(num1==num2)
                return true;
            else
                return false;
        case NEQ:
            if(num1!=num2)
                return true;
            else
                return false;
        case GEQ:
            if(num1>=num2)
                return true;
            else
                return false;
        case LEQ:
            if(num1<=num2)
                return true;
            else
                return false;
        case GT:
            if(num1>num2)
                return true;
            else
                return false;
        case LT:if(num1<num2)
                return true;
            else
                return false;
        default:
            ErrorMsgs(INVALID_COMPARATOR_OPERATOR);
    }
    return false;
}

//This function compare two strings
boolean compString(char *s1,char *s2,int operator){
    switch (operator){
        case EQ:
            if(strcmp(s1,s2)==0)
                return true;
            else
                return false;
        case NEQ:
            if(strcmp(s1,s2)!=0)
                return true;
            else
                return false;
        case GEQ:
            if(strcmp(s1,s2)>=0)
                return true;
            else
                return false;
        case LEQ:
            if(strcmp(s1,s2)<=0)
                return true;
            else
                return false;
        case GT:
            if(strcmp(s1,s2)>0)
                return true;
            else
                return false;
        case LT:if(strcmp(s1,s2)<0)
                return true;
            else
                return false;
        default:
            ErrorMsgs(INVALID_COMPARATOR_OPERATOR);
    }
    return false;
}

