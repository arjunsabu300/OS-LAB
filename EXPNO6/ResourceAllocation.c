#include <stdio.h>
#include <limits.h>
struct process
{
   int pid;
   int memreq;
}p[20];

struct memory
{
   int size;
   int flag;
}m[20];

int n,s;

void firstfit()
{
   int i,j,q;
   printf("FIRST FIT\n");
   for(i=0;i<n;i++)
   {
      q=0;
      for(j=0;j<s;j++)
      {
         if(m[j].size>=p[i].memreq && m[j].flag==0)
         {
            m[j].flag=1;
            printf("Process with pid = %d occupied = %d\n",p[i].pid,m[j].size);
            printf("Internal Fragmentation of process PID = %d = %d\n",p[i].pid,(m[j].size-p[i].memreq));
            q=1;
            break;
         }
      }
      if(q==0)
         printf("Process with pid = %d is not occupied to memory\n",p[i].pid);
   }
   printf("\n\n");
}


void bestfit()
{
   int i,small,j,k,l;
   printf("BEST FIT\n");
   for(i=0;i<s;i++)
   {
      m[i].flag=0;
   }
   for(i=0;i<n;i++)
   {
      small=INT_MAX,k=-1,l=0;
      for(j=0;j<s;j++)
      {
         if(m[j].size>=p[i].memreq && m[j].flag==0)
         {
            if(m[j].size<small)
            {
               small=m[j].size;
               k=j;
            }

         }
      }
      //printf("Process %d, Best fit partition: %d\n", p[i].pid, k);
      if(k!=-1)
      {
         m[k].flag=1;
         l=1;
         printf("Process with pid = %d occupied = %d\n",p[i].pid,m[k].size);
         printf("Internal Fragmentation of process PID = %d = %d\n",p[i].pid,(m[k].size-p[i].memreq));
      }
      if(l==0)
         printf("Process with pid = %d is not occupied in memory\n",p[i].pid);
   }
   printf("\n\n");
}


void worstfit()
{
   int i,j,k,large,l;
   printf("WORST FIT\n");
   for(i=0;i<s;i++)
   {
      m[i].flag=0;
   }
   for(i=0;i<n;i++)
   {
      large=INT_MIN;
      k=-1,l=0;
      for(j=0;j<s;j++)
      {
         if(m[j].size>=p[i].memreq && m[j].flag==0)
         {
            if(m[j].size>large)
            {
               large=m[j].size;
               k=j;
            }
         }
      }
      if(k!=-1)
      {
         m[k].flag=1;
         l=1;
         printf("Process with pid = %d occupied = %d\n",p[i].pid,m[k].size);
         printf("Internal Fragmentation of process PID = %d = %d\n",p[i].pid,(m[k].size-p[i].memreq));
      }
      if(l==0)
         printf("Process with pid = %d is not occupied in memory\n",p[i].pid);
   }
   printf("\n\n");
}


int main(void)
{
   int i,j;
   printf("Enter number of partitions of memory : ");
   scanf("%d",&s);
   printf("Enter amount of partitions of %d partitions \n",s);
   for(i=0;i<s;i++)
   {
      scanf("%d",&m[i].size);
      m[i].flag=0;
   }
   printf("Enter number of processes : ");
   scanf("%d",&n);
   printf("PID\t\t Memory Required\n");
   for(i=0;i<n;i++)
   {
      //printf("Process Id , memory require of process %d : ",i);
      scanf("%d%d",&p[i].pid,&p[i].memreq);
   }
   firstfit();
   bestfit();
   worstfit();
}

