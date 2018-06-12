#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_LINE 80 // max length

void loop();
char* getLine();
char** tokenize(char *line);
void executeVP(char **args);

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
	char **args; // CLI arguments
	args = malloc(41 * sizeof(char *));
	char *line;
	line = (char *)malloc(sizeof(MAX_LINE));
	char *token;
	int index;
	
	int sRun = 1;
	
	while (sRun) {
		printf("CSCI3120> ");

		line = getLine(line);
		printf("Line: %s", line);

		if (strcmp(line, "exit") == 0) {
			sRun = 0;
			exit(0);
		} else {
			args = tokenize(line);
			executeVP(args);
			free(args);
			free(line);
		}	
			
		fflush(stdout);
	}
}

char* getLine(void) {
	char *line = NULL;
	ssize_t buff = 0;
	getline(&line, &buff, stdin);
	return line;
}

char** tokenize(char *line) {
	int index = 0;
	char** tokens = malloc(41 * sizeof(char *));
	char* tok;

	tok = strtok(line, " ");
	while (tok != NULL) {
		tokens[index] = tok;
		printf("%s", tokens[index]);
		index++;
		tok = strtok(NULL, " ");
	}
	tokens[index+1] = NULL;
	return tokens;
}

void executeVP(char **args) {
	pid_t pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork Failed");
		exit(1);
	} else if (pid == 0) {
		execvp(args[0], args);
	} else {
		wait(NULL);
		printf("\nChild complete\n\n");
	}
}

