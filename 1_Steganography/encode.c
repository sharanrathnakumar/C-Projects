#include <stdio.h>
#include "encode.h"
#include "types.h"
#include <string.h>
#include "common.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */

uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    //   printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    //   printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

        return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

        return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

        return e_failure;
    }

    // No failure return e_success
    return e_success;
}
OperationType check_operation_type(char *argv[]) // function defenition for the check the operation
{
    if (strcmp(argv[1], "-e") == 0) // using the string compare checking the argv[1] is -e
    {
        return e_encode;
    }
    else if (strcmp(argv[1], "-d") == 0) // checking the same to -d
    {
        return e_decode;
    }
    else
    {
        return e_unsupported; // if user entered anyting different then print this message
    }
}

// function defination to read validate the arguments passed through the command line arguments
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    if (argv[2] != NULL)
    {
        char *bmp_file_ext = strstr(argv[2], ".bmp");
        if (bmp_file_ext != NULL)
        {
            if (strcmp(bmp_file_ext, ".bmp") == 0)
            {
                encInfo->src_image_fname = argv[2];
            }
            else
            {
                return e_failure;
            }
        }
        else
        {
            return e_failure;
        }
    }
    else
        return e_failure;
    if (argv[3] != NULL)
    {
        char *txt_file_ext = strstr(argv[3], ".txt");
        if (txt_file_ext != NULL)
        {
            if (strcmp(txt_file_ext, ".txt") == 0)
            {
                encInfo->secret_fname = argv[3];
                strcpy(encInfo->extn_secret_file, ".txt");
            }
            else
            {
                return e_failure;
            }
        }
        else
        {
            return e_failure;
        }
    }
    else
        return e_failure;
    if (argv[4] != NULL) // argv[4] file is bmp or not and passed or not
    {
        encInfo->stego_image_fname = argv[4];
        char *stego_file_ext = strstr(argv[4], ".bmp");
        if (stego_file_ext == NULL)
        {
            encInfo->stego_image_fname = "stego.bmp";
            return e_success;
        }
    }
    else
        encInfo->stego_image_fname = "stego.bmp";
    return e_success;
}

Status do_encoding(EncodeInfo *encInfo) // function defenition
{
    if (open_files(encInfo) == e_success) // calling the open file function and If open file is success then print success message
    {
        printf("INFO : Files Opened Succesfully\n");
        if (check_capacity(encInfo) == e_success) // calling the check capacity function and If capacity is sufficient then print success message
        {
            printf("INFO : Checked Capacity\n");
            if (copy_bmp_header(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success) // calling the function copy the header
            {
                printf("INFO : Header Copied\n"); // if header copied successfully then print success message

                if (encode_magic_string(MAGIC_STRING, encInfo) == e_success) // /calling the magic string function if #* are encoded successfully the print the message
                {
                    printf("INFO : Magic String Copied\n");
                    if (encode_secret_file_extn_size(strlen(encInfo->extn_secret_file), encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success) // calling the function to encode the size of .txt and if size of the extention is encoded then print success message
                    {
                        printf("INFO : File Extension Encoded\n");
                        if (encode_secret_file_extn(encInfo->extn_secret_file, encInfo) == e_success) // calling the function to encode the .txt of the secret file extention
                        {
                            printf("INFO : Secret Data Extention Encoded\n");

                            if (encode_secret_file_size(encInfo->size_secret_file, encInfo) == e_success) // calling the function to encode the size of the secret file to the destination image
                            {
                                printf("INFO : Secret File Size Encoded\n");

                                if (encode_secret_file_data(encInfo) == e_success) // calling the function to encode data of the secret file
                                {
                                    printf("INFO : Encode Secret Data is Success\n");

                                    if (copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success) // calling the function to copy remaing data
                                    {
                                        printf("INFO : Remaining Data Copied\n");
                                        return e_success; // if all the steps completed then return success to main function
                                    }
                                    else
                                    {
                                        printf("ERROR : Remaining Data Copying Failed\n"); // if remaing data not copied then print failure message
                                        return e_failure;
                                    }
                                    return e_success;
                                }
                                else
                                {
                                    printf("ERROR : Secret Data Encoding Failed\n"); // if secret data not encoded then print this error message
                                    return e_failure;
                                }
                            }
                            else
                            {
                                printf("INFO : Secret File Size Encoding Failed\n"); // if file size is not encoded them print this error messge
                                return e_failure;
                            }
                        }

                        else
                        {
                            printf("ERROR : Secret File Extention Encoding Failed\n"); // if extention of secret data is failure then print this message
                            return e_failure;
                        }
                    }
                    else
                    {
                        printf("ERROR : File Extention Size Failed\n"); // if extention of secret data file size encoding is failed then print this message
                        return e_failure;
                    }
                }
                else
                {
                    printf("ERROR : Copying Header failed\n"); // if header  file is not capied then print this message
                    return e_failure;
                }
            }
            else
            {
                printf("ERROR : Check capacity Failed\n"); // if sufficient bytes are not available then failure
                return e_failure;
            }
        }
        else
        {
            printf("ERROR : Open File Failed\n"); // if file is fail to open then print error message
            return e_failure;
        }
    }
}
Status check_capacity(EncodeInfo *encInfo) // function defenition for the check capacity
{
    encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);                          // getting the image size from source  image
    encInfo->size_secret_file = get_file_size(encInfo->fptr_secret);                                    // getting the secret data size
    if (encInfo->image_capacity > ((strlen(MAGIC_STRING) + 4 + 4 + 4 + encInfo->size_secret_file) * 8)) // comparing the sufficient size availability
    {
        return e_success; // if present success or else return failure
    }
    else
    {
        return e_failure;
    }
}
/*uint get_image_size_for_bmp(FILE *fptr_image)   //function defenition for to get the image size
{
    int size;
    fseek(fptr_image,0,SEEK_END);             //getting the byte size by moving the file pointer
    size=ftell(fptr_image);                  //by using ftell getting the total bytes
    rewind(fptr_image);                      //setting the file pointer to the first position
    return size;
}*/
uint get_file_size(FILE *fptr) // function to get file size
{
    int size;
    fseek(fptr, 0, SEEK_END); // getting the file size by moving the file pointer
    size = ftell(fptr);       // by using the ftell getting the totle size
    rewind(fptr);             // rewinding the file pointer
    return size;
}
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image) // function to copy the header
{
    char header[54];                        // declaring character array
    rewind(fptr_src_image);                 // rewing the file pointer
    fread(header, 54, 1, fptr_src_image);   // reading the 54 bytes data from source image
    fwrite(header, 54, 1, fptr_dest_image); // writing the 54 bytes data to destination image
    return e_success;
}
Status encode_magic_string(char *magic_string, EncodeInfo *encInfo) // function declaration to magic string
{
    int status = encode_data_to_image(magic_string, strlen(magic_string), encInfo->fptr_src_image, encInfo->fptr_stego_image, encInfo); // calling the function
    return e_success;
}
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image, EncodeInfo *encInfo) // function defenition
{
    for (int i = 0; i < size; i++) // running the loop upto size time
    {
        fread(encInfo->image_data, 8, 1, encInfo->fptr_src_image); // reading the 8 bytes of data from source image
        encode_byte_to_lsb(data[i], encInfo->image_data);          // calling the function
        fwrite(encInfo->image_data, 8, 1, fptr_stego_image);       // writeing the data to destination image
    }
    return e_success;
}
Status encode_byte_to_lsb(char data, char *image_buffer) // function defenition
{
    unsigned int bit;           // decalring the variable
    for (int i = 0; i < 8; i++) // runnig the loop for 8 times
    {
        image_buffer[i] = (image_buffer[i] & 0xFE); // creating the mask
        bit = (data >> (7 - i)) & 1;                // logic to send the data
        image_buffer[i] = image_buffer[i] | bit;
    }
    return e_success;
}
Status encode_size_to_lsb(int size, char *str) // function defenition for the size
{
    unsigned int bit;
    for (int i = 0; i < 32; i++) // running the loop for the 32 times
    {
        str[i] = (str[i] & 0xFE); // logic to replace the lsb bit
        bit = (size >> (31 - i)) & 1;
        str[i] = str[i] | bit;
    }
    return e_success;
}

Status encode_secret_file_extn_size(int size, FILE *fptr_src_image, FILE *fptr_stego_image) // function defenition for file extention
{
    char str[32];
    fread(str, 32, 1, fptr_src_image);    // reading the  32 byte from the source
    encode_size_to_lsb(size, str);        // calling the function
    fwrite(str, 32, 1, fptr_stego_image); // writing to destination image
    return e_success;
}
Status encode_secret_file_extn(char *file_extn, EncodeInfo *encInfo) // function defenition
{
    encode_data_to_image(file_extn, strlen(file_extn), encInfo->fptr_src_image, encInfo->fptr_stego_image, encInfo); // calling the function
    return e_success;
}
Status encode_secret_file_size(long size, EncodeInfo *encInfo) // function defenition
{
    char str[32];                                  // declaring the variable
    fread(str, 32, 1, encInfo->fptr_src_image);    // reading the 32 byte from the source image
    encode_size_to_lsb(size, str);                 // calling the function
    fwrite(str, 32, 1, encInfo->fptr_stego_image); // writeing the data from the source to destination
    return e_success;
}
Status encode_secret_file_data(EncodeInfo *encInfo) // function defenition
{
    fseek(encInfo->fptr_secret, 0, SEEK_SET);
    char var[encInfo->size_secret_file];                            // declaring the character array
    fread(var, encInfo->size_secret_file, 1, encInfo->fptr_secret); // reading the data
    //    var[encInfo-> size_secret_file - 1] ='\0';                  //assigning the null pointer
    encode_data_to_image(var, strlen(var), encInfo->fptr_src_image, encInfo->fptr_stego_image, encInfo); // calling the function
    return e_success;
}
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest) // function defenition
{
    char ch;                                 // declaring the variable
    while ((fread(&ch, 1, 1, fptr_src)) > 0) // running the loop for reading remaining the data
    {
        fwrite(&ch, 1, 1, fptr_dest); // writing the data
    }
    return e_success;
}
