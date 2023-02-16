#include "inverted_index.h"

int main(int argc, char *argv[])
{
    // Validation  and storing part
    file_node_t *head = NULL;
    if (argc <= 1)
        printf("Erorr: Please enter parameters\n");
    else
    {
        validate_n_store_filenames(&head, argv);
    }
}

