#include "Game.h"
#include "Game_Variables.h"

void sort_score()
{
    //Our file pointer
     FILE *fp;
     //For looping
     int i=0,j;
     //Loop for 10 times using bubble sort algorithm   
     for( i=0;i<10;++i)
     {
             for(j=i;j<10;++j)
             {
                   if(score[i].score < score[j].score)
                   {
                        //swapping
                       SCORES temp;
                       temp=score[i];
                       score[i]=score[j];
                       score[j]=temp;                  
                   }                       
             }        
     } 
     //open the file to write sorted scores
     fp=fopen("Scores.dat","w");
     //loop for writing score to the file
     for(i=0;i<10;++i)
     {
         fwrite(&score[i],sizeof(SCORES),1,fp);                
    }
    //close the file
    fclose(fp);
}
//////////////////////////////////////////////////////////////////////////////////////////////////

void read_score()
{
     //Our file pointer
     FILE *fptr;
     
     //For looping
     int i=0;
     
     //Open the file Scores.dat
     fptr=fopen("Scores.dat","r");
     
     //loop
     for(i=0;i<10;++i)
     {
        //read the file and assign the score to the structure
       fread(&score[i],sizeof(SCORES),1,fptr);     
                  
     }
     //close the file
      fclose(fptr);   
}

void write_score(SCORES st[])
{
    //Our file pointer
     FILE *fptr;
     
     //for looping
     int i=0;
     
     //open the file
     fptr=fopen("Scores.dat","w");     
    
    //loop 10 times
     while(i<10)
     {
            //write the score information to the file
            fwrite(&st[i],sizeof(SCORES),1,fptr);
            //increment i
            ++i;           
     }
     
     //close the file
    fclose(fptr);   
}
void add_score(char *name, long int scoreVal)
{
    SCORES temp;
    int i=0;
    int addition_point;
    
    for(i=0;i<10;++i)
    {
        if(score[i].score<scoreVal)
        {
            addition_point = i;
        }   
    }
    for(i=addition_point;i<9;++i)
    {
        temp = score[i+1];
        score[i+1] = score[i];
    }
    strcpy(score[addition_point].name,name);
    score[addition_point].score =scoreVal;
    
    write_score(score);
    
}

void reset_scores()
{
    int i=0;
    for(i=0;i<10;++i)
    {
        strcpy(score[i].name,"NO NAME");
        score[i].score = 0;
    }
    write_score(score);
    
}





