#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <sys/select.h>
#include <poll.h>

pid_t pid;
int input;
int correct, wrong, miss = 0;
// A simple handle signal function
void handle_sigint(int sig)
{
  kill(pid, SIGKILL);
  printf("\ncan not reset time again - game over\n");
  exit(0);
}
// The three functions below are arithmetic functions used to calculate values
void add(int a, int b, int num)
{
  struct pollfd mypoll = {STDIN_FILENO, POLLIN | POLLPRI};
  printf("What is %d + %d?\n", a, b);
  while (num != a + b)
  {
    if (poll(&mypoll, 1, 5050))
    {
      if (poll(&mypoll, 1, 50))
      {
        scanf("%d", &num);
      }
      if (num == a + b)
      {
        printf("Correct!\n");
        kill(pid, SIGKILL);
        correct++;
        break;
      }
      else
      {
        printf("Incorrect, please try again\n");
        wrong++;
      }
    }
    else
    {
      printf("Time out!\n");
      miss++;
      kill(pid, SIGKILL);
      break;
    }
  }
}
void multi(int a, int b, int num)
{
  struct pollfd mypoll = {STDIN_FILENO, POLLIN | POLLPRI};
  printf("What is %d * %d?\n", a, b);
  while (num != a * b)
  {
    if (poll(&mypoll, 1, 5050))
    {
      if (poll(&mypoll, 1, 50))
      {
        scanf("%d", &num);
      }
      if (num == a * b)
      {
        printf("Correct!\n");
        kill(pid, SIGKILL);
        correct++;
        break;
      }
      else
      {
        printf("Incorrect, please try again\n");
        wrong++;
      }
    }
    else
    {
      printf("Time out!\n");
      miss++;
      kill(pid, SIGKILL);
      break;
    }
  }
}
void minus(int a, int b, int num)
{
  struct pollfd mypoll = {STDIN_FILENO, POLLIN | POLLPRI};
  printf("What is %d - %d?\n", a, b);
  while (num != a - b)
  {
    if (poll(&mypoll, 1, 5050))
    {
      if (poll(&mypoll, 1, 50))
      {
        scanf("%d", &num);
      }
      if (num == a - b)
      {
        printf("Correct!\n");
        kill(pid, SIGKILL);
        correct++;
        break;
      }
      else
      {
        printf("Incorrect, please try again\n");
        wrong++;
      }
    }
    else
    {
      printf("Time out!\n");
      miss++;
      kill(pid, SIGKILL);
      break;
    }
  }
}
// The function here is for asking questions and calling the three functions
void ask_questions(int input)
{

  // input here how many questions will it ask
  if (input == 0)
  {
    exit(0);
  }
  for (int i = 0; i < input; i++)
  {
    int num = 0;
    pid = fork();
    // create a child process for time calling
    if (pid == 0)
    {
      pid = execve("Process6P1", NULL, NULL);
    }
    int a, b, c;
    srand((unsigned)time(NULL));
    a = rand() % 10;
    b = rand() % 10;
    c = rand() % 3;
    // c represents what kind of question to ask
    switch (c)
    {
    case 0:
      add(a, b, num);
      break;
    case 1:
      minus(a, b, num);
      break;
    case 2:
      multi(a, b, num);
      break;
    default:
      break;
    }
  }
}

void handle_signup(int sig)
{
  // kill(pid, SIGKILL);
  printf("\nTime is up\n");
}

int main(int argc, char **argv)
{
  // populate arraay with random numbers
  signal(SIGINT, handle_sigint);
  signal(SIGHUP, handle_signup);
  int child_status;
  int i;
  printf("Please input the number of questions:");
  scanf("%d", &input);
  ask_questions(input);
  printf("Correct Answers: %d\nIncorrect Answers: %d\nMissed Answers: %d\n", correct, wrong, miss);
  return (0);
}