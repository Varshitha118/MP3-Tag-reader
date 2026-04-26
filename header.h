#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
    char option[3]; 
    char tag[5];   
    char value[100];
} choice;

void view(FILE *fp);
void edit(FILE *fp, const char *tag, const char *new_data);
void help(FILE *fp);
