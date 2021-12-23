#include <unistd.h> 
#include <sys/types.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/time.h> 
// define a file name char list
char filename [12][20]= {"result_folder/1.txt","result_folder/2.txt","result_folder/3.txt","result_folder/4.txt","result_folder/5.txt","result_folder/6.txt","result_folder/7.txt","result_folder/8.txt","result_folder/9.txt","result_folder/10.txt", "with_fork.txt"};
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
    // condition for non-prime
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
// count and write with corresponding starting parameter
void count_write(int para){
    int num = 10000*para + 1;
    FILE *pFile;
    pFile=fopen(filename[para], "a");
    int n = num+10000;
    while (num <(n)){
        int sum = get_sum(num);
        if (sum==11 && is_prime(num)){
        printf("The number that sum up to 11 is %d \n", num);
        fprintf(pFile, "%d\n", num);
        }
    num++;
    }
    fclose(pFile);
}
// combine 10 files to 1 file 
void write_to_file(FILE *fp1){
  char c;
  FILE *fp2 = fopen("with_fork.txt", "a");
   if (fp1 == NULL || fp2 == NULL)
   {
         puts("Could not open files");
         exit(0);
   }
   // Copy contents of first file to file2.txt
   while ((c = fgetc(fp1)) != EOF)
      fputc(c, fp2);
  fclose(fp1);fclose(fp2);
}
int main(){
    struct timeval start, end;
    gettimeofday(&start, NULL);
    // create 10 child and write numebers to 10 files
    for (int i=0; i<10; i++){
      pid_t pid;
      pid = fork();
      if (pid == 0){
        count_write(i);
        exit(0);
    }
    }
    while(wait(NULL) > 0);
// combine 10 to 1
    for (int i=0; i<10; i++){
      FILE *aFile;
      aFile=fopen(filename[i], "r");
      write_to_file(aFile);
    }
    
    gettimeofday(&end, NULL);
 
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 
    printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);
 
    return 0;
}