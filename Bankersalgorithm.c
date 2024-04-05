#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int sem=1;
int state=1;

void sem_wait(int *sem)
{
   while(*sem<=0)
   {
      *sem--;
   }
}

void signal(int *sem)
{
   sleep(1);
   *sem++;
}

void* Printer(void * arg)
{
   int num=*((int*)arg);
   int st=num;
   while(1)
   {
       sem_wait(&sem);
       if(state==st)
       {
          if(num%2==0)
          {
             printf("Even : %d\n",num);
             state=1;
          }
          else
          {
             printf("Odd : %d\n",num);
             state=2;
          }
          num+=2;
          //state=3-st;
       }
       signal(&sem);
   }
   pthread_exit(NULL);
}

void main()
{
   pthread_t oddT,evenT;
   int odd=1,even=2;
   pthread_create(&oddT,NULL,(void*)Printer,&odd);
   pthread_create(&evenT,NULL,(void*)Printer,&even);
   pthread_join(oddT,NULL);
   pthread_join(evenT,NULL);
}