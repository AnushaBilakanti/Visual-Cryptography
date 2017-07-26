//will contain all the declarations
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <openssl/md5.h> 


#define CODES "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define PADDING "="

unsigned char * stream(char *pphrase,int len, int flag);
void encrypt(char * input_file,char *output_filename1,char *output_filename2,char *pphrase,int no_of_argc);
void merge(FILE *fp1,FILE *fp2);
void decrypt(FILE *fp);
unsigned char setBit(unsigned char byte_initial, int bit_count,int img_value);
unsigned char getBit(unsigned char  byte,int i);


