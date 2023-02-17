#include "inverted_index.h"

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

int store_filenames_to_list(char *filename, file_node_t **file_f_head)
{
    file_node_t *new = malloc(sizeof(file_node_t));
    strcpy(new->f_name, filename);
    new->link = NULL;
    if (*file_f_head == NULL)
    {
        *file_f_head = new;
        return SUCCESS;
    }
    file_node_t *ptr = *file_f_head, *prev;
    while (ptr != NULL)
    {
        prev = ptr;
        if (!strcmp(ptr->f_name, new->f_name))
            return REPEATED;
        ptr = ptr->link;
    }
    prev->link = new;
    return SUCCESS;
}

int create_DB(file_node_t *file_f_head, main_node_t **f_head)
{

    while (file_f_head != NULL)
    {
        read_datafile(file_f_head, f_head, file_f_head->f_name);
        file_f_head = file_f_head->link;
    }
}

void read_datafile(file_node_t *file_f_head, main_node_t **f_head, char *f_name)
{
    FILE *fptr = fopen(f_name, "r");
    main_node_t *ptr[26] = {NULL};
    int index = toupper(f_name[0]) % 65;
    *f_head = ptr[index];
    char buff[NAMELENGTH];
    while(!feof(fptr)) {
    fscanf(fptr, "%s", buff);
    insert_at_last_main(f_head, buff);
    }
}

int insert_at_last_main(main_node_t **head, char *word)
{
    int index = toupper(word[0]) % 65;
    printf("Index: %d\n",index);
    
    main_node_t *new = malloc(sizeof(main_node_t));

    if(head[index]->link == NULL)
    {
        printf("Inner Loop\n");
        head[index]->link = new;
        new->f_count = 1;
        new->link = NULL;
        strcpy(new->word,word);
        printf("Word: %s\n", new->word);
        new->sub_link = add_sub_node(word);
        return SUCCESS;
    }
     
}

sub_node_t * add_sub_node(char * word)
{
    sub_node_t *newSub = malloc(sizeof(sub_node_t));
    strcpy(newSub->f_name,word);
    newSub->link = NULL;
    newSub->w_count = 1;
    return newSub;
}
