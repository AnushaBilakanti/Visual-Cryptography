#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void str(char *file_name1,char *file_name2)
{
	char *output_filename1 = (char*)malloc(strlen(output_filename1)+6);
	char *output_filename2 = (char*)malloc(strlen(output_filename2)+6);
	
	strcat(output_filename1, ".1.pbm");
	strcat(output_filename2, ".2.pbm");

	printf("%s\n",output_filename1 );
}
	


int main(int argc, char const *argv[])
{
	char *output_filename1="small";
	char *output_filename2="big";
	
	str(output_filename1,output_filename1);
	return 0;
}

	
