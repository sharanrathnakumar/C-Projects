#ifndef HEADERS_H
#define HEADERS_H
#include "types.h"
#include <stdio.h>

/*Metadata Details*/
typedef struct _Metadata
{
    /* data */
    FILE *fptr_mp3file;
    char mp3_filename[30];
    char Artist_name[30];
    char Song_name[30];
    char Album_name[30];
    int year;
    char Content_name[30];
    char Composer_name[30];
} Metadata;

/*Functions Declaration*/
/*Main Function Function Declarations*/
void display_usage();
void display_help();
OperationType check_operation(char *operation);
/*mp3View Function Declarations*/
Status v_argument_validation(int argc , char * filename);
Status v_open_file(Metadata meta_data);
Status v_version_check(Metadata meta_data);
Status view_contents(Metadata meta_data);
Status get_data(Metadata meta_data);
Tag get_tag(FILE *fptr, long int *bit);
uint get_tag_size(FILE * fptr);

#endif
