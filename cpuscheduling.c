#include <stdio.h>

int n;

struct process
{
   int pid;
   int at;
   int bt;
   int priority;
   int rst;
   int cplt;
   int tat;
   int wt;
}p[20];

void display(struct process t[])
{
   int i;
   printf("\n\tpid\tarrivaltime\tburst time\tresponse time\tcompletion time\tTAT\twait time\n");\
   for(i=0;i<n;i++)
   {
      printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",t[i].pid,t[i].at,t[i].bt,t[i].rst,t[i].cplt,t[i].tat,t[i].wt);
   }
}

void FCFS()
{
   int i,j,systime=0;
   struct process temp,pr[n];

   for(i=0;i<n;i++)
   {
      pr[i]=p[i];
      pr[i].rst=systime-p[i].at;
      pr[i].cplt=systime+pr[i].bt;
      pr[i].tat=pr[i].cplt-pr[i].at;
      pr[i].wt=pr[i].tat-pr[i].bt;
      systime+=p[i].bt;
   }
   display(pr);
}


void SJF()
{
   struct process temp,psjf[n];
   int i,j,systime=0;
   for(i=0;i<n;i++)
   {
      psjf[i]=p[i];
   }
   for(i=0;i<n;i++)
   {
      for(j=0;j<n-i-1;j++)
      {
         if(psjf[j].bt>psjf[j+1].bt && psjf[j].at!=0)
         {
            temp=psjf[j];
            psjf[j]=psjf[j+1];
            psjf[j+1]=temp;
         }
      }
   }
   for(i=0;i<n;i++)
   {
      psjf[i].rst=systime-psjf[i].at;
      psjf[i].cplt=systime+psjf[i].bt;
      psjf[i].tat=psjf[i].cplt-psjf[i].at;
      psjf[i].wt=psjf[i].tat-psjf[i].bt;
      systime+=psjf[i].bt;
   }
   display(psjf);
}

void priority()
{
   int i,j,systime=0;
   struct process temp,prio[n];
   for(i=0;i<n;i++)
   {
      prio[i]=p[i];
   }
/*
   for(i=0;i<n;i++)
   {
      for(j=0;j<n-i-1;j++)
      {
         if(prio[j].at>prio[j+1].at)
         {
            temp=prio[j];
            prio[j]=prio[j+1];
            prio[j+1]=temp;
         }
      }
   }
*/
   // Sort by arrival time first (processes with arrival time 0 come first)
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (prio[j].at > prio[j + 1].at || (prio[j].at == 0 && prio[j + 1].at != 0))
            {
                temp = prio[j];
                prio[j] = prio[j + 1];
                prio[j + 1] = temp;
            }
        }
    }

    // Then sort by priority for processes with arrival time > 0
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (prio[j].at != 0 && prio[j].priority > prio[j + 1].priority)
            {
                temp = prio[j];
                prio[j] = prio[j + 1];
                prio[j + 1] = temp;
            }
        }
    }

    // Sort by arrival time for processes with the same priority
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (prio[i].priority == prio[j].priority && prio[i].at > prio[j].at)
            {
                temp = prio[i];
                prio[i] = prio[j];
                prio[j] = temp;
            }
        }
    }
   for(i=0;i<n;i++)
   {
      if (systime < prio[i].at)
      {
         systime = prio[i].at;
      }
      prio[i].rst=systime-prio[i].at;
      prio[i].cplt=systime+prio[i].bt;
      prio[i].tat=prio[i].cplt-prio[i].at;
      prio[i].wt=prio[i].tat-prio[i].bt;

      systime+=prio[i].bt;
   }
   display(prio);
}

int main(void)
{
   int i;
   printf("Enter how many processes : ");
   scanf("%d",&n);
   for(i=0;i<n;i++)
   {
      printf("Enter the pid,arivaltime,burst time,priority : ");
      scanf("%d%d%d%d",&p[i].pid,&p[i].at,&p[i].bt,&p[i].priority);
   }
   FCFS();
   SJF();
   priority();

}


