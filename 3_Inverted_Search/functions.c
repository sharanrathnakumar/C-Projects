#include "inverted_index.h"

void validate_n_store_filenames(file_node_t **head, char *filenames[])
{
    for (int i = 1; filenames[i] != NULL; i++)
    {
        int ret = IsFileValid(filenames[i]);
        if (ret == SUCCESS) {
            ret = store_filenames_to_list(filenames[i], head);
            if(ret == REPEATED)
            printf("Error: Filename is repeated\n");
            else
            {
                // CREATE DB /////////////////////////////////////////////////////////////
            }
        }
        else if(ret == NOT_PRESENT)
        printf("Error: File not Found\n");
        else
        printf("Error: Empty File\n");

    }
}

int IsFileValid(char *filename)
{
    FILE *fptr;
    long size;
   // printf("%s\n", filename);
    fptr = fopen(filename, "r");
    if (fptr == NULL)
        return NOT_PRESENT;

    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);
    if (size == 0)
        return FILE_EMPTY;
    else
        return SUCCESS;
}

int store_filenames_to_list(char *filename, file_node_t **head)
{
    file_node_t *new = malloc(sizeof(file_node_t));
    strcpy(new->f_name,filename);
    new->link = NULL;
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }
    file_node_t *ptr = *head,*prev;
    while(ptr != NULL)
    {
        prev = ptr;
        if(!strcmp(ptr->f_name,new->f_name))
        return REPEATED;
        ptr = ptr->link;
    }
    prev->link = new;
    return SUCCESS;
}
