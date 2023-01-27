#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void readInLine(char* str);
void clearBuffer(char* str);

int main(int argc, char *argv[])
{
  char PATH[100] = "/usr/bin/;/home/diedrich/assign1-dswetlik/bin/";
  char buffer[100] = {'\0'};
  
  system("clear");
  int fb = fork();
  if(fb == 0)
    {
      char history[20][100];
      int memCount = 0;
      int memStart = 0;
      printf("> Welcome to the \'all new\' Shell!\n> ");
    while(1)
      {	
	readInLine(buffer);

	if(strncmp(buffer, "!", 1) == 0)
	  {
	    if(strcmp(buffer, "!!") == 0)
	      strcpy(buffer, history[(memCount - 1) % 20]);
	    else {
	      char temp[2] = {'\0'};
	      if(buffer[1] != NULL)
		temp[0] = buffer[1];
	      if(buffer[2] != NULL)
		temp[1] = buffer[2];
	      int x = atoi(temp);
	      strcpy(buffer, history[x]);
	    } 
	  }

	strcpy(history[memCount % 20], buffer);
	memCount++;

	
	memStart = (memStart + 1) % 20;
	
	char* token[10];
	token[0] = strtok(buffer, " ");

	if(strcmp(token[0], "exit") == 0)
	  break;
        else if(strcmp(token[0], "getPATH") == 0)
	  {
	    printf("%s\n> ", PATH);
	    continue;
	  }
	else if(strcmp(token[0], "setPATH") == 0)
	  {
	    strcpy(PATH, strtok(NULL, " "));	    
	    printf("Path Updated to %s\n> ", PATH);
	    continue;
	  }
	else if(strcmp(token[0], "history") == 0)
	  {
	    int x = (memCount % 20) - 1;
	    int y = 0;
	    if(memCount >= 20)
	      y = 19;
	    else
	      y = memCount - 1;
	    
	    while(y >= 0){
	      printf("%d\t%s\n", x ,history[x]);
	      x--;
	      if(x < 0)
		x = 19;
	      y--;
	    }
	    printf("> ");
	    continue;
	  }

	int x = 0;
	while(token[x] != NULL)
	  {
	    x++;
	    token[x] = strtok(NULL, " ");
	  }
      
	int fc = fork();
	if(fc == 0)
	  {

	    char* pathTokens[5] = {'\0'};
	    int y = 0;
	    pathTokens[0] = strtok(PATH, ";");

	    while(pathTokens[y] != NULL)
	      {
		y++;
		pathTokens[y] = strtok(NULL, ";");
	      }

	    while(y > 0)
	      {
		y--;
		char exe[128] = {'\0'};
		strcat(exe, pathTokens[y]);
		strcat(exe, token[0]);
		execv(exe, token);
	      }

	    printf("Error: Command not found.\n");
	    break;
	  }
	else
	  {
	    wait(NULL);
	    clearBuffer(buffer);
	    printf("> ");
	  }
      }
    }
  else
    {
      wait(NULL);
      system("clear");
    }
}

void readInLine(char* str) {
  char x = getchar();
  int i = 0;
  while(x != '\n')
    {
      str[i] = x;
      i++;
      x = getchar();
    }
  str[i] = '\0'; 
}

void clearBuffer(char* str)
{
  char j = str[0];
  int i = 0;
  while(j != '\0')
    {
      str[i] = '\0';
      i++;
      j = str[i];
    }
}
