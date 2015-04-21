#include<stdlib.h>
#include<stdio.h>

typedef struct {
    char name[20];
    long int score;
}SCORES;
    
int main()
{
     FILE *fptr;
     int i=0;
        SCORES abc;
        
     fptr=fopen("Scores","w");     
    
     strcpy(abc.name,"SANDIP SAHANI");
     
     
     while(i<10)
     {
            
            fwrite(&abc,sizeof(SCORES),1,fptr);
            abc.score = i * 10000;
            ++i;           
     }
     
     fclose(fptr);
     
     fptr = fopen("Scores","r");
     i=0;
     while(i<10)
     {
            fread(&abc,sizeof(SCORES),1,fptr);
            printf("\n%s\t%ld",abc.name,abc.score);
            i++;
        }
     fclose(fptr);
        
        system("PAUSE");
        return 0;

}
