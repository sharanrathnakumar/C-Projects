/* Documentation
Name : Sharan Rathnakumar
Date : 3rd January 2023
Description : Steganography
Sample Execution : ./a.out -e beautiful.bmp secret.txt
Output :
INFO : Encoding Selected
INFO : Read and validated encode argument
INFO : Encoding Started
INFO : Files Opened Succesfully
INFO : Checked Capacity
INFO : Header Copied
INFO : Magic String Copied
INFO : File Extension Encoded
INFO : Secret Data Extention Encoded
INFO : Secret File Size Encoded
INFO : Encode Secret Data is Success
INFO : Remaining Data Copied
INFO : Encoding Completed
*/

#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "common.h"
#include "decode.h"

/* Passing arguments through command line arguments */
int main(int argc, char *argv[])
{

    // checking for the argc
    if (argc > 1)
    {

        // Function call for check operation type
        if (check_operation_type(argv) == e_encode)
        {
            printf("INFO : Encoding Selected\n");
            if (argc > 3)
            {
                // Declare structure variable
                EncodeInfo encInfo;
                // Read and validate encode arguments
                if (read_and_validate_encode_args(argv, &encInfo) == e_success)
                {
                    printf("INFO : Read and validated encode argument\n");
                    printf("INFO : Encoding Started\n");

                    // Function call for encoding
                    if (do_encoding(&encInfo) == e_success)
                    {
                        printf("INFO : Encoding Completed\n");
                    }
                    else
                    {
                        printf("ERROR : Failed to encode\n");
                        return -1;
                    }
                }
                else
                {
                    printf("ERROR : Read and validating Encode Argument Failed\n");
                    return -1;
                }
            }
            else
            {
                printf("ERROR : for -e argc > 3\n");
                return -1;
            }
        }
        // Function call for check operation type
        else if (check_operation_type(argv) == e_decode)
        {
            printf("INFO : Selected Decoding\n");
            if (argc > 2)
            {

                // Declare structure variables
                DecodeInfo decInfo;
                if (read_and_validate_decode_args(argv, &decInfo) == d_success)
                {
                    printf("INFO : Read and validated Decode Arguments\n");
                    printf("INFO : Decoding Started\n");

                    // Function call for do decoding
                    if (do_decoding(&decInfo) == d_success)
                    {
                        printf("INFO : Decoding is Completed\n");
                    }
                    else
                    {
                        printf("ERROR : Decoding Failed\n");
                        return -1;
                    }
                }
                else
                {
                    printf("ERROR : Read and Validation of Decode Arguments Failed\n");
                    return -1;
                }
            }
            else
            {
                printf("ERROR : Invalid option\npass for\nEncoding: ./a.out -e beautiful.bmp secret.txt stego.bmp\nDecoding: ./a.out -d stego.bmp decode.txt\n");
            }
        }
        else
        {
            printf("ERROR :pass for\n Encoding: 4 arguments\nDecoding: 3 arguments\n");
        }
    }
    else
    {
        printf("ERROR : argc should be > 1\n");
        return -1;
    }

    return 0;
}
