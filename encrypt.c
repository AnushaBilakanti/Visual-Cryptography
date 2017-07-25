#include "functions.h"


unsigned char  getBit(unsigned char  byte,int i)
{
	
	unsigned char bit;
	bit=(byte>>i) & 0x01;
	return bit;

}

unsigned char setBit(unsigned char byte_initial, int bit_count,int img_value)
{
	
	unsigned char bit;
	bit=(byte_initial>>bit_count) & 0x01;
	if(bit!=img_value && img_value==1)
	{
		byte_initial |= (1<<bit_count);
	}
	return byte_initial;
}

void encrypt(FILE *fp,char *file_name1, char *file_name2,char *pphrase)
{
	
	// FILE * fp=NULL;
	// if(no_of_argc==5)
	// {
	// 	fp = fopen(input_file, "rb");
	// }
	// else if(no_of_argc==4)
	// {
	// 	fp = stdin;
	// }
	char ch;
	// fp=fopen("small.pbm","rb");
	if (fp==NULL)
	{
		fprintf(stderr, "Error-no valid input file\n");
		exit(0);
	}
	if(fp!=NULL)
	{
		// char p4_check[3];
		int counter=0;
		char format[3];
		char dimen[10];
		int width,height;
		/*********************checking if PBM file**********/
		while(counter<=2)//storing P4 value into p4_check to validate 
		{
			format[counter]=fgetc(fp);
			counter++;
		}
		if(strncmp(format,"P4\n",3)!=0)
		{
			fprintf(stderr, "Not a PBM file");
			// printf("%d---%d\n",count++,ch );
		}


		/*********************calculating the width and height**********/
		int d=0;
		while(1)
		{

			ch=fgetc(fp);
			if(ch==' ')
				break;
			dimen[d]=ch;
			d++;

		}
		
		width=atoi(dimen);

		int w;
		for(w=0;w<10;w++)
		{
			dimen[w]='\0';
		}
		
		d=0;
		while(1)
		{
			ch=fgetc(fp);
			if(ch=='\n')
				break;
			dimen[d]=ch;
			d++;
		}
		height=atoi(dimen);

		//+1 is added else we will loose one byte
		int total_bytes;
		if((width % 8)==0)
		{
			total_bytes=(height*width)/8;
		}
		else
		{
			total_bytes=((height*width)/8)+1;
		}	


		/**********************Declaring arrays**********************************/
		
		
		
		unsigned char* img_array[height];

		int i;
		for(i=0;i<height;i++)
		{
			img_array[i] = (unsigned char *)malloc(width*sizeof(unsigned char));
			img_array[i][width] = '\0';
		}
		for(i=0;i<height;i++)
		{
			img_array[i][0] = '\0';
		}

		//creating output1 and output2 grids. 
		
		unsigned char *img_array1[height*2];
		for(i=0;i<height*2;i++)
		{
			img_array1[i] = (unsigned char *)malloc(width*2 * sizeof(unsigned char));
			//small1[i][0] = '\0';
		}
		for(i=0;i<height*2;i++)
		{
			img_array1[i][0] = '\0';
		}
		

		char *img_array2[height*2];
		for(i=0;i<height*2;i++)
		{
			img_array2[i] = (char *)malloc(width *2 *sizeof(unsigned char));
			//small2[i][h*2] = '\0';
		}
		for(i=0;i<height*2;i++)
		{
			img_array2[i][0] = '\0';
		}


		/************************converting .pbm into 2-D array************************/
		int row,col;
		int bit_count=7;
		unsigned char byte_read;
		// int l_count=0;

		byte_read=fgetc(fp);
		// printf("%d-%x\n",l_count,byte_read );
		
		char bit;
		for(row=0;row<height;++row)
		{
			for (col = 0; col < width; ++col)
			{
				// if(no_of_bytes%bytes_to_read==0 && bit_count>=0)
				// {

				// }
				bit=getBit(byte_read,bit_count);
				img_array[row][col]=bit;
				bit_count--;
				if(bit_count<0)
				{
					byte_read=fgetc(fp);
					if(feof(fp))
					{
						break;
					}
					bit_count=7;
					
				}
				
			}
			byte_read=fgetc(fp);
			if(feof(fp))
			{
				break;
			}
			bit_count=7;
		}
		
		/******************Reading key contents**********************************/
		unsigned char * key=(unsigned char*) malloc(total_bytes);
		key=stream(pphrase,total_bytes,1);
		
		//get all the bytes of key and convet into bits and store in a single array
		// read one byte from key and find its 8 corresponding bit
	
		unsigned char key_stream[total_bytes*8]; // hold the binary value of key
		key_stream[0] = '\0';

		char bin;
		int key_c=0,k,l;

		for(k=0;k<total_bytes;k++)
		{

			for(l=7;l>=0;l--)
			{
				
				bin=getBit(key[k],l);
				key_stream[key_c]=bin;
				key_c++;
				
			}
			
		}


// /**************Comparing bits of img and key to assign to small1 and small2**************/
		int j,m;
		key_c=0; //key counter
		for(i=0,k=0,l=1;i<height && k<(height*2);i++,k=k+2,l=l+2)
		{
			for(j=0,m=0;j<width && m<(2*width);j++,m=m+2)
			{
				if(img_array[i][j]==0) //when img pixel is 1
				{
					if(key_stream[key_c]==0)
					{
						img_array1[k][m]=1;
						img_array1[k][m+1]=0;
						img_array1[l][m]=0;
						img_array1[l][m+1]=1;

						img_array2[k][m]=1;
						img_array2[k][m+1]=0;
						img_array2[l][m]=0;
						img_array2[l][m+1]=1;

						
						key_c++;
					}
					else if(key_stream[key_c]==1)
					{
						img_array1[k][m]=0;
						img_array1[k][m+1]=1;
						img_array1[l][m]=1;
						img_array1[l][m+1]=0;

						img_array2[k][m]=0;
						img_array2[k][m+1]=1;
						img_array2[l][m]=1;
						img_array2[l][m+1]=0;

						key_c++;
					}
				}
				else if(img_array[i][j]==1)
				{
					if(key_stream[key_c]==0)
					{
						img_array1[k][m]=1;
						img_array1[k][m+1]=0;
						img_array1[l][m]=0;
						img_array1[l][m+1]=1;

						img_array2[k][m]=0;
						img_array2[k][m+1]=1;
						img_array2[l][m]=1;
						img_array2[l][m+1]=0;

						key_c++;
					}
					else if(key_stream[key_c]==1)
					{
						img_array1[k][m]=0;
						img_array1[k][m+1]=1;
						img_array1[l][m]=1;
						img_array1[l][m+1]=0;

						img_array2[k][m]=1;
						img_array2[k][m+1]=0;
						img_array2[l][m]=0;
						img_array2[l][m+1]=1;

						key_c++;
					}
				}
			}
		}

/********************Converting two arrays to the two images********************/
		
		// char *output_filename1=file_name1;
		// char *output_filename2=file_name2;
		// output_filename1 = (char*)malloc(strlen(output_filename1)+6);
		// output_filename2 = (char*)malloc(strlen(output_filename2)+6);
		
		char * buf1 = (char *)calloc(100, sizeof(char));
		char * buf2 = (char *)calloc(100, sizeof(char));
		sprintf(buf1,"%s.1.pbm",file_name1);
		sprintf(buf2,"%s.2.pbm",file_name2);
		

		
		//writing pbm formats- P4 & width and height to the file
		FILE * fp1 = fopen(buf1, "wb");
		if(fp1!=NULL)
		{
			
			fputs("P4\n", fp1);
			char * buf = (char *)malloc(10*sizeof(char));
			sprintf(buf, "%d %d\n", width*2, height*2);
			fputs(buf, fp1);
			free(buf);

			bit_count=7;

			unsigned char byte_initial=0;

			for(row=0;row<height*2;++row)
			{
				for (col = 0; col < width*2; ++col)
				{
					byte_initial=setBit(byte_initial,bit_count,img_array1[row][col]);
			
					bit_count--;

					if(bit_count<0)
					{
						fwrite(&byte_initial,1,1,fp1);
						byte_initial=0;
						bit_count=7;
						
					}
					
				}
				fwrite(&byte_initial,1,1,fp1);
				byte_initial=0;
				bit_count=7;
				// exit(0);
			}
		
			fclose(fp1);
		}
		else
		{
			fprintf(stderr, "Error-no valid input file\n");
		}


		FILE * fp2 = fopen(buf2, "wb");
		if(fp2!=NULL)
		{
			
			fputs("P4\n", fp2);
			char * buf = (char *)malloc(10*sizeof(char));
			sprintf(buf, "%d %d\n", width*2, height*2);
			fputs(buf, fp2);
			free(buf);

			bit_count=7;

			unsigned char byte_initial=0;

			for(row=0;row<height*2;++row)
			{
				for (col = 0; col < width*2; ++col)
				{
					byte_initial=setBit(byte_initial,bit_count,img_array2[row][col]);
			
					bit_count--;

					if(bit_count<0)
					{
						fwrite(&byte_initial,1,1,fp2);
						byte_initial=0;
						bit_count=7;
						
					}
					
				}
				fwrite(&byte_initial,1,1,fp2);
				byte_initial=0;
				bit_count=7;
				// exit(0);
			}
		
			fclose(fp2);
		}
		else
		{
			fprintf(stderr, "Error-no valid input file\n");
		}
	}//if(fp!NULL)

}
