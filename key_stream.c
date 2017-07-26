#include "functions.h" 


unsigned char * stream(char *pphrase,int length, int flag)
{
	
	char md5_buf[MD5_DIGEST_LENGTH];
	int len=strlen(pphrase)+2+MD5_DIGEST_LENGTH;
	char *s=malloc(len+1);
	int i=0,j,key_c=0;

	MD5((unsigned char *)pphrase, (unsigned  int)strlen(pphrase), (unsigned char *)md5_buf);

	// char key[length];
	unsigned char * key = malloc(sizeof(char)*length);
	unsigned char * key_str;// used to return key stream of specified length
	key[length]='\0';

	int counter=0;

	if(flag==0)
	{
		for (;;) 
		{
			counter=counter+8;
			if(counter<=length)
			{
				sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, pphrase);
				memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
				MD5((unsigned char *)s,  (unsigned int)len,(unsigned char * )md5_buf); //returns MD5 value of s of 
				fwrite(md5_buf, 1, sizeof(md5_buf)>>1, stdout);
			}
			
			else if (counter>length)
			{
				int bytes_left=8-(counter- length);
				if(bytes_left==0)
				{
					break;
				}
				else
				{
					sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, pphrase);
					memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
					MD5((unsigned char *)s,  (unsigned int)len, (unsigned char * )md5_buf); //returns MD5 value of s of 
					fwrite(md5_buf, 1, sizeof(md5_buf)>>1, stdout);
					break;
				}
				
			}
			if (++i == 100) 
					i = 0;

		}
		printf("\n");
	}
	/********************************************************************************/
	//used when we need to get key stream for encrypt
	else if(flag==1)
	{
		for (;;) 
		{
			counter=counter+8;
			if(counter<=length)
			{
				sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, pphrase);
				memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
				MD5((unsigned char *)s, (unsigned int)len, (unsigned char * )md5_buf); //returns MD5 value of s of 
				for(j=0;j<8;j++)
				{
					// if(md5_buf[j]=='0'||md5_buf[j]=='1'||md5_buf[j]=='2'||md5_buf[j]=='3'
					// 	||md5_buf[j]=='4'||md5_buf[j]=='5'||md5_buf[j]=='6'||md5_buf[j]=='7'||
					// 	md5_buf[j]=='8'||md5_buf[j]=='9')
					key[key_c]=md5_buf[j];
					key_c++;
					
				}
			}
			
			else if (counter>length)
			{
				int bytes_left=8-(counter- length);
				if(bytes_left==0)
				{
					break;
				}
				sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, pphrase);
				memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
				MD5((unsigned char *)s, (unsigned int)len,(unsigned char * ) md5_buf); //returns MD5 value of s of 
				for(j=0;j<bytes_left;j++)
				{
					key[key_c]=md5_buf[j];
					key_c++;
					
				}
				break;
			}
			if (++i == 100) 
					i = 0;

		}
		key_str = key;// returning key of those many bytes
		int l=0;
		while(key_str[l]!='\0')
		{
			printf("%x\n",key_str[l] );
			l++;
		}
	}
	free(s);
	printf("\n");
	return (unsigned char *)key_str;
	
}
