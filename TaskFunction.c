#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char line[256];

// ### Adding The Tasks ######

int AddTask(char *id,char *task){
  if (id == NULL || task == NULL || strlen(task) == 0 || strlen(id) == 0){
    printf("Provide the ID/Task\n");
    return 1;
  } 
  FILE *fp = fopen("task.txt","a+");
  if (fp == NULL) {
    printf("error opening/creating file");
    return 1;
  }
  while(fgets(line,sizeof(line),fp) != NULL){
    char *tkn = strtok(line," \t\n");
    if(strcmp(id,tkn) == 0){
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
  if (id == NULL){
    printf("provide the task id");
    return 1;
  }
  FILE *fp = fopen("task.txt","r");
  FILE *fptr = fopen("new.txt","w");
  if (fp == NULL || fptr == NULL){
    printf("Failed To Open File");
    return 1;
  }

  char line[256];
  char copy[256];
  int found = 0;

  while(fgets(line,sizeof(line),fp) != NULL){
    strcpy(copy,line);
    found = 0;
    char *token = strtok(copy ," ,\t\n");
    while(token != NULL){
      if(strcmp(token,id)==0){
        found=1;
        break;
      }
      token = strtok(NULL," ,\t\n");
    }
    if (!found){
      fputs(line,fptr);
    }
  }

  fclose(fptr);
  fclose(fp);

  remove("task.txt");
  rename("new.txt","task.txt");
  printf("Deleted the %s\n",id);
  return 0;
}

// ### Mark Tasks ###

int MarkTask(char *id){
  if(id == NULL){
    printf("Enter the id");
    return 1;
  }
  FILE *fp = fopen("task.txt","r");
  if (fp == NULL){
    printf("Unable to open File");
    return 1;
  }
  char line[256];
  char task[256];
  int found = 0;
  while(fgets(line,sizeof(line),fp)!= NULL){
    char *token = strtok(line," \t\n");
    while(token != NULL){
      if(strcmp(token,id)==0){
        token = strtok(NULL," \t\n");
        strcpy(task,token);
        found = 1;
        break;
      }
      token = strtok(NULL," \t\n");
    }
    if (found) break;
  }
  if (!found) {
        printf("Task with ID %s not found.\n", id);
        return 1;
    }
  fclose(fp);
  DeleteTask(id);
  FILE *fpWrite = fopen("task.txt","a");
  if (fpWrite == NULL){
    printf("Error Opening File");
    return 1;
  }
  fprintf(fpWrite,"%s\t%s\t%s\n",id,task,"Completed");
  fclose(fpWrite);
  printf("Marked Completed");
  return 0;
}

//  ### Edit Tasks ###

int EditTask(char *id, char *newTask){
  if(id == NULL || newTask == NULL){
    printf("Enter the id/newTask");
    return 1;
  }
  FILE *fp = fopen("task.txt","r");
  if (fp == NULL){
    printf("Unable to open File");
    return 1;
  }
  char line[256];
  char marker[256];
  int found = 0;
  while(fgets(line,sizeof(line),fp)!= NULL){
    char *tkn = strtok(line," \t\n");
    while(tkn != NULL){
      if(strcmp(tkn,id)==0){
        tkn = strtok(NULL," \t\n");
        tkn = strtok(NULL," \t\n");
        strcpy(marker,tkn);
        found = 1;
        break;
      }
      tkn = strtok(NULL," \t\n");
    }
    if (found) break;
  }
  if (!found) {
        printf("Task with ID %s not found.\n", id);
        return 1;
    }
  fclose(fp);
  DeleteTask(id);
  FILE *fpWrite = fopen("task.txt","a");
  if (fpWrite == NULL){
    printf("Error Opening File");
    return 1;
  }
  fprintf(fpWrite,"%s\t%s\t%s\n",id,newTask,marker);
  fclose(fpWrite);
  printf("Edited the Task");
  return 0;
}

