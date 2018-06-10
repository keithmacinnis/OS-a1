#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_LINE 80 // max length

char * readline();
void loop();
char * readLine();
char * tokenize(char *line);
int executeVP(char *args);

int a = 0;

/*
	After reading input, the steps are:
	fork a child process using fork()
	the child process will envoke execvp()
	if command included &, parent will invoke wait()
*/		

int main(void) 
{
	loop();
	return 0;
}

void loop()
{
	char *args[MAX_LINE/2+1]; // CLI arguments
	char *line;
	line = (char *)malloc(sizeof(MAX_LINE));
	char *token;
	int index;
	
	int sRun = 1;
	
	while (sRun) {
		printf("CSCI3120> ");
		fflush(stdout);

		scanf("%s", line);
		args[index] = line;
		index++;

		pid_t pid = fork();
		sRun = pid;
		if (pid < 0) {
			fprintf(stderr, "Fork Failed");
		} else if (pid == 0) {
			execvp(args[0], args);
		} else {
			wait(NULL);
			printf("\nChild complete\n\n");
		}	
	}

	// char *line;
	// char *token;

	// int sRun = 1; // flag to determine 
	// int index = 0;

	// while (sRun) {
	// 	printf("CSCI3120>");
	// 	fflush(stdout);	

	// 	line = readLine();
	// 	token = strtok(line, " ");
	// 	while (token != NULL) {
	// 		args[index] = token;
	// 		index++;
	// 	}
	// 	args[index] = NULL;

	
	// 	 sRun = 0;

		
	// }
}

// char** tokenize(char *line) 
// {
// 	char **args; 
// 	int index = 0;
// 	char *token = strtok(line, " ");

// 	while (token != NULL) {
// 		args[index] = token;
// 		index++;
// 		token = strtok(NULL, " ");
// 	}

// 	return args;
// }
// char * readLine() 
// {
// 	char *line = NULL;
// 	size_t size = 0;
// 	if (getline(&line, &size, stdin) > -1) {
// 		return line;
// 	}
// }
// Retrieved from "System Calls and Processes/CSCI 3120: Operating System"
// int executeVP(char *args)
// { 
// 	pid_t pid = fork();

// 	if (pid < 0) {
// 		fprintf(stderr, "Fork Failed");
// 		return 1;
// 	} else if (pid ==0) {
// 		execvp(args[0], args);
// 	} else {
// 		wait(NULL);
// 		printf("Child Complete");
// 	}
// 	return 0;
// }