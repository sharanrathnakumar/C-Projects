#include <stdio.h>
#include <string.h>
#include "types.h"
#include "headers.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        display_usage();
    }
    else
    {
        Metadata meta_data;
        strcpy(meta_data.mp3_filename,argv[2]);
        OperationType option = check_operation(argv[1]);

        /*Error During Function Call Will Be Printed In Function Definition*/
        if (option == view)
        {
            if (v_argument_validation(argc, meta_data.mp3_filename) == success)
            {
                if (v_open_file(meta_data) == success)
                {
                    if (v_version_check(meta_data) == success)
                    {
                        view_contents(meta_data);
                    }
                }
            }
        }
        else if (option == edit)
        {
        }
        else
        {
            printf("\nExit\n");
        }
    }
}

OperationType check_operation(char *operation)
{
    if (!strcmp(operation, "-v"))
    {
        return view;
    }
    else if (!strcmp(operation, "-e"))
    {
        return edit;
    }
    else if (!strcmp(operation, "--help"))
    {
        display_help();
    }
    else
    {
        printf("Error: Invalid Operation\n");
        display_usage();
    }
}

void display_usage()
{
    printf("Usage:\nTo View: ./a.out -v <mp3 filename>\nTo Edit: ./a.out -e -t/-a/-A/-m/-y/-c changing_text <mp3 filename>\nTo get Help: ./a.out --help\n");
}

void display_help()
{
    printf("1. -v To View mp3 file contents\n2. -e To Edit mp3 file contents\n");
    printf("      -t -> To Edit Song Title\n      -a -> To Edit Artist name\n      -A -> To Edit Album name\n      -y -> To Edit year\n      -m -> To Edit content\n      -c -> To Edit comment\n");
}
