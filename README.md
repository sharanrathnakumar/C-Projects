
# Steganography

Abstarct :

Steganography is the practice of hiding private or sensitive information within something that appears to be nothing out to the usual. Steganography is often confused with cryptology because the two are similar in the way that they both are used to protect important information. The difference between two is that steganography involves hiding information so it appears that no information is hidden at all. If a person or persons views the object that the information is hidden inside of he or she will have no idea that there is any hidden information, therefore the person will not attempt to decrypt the information.

What steganography essentially does is exploit human perception, human senses are not trained to look for files that have information inside of them, although this software is available that can do what is called Steganography. The most common use of steganography is to hide a file inside another file.


Requirements :

•	The application accept an image file say .bmp along with the a text file which contains the message to be steged.

•	Analize the size of the message file and the data part of the .bmp file to check whether the messsage could fit in the provided .bmp image.

•	Provide a option to steg a magic string which could be usefull to identify whether the image is steged or not.

•	The appliaction should provide a option to decrpt the file.

•	This has to be an command line apliaction and all the options has to be passed as an command line argument.

## Usage
Compiling Files :
```bash
gcc test_encode.c encode.c decode.c
```
Executing the command : 
```bash
Usage for Encoding : ./a.out -e <image to be encoded> <secret message file> [output file name]
Usage for Decoding : ./a.out -d <steged image >
```
Note : Image Should be in .bmp format.
## Authors

- [@sharanrathnakumar](https://www.github.com/sharanrathnakumar)

