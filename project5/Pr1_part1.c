#include <unistd.h> 
#include <sys/types.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/time.h> 

// two tool functions 
int get_sum(int num){
    int sum = 0;
    int i,r = 0;
    while (num != 0){
        r = num%10;
        sum+=r;
        i++;
        num/=10;
    }
    return sum;
}
int is_prime(int n){
    int i, flag = 0;
    for (i = 2; i <= n / 2; ++i) {
    if (n % i == 0) {
      flag = 1;
      break;
    }
  }

  if (n == 1) {
    return 0;
  } 
  else {
    if (flag == 0)
      return 1;
    else
      return 0;
  }

}

int main(){
    // get time beginning
    struct timeval start, end;
    gettimeofday(&start, NULL);
    // write to file
    FILE *pFile;
    pFile=fopen("without_fork.txt", "a");
    pid_t pid;
    int num;
    num = 0;
    // Simple loop to find numbers
    while (num <100001){
        int sum = get_sum(num);
        if (sum==11 && is_prime(num)){
        printf("The number that sum up to 11 is %d \n", num);
        fprintf(pFile, "%d\n", num);
        }
    num++;
    }

    
    gettimeofday(&end, NULL);
 
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);
 
    return 0;
}