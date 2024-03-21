#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

/* Count the number of nodes in the tree */
int number_of_nodes(mpc_ast_t* t) {
  if (t->children_num == 0) { return 1; }
  if (t->children_num >= 1) {
    int total = 1;

    for(int i = 0; i < t->children_num; i++) {
      total = total + number_of_nodes(t->children[i]);
    }

    return total;
  }
  return 0;
}

/* Use operator string to see which operation to perform */
long eval_op(long x, char* op, long y) {
  if(strcmp(op, "+") == 0) { return x + y; }
  if(strcmp(op, "-") == 0) { return x - y; }
  if(strcmp(op, "*") == 0) { return x * y; }
  if(strcmp(op, "/") == 0) { return x / y; }
  if(strcmp(op, "%") == 0) { return x % y; }
  if(strcmp(op, "^") == 0) { return pow(x, y); }
  return 0;
}

/* Evaluate the tree traversing it */
long eval(mpc_ast_t* t) {
  /* If tagged as number return it directly */
  if(strstr(t->tag, "number")) {
    return atoi(t->contents);
  }

  /* The operator is always second child. */
  char* op = t->children[1]->contents;

  long x = eval(t->children[2]);

  int i = 3;
  while(strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  return x;
}

int main(int argc, char** argv) {
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");
  
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                           \
      number   : /-?[0-9]+/ ;                                   \
      operator : '+' | '-' | '*' | '/' | '%' | '^' ;            \
      expr     : <number> | '(' <operator> <expr>+ ')' ;        \
      lispy    : /^/ <operator> <expr>+ /$/ ;                   \
    ",
    Number, Operator, Expr, Lispy
  );

  puts("Lispy program");
  puts("Version: 0.0.1");
  puts("Use Ctrl + C to exit");

  while(1) {
    char* input = readline("CMD> ");

    add_history(input);

    mpc_result_t r;
    if(mpc_parse("<stdin>", input, Lispy, &r)) {
      long result = eval(r.output);
      printf("%li\n", result);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

	  free(input);
  }

  mpc_cleanup(4, Number, Operator, Expr, Lispy);

  return 0;
}
