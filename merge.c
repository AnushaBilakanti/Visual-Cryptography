#include "functions.h"

void merge(FILE *fp1,FILE *fp2)
{
	/**************Checking if files are PBM files**************************/
	int counter=0;
	char format[3];
	while(counter<=2)//storing P4 value into p4_check to validate 
	{
		format[counter]=fgetc(fp1);
		counter++;
	}
	if(strncmp(format,"P4\n",3)!=0)
	{
		fprintf(stderr, "File1 not a PBM file");
		// printf("%d---%d\n",count++,ch );
	}


	counter=0;
	while(counter<=2)//storing P4 value into p4_check to validate 
	{
		format[counter]=fgetc(fp2);
		counter++;
	}
	if(strncmp(format,"P4\n",3)!=0)
	{
		fprintf(stderr, "File2 not a PBM file");
		// printf("%d---%d\n",count++,ch );
	}

	/**************Calculating width and height for PBM files**************************/

	char dimen[10];
	int d=0;
	int width1,height1,width2,height2;
	char ch;

	//File1-width
	while(1)
	{
		ch=fgetc(fp1);
		if(ch==' ')
			break;
		dimen[d]=ch;
		d++;
	}
	
	width1=atoi(dimen);
	//File1-height
	d=0;
	while(1)
	{
		ch=fgetc(fp1);
		if(ch=='\n')
			break;
		dimen[d]=ch;
		d++;
	}
	height1=atoi(dimen);

	d=0;
	/*--------------------FILE 2------*/
	//File2-width
	while(1)
	{
		ch=fgetc(fp2);
		if(ch==' ')
			break;
		dimen[d]=ch;
		d++;
	}
	
	width2=atoi(dimen);
	//File1-height
	d=0;
	while(1)
	{
		ch=fgetc(fp2);
		if(ch=='\n')
			break;
		dimen[d]=ch;
		d++;
	}
	height2=atoi(dimen);

	/*********************Bytes per line**********************************/
	int bytes_per_line;
	if(width1%8 == 0)
	{
		bytes_per_line = (width1/8); //number of bytes to consider at a time. 
	}
	else
	{
		bytes_per_line = (width1/8)+1; 
	}

	int total_bytes=bytes_per_line*height1;

	unsigned char * buffer1 = malloc(total_bytes);
	unsigned char * buffer2 = malloc(total_bytes);

	fread( buffer1, sizeof(unsigned char), total_bytes,fp1 ); 
	fread( buffer2, sizeof(unsigned char), total_bytes,fp2 );

	/*********************Writing in PMB file format********************************/
	printf("P4\n");
	printf("%d %d\n",width1, height1);

	int i,j;
	unsigned char ch1,ch2;
	unsigned char * merged = malloc(bytes_per_line); 



	for(i=0;i<height1; i++)
	{
		for(j=0;j<bytes_per_line; j++)
		{
			ch1= *(buffer1++);
			ch2 = *(buffer2++);
			merged[j] = ch1 | ch2;
		}
		fwrite ( merged, sizeof ( unsigned char ), bytes_per_line, stdout );
	}
	
	fclose ( fp1 );
	fclose ( fp2 );
	printf("\n");
}
