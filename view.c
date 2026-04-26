#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void view(FILE *fp)
{
    fseek(fp,10,SEEK_SET);//skip 10 bytes ID3 header
    int count = 0;

    while(count < 6)//loop to print 6 tags
    {
        char str[5];
        unsigned char arr[4];
        unsigned char flag[2];
        unsigned char encoding;
        unsigned int size = 0;

        if(fread(str,4,1,fp) != 1)
        break;
        str[4] = '\0';

        fread(arr,4,1,fp);//read 4 byte of array size

        // endian conversion
        for(int i = 0; i < 4; i++)
        {
            size = (size << 8) | (unsigned int) arr[i];
        }

        if(size == 0) //if size is zero stop reading
        break;

        fseek(fp,2,SEEK_CUR);//skip 2 bytes of flag

        fread(&encoding,1,1,fp);//read encoding byte

        char info[size];
        fread(info,size - 1,1,fp);
        info[size - 1] = '\0';

        if(!strcmp(str,"TIT2")) //check the title 
        {
            printf("Title - %s\n",info); //prints title
            count++; //increment count
        }
        else if(!strcmp(str,"TPE1"))
        {
            printf("Artist - %s\n",info); //prints Artist
            count++; 
        }
        else if(!strcmp(str,"TYER"))
        {
            printf("Year - %s\n",info); //prints Year
            count++; 
        } 
        else if(!strcmp(str,"TALB"))
        {
            printf("Album - %s\n",info); //prints album
            count++; 
        } 
        else if(!strcmp(str,"TCON"))
        {
            printf("Genre - %s\n",info); //prints genre
            count++; 
        }
        else if(!strcmp(str,"COMM"))
        {
            printf("Comment - %s\n",info + 4); //prints comment
            count++; 
        }      
    }
}

