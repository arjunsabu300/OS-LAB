#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char seq[50];
int frame[50],sequence[50],f,m=0;


void FIFO()
{
   int hit=0,miss=0,i,j,index=0;
   for(i=0;i<f;i++)
   {
      frame[i]=-1;
   }
   //int hit=0,miss=0,i,j,index=0;
   for(i=0;i<m;i++)
   {
      int found=0;
      for(j=0;j<f;j++)
      {
         if(sequence[i]==frame[j])
         {
            found=1;
            hit++;
            break;
         }
      }
      if(found==0)
      {
         frame[index]=sequence[i];
         index=(index+1)%f;
         miss++;
      }
   }
   printf("No.of misses : %d\n",miss);
   printf("No.of hits : %d\n",hit);
}



void optimal()
{
   //int frame[f];
   int i, j, k, hit = 0, miss = 0;

   // Initialize frames to -1
   for (i = 0; i < f; i++)
   {
      frame[i] = -1;
   }

   for (i = 0; i < m; i++)
   {
      int found = 0;

      // Check if the page is already in one of the frames
      for (j = 0; j < f; j++)
      {
         if (frame[j] == sequence[i])
         {
            found = 1;
            hit++;
            break;
         }
      }

      // If the page is not found, we need to replace one
      if (!found)
      {
         // If there is still space in the frames
         if (frame[f - 1] == -1)
         {
            for (j = 0; j < f; j++)
            {
               if (frame[j] == -1)
               {
                  frame[j] = sequence[i];
                  miss++;
                  break;
               }
            }
         }
         else
         {
            int farthest = i + 1, index = -1;

            for (j = 0; j < f; j++)
            {
               int foundInFuture = 0;
               for (k = i + 1; k < m; k++)
               {
                  if (frame[j] == sequence[k])
                  {
                     if (k > farthest)
                     {
                        farthest = k;
                        index = j;
                     }
                     foundInFuture = 1;
                     break;
                  }
               }
               if (!foundInFuture)
               {
                  index = j;
                  break;
               }
            }

            // Replace the frame that will not be used for the longest period
            frame[index] = sequence[i];
            miss++;
         }
      }
   }

   printf("No. of misses: %d\n", miss);
   printf("No. of hits: %d\n", hit);
}


void lru()
{
    //int frame[f];
    int counter[f];  // To keep track of the usage
    int i, j, k, hit = 0, miss = 0, time = 0;

    // Initialize frames to -1 and counters to 0
    for (i = 0; i < f; i++)
    {
        frame[i] = -1;
        counter[i] = 0;
    }

    for (i = 0; i < m; i++)
    {
        int found = 0, lru_index = 0, min = counter[0];

        // Check if the page is already in one of the frames
        for (j = 0; j < f; j++)
        {
            if (frame[j] == sequence[i])
            {
                found = 1;
                hit++;
                counter[j] = ++time;  // Update the counter for the page
                break;
            }
        }

        // If the page is not found, we need to replace one
        if (!found)
        {
            // Find the least recently used page
            for (j = 0; j < f; j++)
            {
                if (frame[j] == -1)
                {
                    lru_index = j;
                    break;
                }
                if (counter[j] < min)
                {
                    min = counter[j];
                    lru_index = j;
                }
            }

            // Replace the LRU page with the new page
            frame[lru_index] = sequence[i];
            counter[lru_index] = ++time;  // Update the counter for the new page
            miss++;
        }
    }

    printf("No. of misses: %d\n", miss);
    printf("No. of hits: %d\n", hit);
}



void lfu()
{
    int frequency[f];  // To keep track of the usage frequency
    int recent[f];     // To keep track of the most recent use
    int i, j, k, hit = 0, miss = 0, time = 0;

    // Initialize frames to -1, frequencies to 0, and recent to 0
    for (i = 0; i < f; i++)
    {
        frame[i] = -1;
        frequency[i] = 0;
        recent[i] = 0;
    }

    for (i = 0; i < m; i++)
    {
        int found = 0, lfu_index = 0, min_freq = frequency[0];

        // Check if the page is already in one of the frames
        for (j = 0; j < f; j++)
        {
            if (frame[j] == sequence[i])
            {
                found = 1;
                hit++;
                frequency[j]++;  // Update the frequency for the page
                recent[j] = ++time;  // Update the recent use time for the page
                break;
            }
        }

        // If the page is not found, we need to replace one
        if (!found)
        {
            // If there is still space in the frames
            for (j = 0; j < f; j++)
            {
                if (frame[j] == -1)
                {
                    frame[j] = sequence[i];
                    frequency[j] = 1;
                    recent[j] = ++time;  // Update the recent use time for the new page
                    miss++;
                    found = 1;
                    break;
                }
            }
        }

        if (!found)
        {
            // Find the least frequently used page
            for (j = 0; j < f; j++)
            {
                if (frequency[j] < min_freq)
                {
                    min_freq = frequency[j];
                    lfu_index = j;
                }
                else if (frequency[j] == min_freq && recent[j] < recent[lfu_index])
                {
                    lfu_index = j;
                }
            }

            // Replace the LFU page with the new page
            frame[lfu_index] = sequence[i];
            frequency[lfu_index] = 1;  // Reset the frequency for the new page
            recent[lfu_index] = ++time;  // Update the recent use time for the new page
            miss++;
        }
    }

    printf("No. of misses: %d\n", miss);
    printf("No. of hits: %d\n", hit);
}

int main(void)
{
   printf("Enter sequence : ");
   fgets(seq,sizeof(seq),stdin);
   if(seq[strlen(seq)-1]=='\n')
      seq[strlen(seq)-1]='\0';
   char* token=strtok(seq," ");
   while(token!=NULL)
   {
      sequence[m]=atoi(token);
      token=strtok(NULL," ");
      m++;
   }
   printf("Enter the no.of frames : ");
   scanf("%d",&f);
   FIFO();
   optimal();
   lru();
   lfu();
}

