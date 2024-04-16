#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FRAMES 20
#define MAX_SEQUENCE 50

int f,m;
char seq[MAX_SEQUENCE];
int frame[MAX_FRAMES], sequence[MAX_SEQUENCE];

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
   printf("No.of misses : %d\n",miss);
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
            for(k=j; k>0; k--) // Update recently used page
            {
               frame[k] = frame[k-1];
            }
            frame[0] = sequence[i];
            break;
         }
      }
      if(!found)
      {
         if(re<f)
         {
            frame[re]=sequence[i];
            miss++;
            re++;
         }
         else
         {
            for(k=f-1; k>0; k--) // Shift frames to make space for new page
            {
               frame[k] = frame[k-1];
            }
            frame[0] = sequence[i];
            miss++;
         }
      }
   }
   printf("No.of hits : %d\n",hit);
   printf("No.of misses : %d\n",miss);
}

void LFU()
{
   printf("LFU\n\n");
   int i,j,found=0,hit=0,miss=0,counts[MAX_FRAMES]={0},min_count=0,re=0;
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
            counts[j]++;
            break;
         }
      }
      if(!found)
      {
         if(re<f)
         {
            frame[re]=sequence[i];
            counts[re]=1;
            miss++;
            re++;
         }
         else
         {
            min_count = counts[0];
            re = 0;
            for(j=1; j<f; j++)
            {
               if(counts[j]<min_count)
               {
                  min_count = counts[j];
                  re = j;
               }
            }
            frame[re] = sequence[i];
            counts[re] = 1;
            miss++;
         }
      }
   }
   printf("No.of hits : %d\n",hit);
   printf("No.of misses : %d\n",miss);
}

void MFU()
{
   printf("MFU\n\n");
   int i,j,found=0,hit=0,miss=0,counts[MAX_FRAMES]={0},max_count=0,re=0;
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
            counts[j]++;
            break;
         }
      }
      if(!found)
      {
         if(re<f)
         {
            frame[re]=sequence[i];
            counts[re]=1;
            miss++;
            re++;
         }
         else
         {
            max_count = counts[0];
            re = 0;
            for(j=1; j<f; j++)
            {
               if(counts[j]>max_count)
               {
                  max_count = counts[j];
                  re = j;
               }
            }
            frame[re] = sequence[i];
            counts[re] = 1;
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
   printf("Enter the no.of frames : ");
   scanf("%d",&f);

   FIFO();
   LRU();
   LFU();
   MFU();

   return 0;
}
