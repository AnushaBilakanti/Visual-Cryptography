#include "functions.h"

unsigned char getBit_d(unsigned char  byte,int i)
{
	
	unsigned char bit;
	bit=(byte>>i) & 0x01;
	return bit;

}

unsigned char setBit_d(unsigned char byte_initial, int bit_count,int img_value)
{
	//need to set a particular bit of a byte
	unsigned char bit;
	bit=(byte_initial>>bit_count) & 0x01;
	if(bit!=img_value && img_value==1)
	{
		byte_initial |= (1<<bit_count);
	}
	
	return byte_initial;
}

void decryption(FILE* fp)
{
	if (fp==NULL)
	{
		fprintf(stderr, "Error-no valid input file\n");
		exit(0);
	}
	if(fp!=NULL)
	{
		/**************Checking if file is PBM files**************************/
		int counter=0;
		char format[3];
		while(counter<=2)//storing P4 value into p4_check to validate 
		{
			format[counter]=fgetc(fp);
			counter++;
		}
		if(strncmp(format,"P4\n",3)!=0)
		{
			fprintf(stderr, "File1 not a PBM file");
			// printf("%d---%d\n",count++,ch );
		}

		/**************Calculating width and height of PBM file**************************/
		char dimen[10];
		int dim=0;
		int width,height;
		char ch;

		//File1-width
		while(1)
		{
			ch=fgetc(fp);
			if(ch==' ')
				break;
			dimen[dim]=ch;
			dim++;
		}
		
		width=atoi(dimen);

		int w;
		for(w=0;w<10;w++)
		{
			dimen[w]='\0';
		}


		//File1-height
		dim=0;
		while(1)
		{
			ch=fgetc(fp);
			if(ch=='\n')
				break;
			dimen[dim]=ch;
			dim++;
		}
		height=atoi(dimen);

		/**********************Declaring arrays**********************************/
			
			
			
		unsigned char* merged_array[height];

		int i;
		for(i=0;i<height;i++)
		{
			merged_array[i] = (unsigned char *)malloc(width*sizeof(unsigned char));
			merged_array[i][width] = '\0';
		}
		for(i=0;i<height;i++)
		{
			merged_array[i][0] = '\0';
		}

		//creating output1 grid. 
		
		unsigned char *original_array[height/2];
		for(i=0;i<(height/2);i++)
		{
			original_array[i] = (unsigned char *)malloc((width/2) * sizeof(unsigned char));
		
		}
		for(i=0;i<(height/2);i++)
		{
			original_array[i][0] = '\0';
		}
		
		/************************converting .pbm into 2-D array************************/
		int row,col;
		int bit_count=7;
		unsigned char  byte_read;
		

		byte_read=fgetc(fp);
		
		char bit;
		for(row=0;row<height;++row)
		{
			for (col = 0; col < width; ++col)
			{
				bit=getBit_d(byte_read,bit_count);
				merged_array[row][col]=bit;
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

		/*******create a 2-D array to store the 2 lines and creating original array *******/
	
	
		char a,b,c,d;

		int j,m,l,k;
		for(i=0,k=0,l=1;i<(height/2) && k<height;i++,k=k+2,l=l+2)
		{
			for(j=0,m=0;j<(width/2) && m<(width);j++,m=m+2)
			{
				a=merged_array[k][m];
				b=merged_array[k][m+1];
				c=merged_array[l][m];
				d=merged_array[l][m+1];

				if(a==1 && b==1 && c==1 && d==1)
				{
					original_array[i][j]=1;
				}
			}
		}

		/********************Converting original array to the PBM image********************/

		fwrite("P4\n",1,3,stdout);
		char * buf1 = (char *)calloc(100, sizeof(char));
		sprintf(buf1,"%d %d\n", width/2, height/2);
		fwrite(buf1,1,strlen(buf1),stdout);
		bit_count=7;

		unsigned char byte_initial=0;

		for(row=0;row<height/2;++row)
		{
			for (col = 0; col < width/2; ++col)
			{
				byte_initial=setBit_d(byte_initial,bit_count,original_array[row][col]);
				// printf("Byte:%d\n",byte_initial );
				// printf("IMG:%d\n",img_array2[row][col] );
				bit_count--;

				if(bit_count<0)
				{
					fwrite(&byte_initial,1,1,stdout);
					byte_initial=0;
					bit_count=7;
					
				}
				
			}
			fwrite(&byte_initial,1,1,stdout);
			byte_initial=0;
			bit_count=7;
			
		}
		
	}//fp!=NULL)

	fclose(fp);
}

