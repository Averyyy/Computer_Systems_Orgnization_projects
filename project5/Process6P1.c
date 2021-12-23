#include <unistd.h> 
#include <sys/types.h> 
#include <stdio.h> 
#include <sys/wait.h>
#include <stdlib.h> 
#include<signal.h> 
int secs=0;
int resets=0;
void handle_sigint(int sig) 
{ 
  //  printf("Caught signal %d\n", sig); 
   resets++;
 if(resets>1) {
   pid_t ppid;
   ppid = getppid();
   kill(ppid,SIGINT);
  }  else {
    secs = 0;
  }
} 

int main(int argc, char **argv)
{
sleep(1);
signal(SIGINT, handle_sigint);
     int i;
  int  j ;
 printf("\n");
  while(secs<5) {
     printf("Time:%i\n",secs+1);
     fflush(0);
     sleep(1);
     secs++;
      printf("\r\b\r");
  }
  kill(getppid(), SIGHUP);
  exit(0);

  return 0;
}
 
