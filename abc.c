#include<stdio.h>
#include "TaskFunction.c"
int a = 10;
int main(int argc, char *argv[]){
  printf("TODO SOFTWARE\n");
  char *cmd = argv[1];
  switch (*cmd){
    case 'a':
      AddTask(argv[2],argv[3]);
      break;
    case 'l':
      ListTask(argv[2]);
      break;
    case 'd':
      printf("D\n");
      break;
    case 'm':
      printf("M\n");
      break;
    case 'e':
      printf("E\n");
      break;
    default:
      printf("Bye\n");
  }
  return 0;
}
