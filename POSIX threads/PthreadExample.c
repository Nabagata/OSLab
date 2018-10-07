#include<pthread.h>
#include<stdio.h>

int sum=0;

void runner(void *param)
{
  int n=atoi(param);
  for(int i=0;i<n;i++)
    sum+=i;
  pthread_exit(0);
}

int main(int argc,char *argv[])
{
  pthread_t tid;
  pthread_attr_t attr;

  if(argc!=2){
    printf("Usage: a.out <int>");
    return -1;
  }
  if(atoi(argv[1])<0){
    printf("Enter positive number");
    return -1;
  }
  pthread_attr_init(&attr);
  pthread_create(&tid,&attr,runner,argv[1]);
  pthread_join(tid,NULL);

  printf("Sum= %d\n",sum);
}
