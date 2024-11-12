#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
    FILE *fp1;
    char temp[20],line[20];
    int start_addr;
    fp1=fopen("object.txt","r");
    if(fp1==NULL)
    {
        printf("unable to open file");
    }
    fseek(fp1,7,SEEK_SET);
    fgets(temp,7,fp1);
    start_addr=atoi(temp);
    printf("starting address:%d\n",start_addr);
    rewind(fp1);
    fscanf(fp1,"%s",line);
    while(line[0]!='E')
    {
        if(line[0]=='T')
        {
            int j=0;
            for (int i = 2; i <9; i++)
                {
                    temp[j++] = line[i];
                }
            start_addr=atoi(temp);
            for(int i=12;i<strlen(line);i++)
            {
                if(line[i]=='^')
                    continue;
                printf("%d  %c%c \n",start_addr,line[i],line[i+1]);
                i++;
                start_addr++;
            }
        }
        fscanf(fp1,"%s",line);
    }
}
