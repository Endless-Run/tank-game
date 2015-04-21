#include<stdio.h>
#include<stdlib.h>

int main()
{   
    int i=0;
    FILE *myFile;
    myFile = fopen("Scores.txt","a");
    
    for(i=0;i<11;i++)
    {
        fprintf(myFile,"%d.                Sandip Sahani            1020201",i+1);
    }
    
    fclose(myFile);
    
    return 0;
}
