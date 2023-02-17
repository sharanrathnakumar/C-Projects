#include "inverted_index.h"

int main(int argc, char *argv[])
{
    // Validation  and storing part
    file_node_t *file_f_head = NULL;
    if (argc <= 1)
        printf("Erorr: Please enter parameters\n");
    else
    {
        validate_n_store_filenames(&file_f_head, argv);
    }
}

void validate_n_store_filenames(file_node_t **file_f_head, char *filenames[])
{
    for (int i = 1; filenames[i] != NULL; i++)
    {
        int ret = IsFileValid(filenames[i]);
        if (ret == SUCCESS)
        {
            ret = store_filenames_to_list(filenames[i], file_f_head);
            if (ret == REPEATED)
                printf("Error: Filename is repeated\n");
            else
            {
                main_node_t *f_head = NULL;
                create_DB(*file_f_head, &f_head);
            }
        }
        else if (ret == NOT_PRESENT)
            printf("Error: File not Found\n");
        else
            printf("Error: Empty File\n");
    }
}
