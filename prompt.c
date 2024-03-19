#include <stdio.h>
#include <stdlib.h>

/* If we are compiling on Windows use this functions */
#ifdef _WIN32

#include <string.h>

static char buffer[2048];

/* Fake readline function */
char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer) + 1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy) - 1] = '\0';
    return cpy;
}

/* Fake add_history funtion */
void add_history(char* unused) {}

/* Otherwise include the editline headers to Linux and Mac */

#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char** argv) {
   puts("Lispy program");
   puts("Version: 0.0.1");
   puts("Use Ctrl + C to exit");

   while(1) {
	char* input = readline("CMD> ");

	add_history(input);

	printf("OUTPUT: %s\n", input);

	free(input);
   }

   return 0;
}
