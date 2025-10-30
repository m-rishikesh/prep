#include<stdio.h>
#include "TaskFunction.c"
#include<stdlib.h>
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
      DeleteTask(argv[2]);
      break;
    case 'm':
      MarkTask(argv[2]);
      break;
    case 'e':
      EditTask(argv[2],argv[3]);
      break;
    case 'u':
      int reply = system("go run main.go");
      if (reply == 0){
        printf("File Updated to Cloud");
      }else{
        printf("Error while uploading to the cloud.");
      }
      break;
    default:
      printf("Bye\n");
  }
  return 0;
}
