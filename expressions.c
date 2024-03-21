#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

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
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");
  
  /* Allow new operators %, mul, add, sub, div */
  mpca_lang(MPCA_LANG_DEFAULT,
  "                                                           \
    number   : /-?([0-9]+.[0-9]+|[0-9]+)/ ;                   \
    operator : '+' | '-' | '*' | '/' | ;                      \
    expr     : <number> | '(' <expr> <operator> <expr> ')' ;  \
    lispy    : /^/ <expr> <operator> <expr> /$/ ;             \
  ",
  Number, Operator, Expr, Lispy);

  puts("Lispy program");
  puts("Version: 0.0.1");
  puts("Use Ctrl + C to exit");

  while(1) {
	  char* input = readline("CMD> ");

	  add_history(input);

    mpc_result_t r;
    if(mpc_parse("<stdin>", input, Lispy, &r)) {
      mpc_ast_t* a = r.output;
      printf("Tag: %s\n", a->tag);
      printf("Contents: %s\n", a->contents);
      printf("Number of children: %i\n", a->children_num);

      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

	  free(input);
  }

  return 0;
}
