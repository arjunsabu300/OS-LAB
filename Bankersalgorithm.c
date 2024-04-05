#include <stdio.h>


int main(void)
{
   int allocation[20][20],max[20][20],available[20],need[20][20],n,i,j,k,count=0,found=0,ex=0,it=0;
   printf("Enter number of processes : ");
   scanf("%d",&n);
   int flag[n];
   for(i=0;i<n;i++)
   {
      printf("Enter Alloocation details A,B,C,D of P%d : ",i);
      for(j=0;j<4;j++)
      {
         scanf("%d",&allocation[i][j]);
      }
      printf("Enter Max details A,B,C,D of P%d : ",i);
      for(j=0;j<4;j++)
      {
         scanf("%d",&max[i][j]);
      }
      flag[i]=0;
   }
   printf("Enter available resources amount A,B,C,D : ");
   for(i=0;i<4;i++)
   {
      scanf("%d",&available[i]);
   }
   for(i=0;i<n;i++)
   {
      for(j=0;j<4;j++)
      {
         need[i][j] = max[i][j]-allocation[i][j];
      }
   }

   printf("SAFE SEQUENCE \n <");
   while(count<n && it<n )
   {
      found=0;
      //it=0;
      for(i=0;i<n;i++)
      {
         if(flag[i]==0)
         {
            ex=1;
            for(j=0;j<4;j++)
            {
               if(need[i][j]>available[j])
               {
                  ex=0;
                  break;
               }
            }
            if(ex)
            {
               for(j=0;j<4;j++)
               {
                  available[j]+=allocation[i][j];
               }
               printf(" P%d ",i);
               flag[i]=1;
               found=1;
               count++;
               it++;
               //break;
            }
         }
      }
      if(!found)
      {
         it++;
         break;
      }
   }
   if(count<n)
   {
      printf("unsafe state\n");
   }

   printf(" >\n");
}