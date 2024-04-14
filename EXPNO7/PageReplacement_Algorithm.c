#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int f,m;
char seq[50];
int frame[20],sequence[50];

void FIFO()
{
   printf("FIFO\n\n");
   int i,j,found=0,hit=0,miss=0,re=0;
   for(i=0;i<f;i++)
      frame[i]=-1;
   for(i=0;i<m;i++)
   {
      found=0;
      for(j=0;j<f;j++)
      {
         if(frame[j]==sequence[i])
         {
            hit++;
            found=1;
            break;
         }
      }
      if(found==0)
      {
         frame[re]=sequence[i];
         miss++;
         re=(re+1)%f;
      }
   }
   printf("No.of hits : %d\n",hit);
   printf("No.of miss : %d\n",miss);
}



void LRU()
{
   printf("LRU\n\n");
   int i,j,found=0,hit=0,miss=0,re=0,t=0,num=0,k;
   for(i=0;i<f;i++)
   {
      frame[i]=-1;
   }
   for(i=0;i<m;i++)
   {
      found=0;
      for(j=0;j<f;j++)
      {
         if(frame[j]==sequence[i])
         {
            hit++;
            found=1;
            break;
         }
      }
      if(!found)
      {
         if(i<f)
         {
            frame[re]=sequence[i];
            miss++;
            re++;
         }
         else
         {
            t=i-f;
            num=sequence[t];
            for(k=0;k<f;k++)
            {
               if(num==frame[k])
               {
                  frame[k]=num;
               }
            }
            miss++;
         }
      }
   }
   printf("No.of hits : %d\n",hit);
   printf("No.of misses : %d\n",miss);
}


int main(void)
{
   printf("Enter sequence : ");
   fgets(seq, sizeof(seq), stdin);
   if (seq[strlen(seq) - 1] == '\n')
       seq[strlen(seq) - 1] = '\0';
   char *token = strtok(seq," ");
   while(token!=NULL)
   {
      sequence[m]=atoi(token);
      token = strtok(NULL," ");
      m++;
   }
   int c;
   printf("Enter the no.of frames : ");
   scanf("%d",&f);

   FIFO();
   LRU();

}

