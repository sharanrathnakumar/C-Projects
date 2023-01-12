#include <stdio.h>
#include <string.h>
#include "types.h"
#include "headers.h"

/*Command Line Argument Validation*/
Status v_argument_validation(int argc, char *filename)
{
    if (argc == 3)
    {
        char *extension = strstr(filename, ".");
        if (!strcmp(extension, ".mp3"))
        {
            return success;
        }
        else
        {
            printf("Error: File ' %s ' is not an mp3 file\n", filename);
        }
    }
    else
    {
        printf("Error: Argument missing\nEnter name of mp3 file\nUsage: ./a.out -v <filename.mp3>\n");
    }
}

#if 1
/*Opening mp3 File in View Mode*/

Status v_open_file(Metadata meta_data)
{
    meta_data.fptr_mp3file = fopen(meta_data.mp3_filename, "r");
    // Error Handling
    if (meta_data.fptr_mp3file == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", meta_data.mp3_filename);

        return failure;
    }
    else
    {
        fclose(meta_data.fptr_mp3file);
        return success;
    }
}

#endif

#if 1
/*Version verification*/

Status v_version_check(Metadata meta_data)
{
    meta_data.fptr_mp3file = fopen(meta_data.mp3_filename, "r");
    unsigned char buffer[10];
    int version;
    // fseek(fptr_file,10,SEEK_SET);
    fread(buffer, sizeof(char), 10, meta_data.fptr_mp3file);
    rewind(meta_data.fptr_mp3file);
    if (buffer[0] == 'I' && buffer[1] == 'D' && buffer[2] == '3')
    {
        version= buffer[3];
        printf("Version: V2.%d\n", version);
        return success;
    }
    else
    {
        printf("Error: Unsupported Version of mp3\n");
        return failure;
    }
}
#endif
