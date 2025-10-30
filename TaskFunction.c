#include<stdio.h>
#include<string.h>
char line[256];

// ### Adding The Tasks ######

int AddTask(char *id,char *task){
  if (id == NULL || task == NULL){
    printf("Provide the ID/Task\n");
    return 1;
  } 
  FILE *fp = fopen("task.txt","a+");
  if (fp == NULL) {
    printf("error opening/creating file");
    return 1;
  }
  while(fgets(line,sizeof(line),fp) != NULL){
    if(strstr(line,id)){
      printf("task already exists!!");
      return 1;
    }
  }

  fprintf(fp,"%s\t%s\t%s\n",id,task,"Pending...");
  fflush(fp);
  printf("task added");
  fclose(fp);
  return 0;
}

// ### Listing Tasks #####

int ListTask(char *marker){
  if (marker == NULL){
    printf("Provide the Marker\n");
    return 1;
  }
  FILE *fp = fopen("task.txt","a+");
  if (fp == NULL){
    printf("Error opening the file");
    return 1;
  }
  marker++;

  switch(*marker){
    case 'a':
      while(fgets(line,sizeof(line),fp)){
        printf("%s",line);
      }
      break;

    case 'c':
      while(fgets(line,sizeof(line),fp)){
        if(strstr(line,"Completed")){
          printf("%s",line);
        }
      }
      break;

    case 'p':
      while(fgets(line,sizeof(line),fp)){
        if(strstr(line,"Pending...")){
          printf("%s",line);
        }
      }
      break;
  }

}

// ### Delete A Task #####

int DeleteTask(char *id){
  
}