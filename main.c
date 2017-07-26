// #include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <openssl/md5.h> 

int main(int argc, char const *argv[])
{

	char *pphrase;
	char *input_file;
	char *len;
	int input_len;
	char * std_null=" ";

	char * output_filename1;
	char * output_filename2;
	
	if(argc<2 || argc>5)
	{
		fprintf(stderr, "Error-invaid input\n");
	}
	if(strcmp(argv[1],"stream")==0)//stream
	{
		if(argc!=4) 
		{
			fprintf(stderr, "Error-invaid input\n");
		} 
		else
		{
			if(argv[2][0]=='p')
			{
				// pphrase=argv[2][3];
				pphrase = strchr(argv[2], '=');
				pphrase++;
				// printf("%s\n", pphrase);
			}
			if (argv[3][0]=='l')
			{
				// len=atoi(len);
				// len=atoi(argv[3][3]);
				len = strchr(argv[3], '=');
				len++;
				input_len = atoi(len);
				// printf("%d\n",input_len );
				stream(pphrase,input_len,0);
			}
			if(argv[3][0]=='p')
			{
				// pphrase=argv[3][3];
				pphrase = strchr(argv[3],'=');
				pphrase++;
			}
			if (argv[3][0]=='l')
			{
				// len=argv[3][3];
				// len=atoi(len);
				// stream(pphrase,len);
				len = strchr(argv[2], '=');
				len++;
				input_len = atoi(len);
				stream(pphrase,input_len,0);
			}
			else
			{
				fprintf(stderr, "Error-invaid input\n");
			}
		}
	}
	if(strcmp(argv[1],"encrypt")==0)//stream
	{
		if(argc<4 || argc>5) 
		{
			fprintf(stderr, "Error-invaid input\n");
		
		} 
		else
		{
			if(argv[2][1]=='p')
			{
				pphrase = strchr(argv[3],'=');
				pphrase++;
				
			}
			if (strstr(argv[3],"out")!=NULL)
			{
				output_filename1 = strchr(argv[3], '=');
				output_filename1++;
				output_filename2 = strchr(argv[3], '=');
				output_filename2++;
			}
			if(argv[3][1]=='p')
			{
				pphrase = strchr(argv[3],'=');
				pphrase++;
				// pphrase=argv[4][4];
			}
			if (strstr(argv[2],"out")!=NULL)
			{
				output_filename1 = strchr(argv[2], '=');
				output_filename1++;
				output_filename2 = strchr(argv[2], '=');
				output_filename2++;
			}
			else
			{
				fprintf(stderr, "Error-invaid input\n");
			}
			if(argc==5)
			{
				encrypt(argv[4],input_file,output_filename1, output_filename2,pphrase,argc);
			}
			else//if no input file is given 
			{
				encrypt(std_null,input_file,output_filename1, output_filename2,pphrase,argc);
			}
		}
	}
	if(strcmp(argv[1],"merge")==0)//stream
	{
		if(argc!=4) 
		{
			fprintf(stderr, "Error-invaid input\n");
		} 
		else
		{
			if(argv[2]==NULL)
			{
				fprintf(stderr, "Error-invaid input\n");
			}
			if(argv[3]==NULL)
			{
				fprintf(stderr, "Error-invaid input\n");
			}
			else
			{
				FILE *fp1 = NULL;
				FILE *fp2 = NULL;
				fp1 = fopen(argv[2], "r");
				fp2 = fopen(argv[3], "r");

				merge(fp1,fp2);

				fclose(fp1);
				fclose(fp2);
			}
		}
	}
	if(strcmp(argv[0],"decrypt")==0)
	{
		if(argc!=2 || argc!=3)
		{
			fprintf(stderr, "Error-invaid input\n");
		}
		else
		{
			FILE *fp = NULL;
			

			if(argc ==2)
				decrypt(stdin);
			else
			{
				fp = fopen(argv[2], "r");
				decrypt(fp);
				fclose(fp);
			}
		}
	}	
	return 0;
}
