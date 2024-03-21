# Parsing

## Polish notation

`1 + 2 + 6` is equivalent to `+ 1 2 6` and `(10 * 2) / (4 + 2)` is equivalent to `/ (* 10 2) (+ 4 2)`.

In polish notation the operator always come first in an expression, followed by numbers or expressions in parentheses. A program is an operator followed by one or more expression, where an expression is either a number, or, in parentheses, an operator followed by one or more expressions.

| Type | Expression |
| - | - |
| `Expression` | either a `Number` or `(`, an `Operator`, one or more `Expression`, and an `)`. |
| `Operator` | `+`, `-`, `*`, or `/` |
| `Number` | one or more characters between `0` and `9` |

## Regular expressions

Are a way of writing grammars for small sections of text such as words or numbers.

| symbol | Meaning |
| - | - |
| . | Any character is required |
| a | The character a is required |
| [abc] | Any character in the set abc is required |
| [a-f] | Any character in the range of a to f is required |
| a? | The character a is optional |
| a* | Zero or more of the character a are required |
| a+ | One or more of the character a are required |
| ^ | The start of input is required |
| $ | The end of input is required |

## Bonus Marks

- Write a regular expression matching strings of all `a` or `b` such as `aababa` or `bbaa`.

**answer**: `/[ab]*/`|

- Write a regular expression matching strings of consecutive `a` and `b` such as `ababab` or `aba`.

**answer**: `/ab/`

- Write a regular expression matching pit, pot and respite but not peat, spit, or part.

**answer**: `/(res)?p(i|o)(t|te)?/`

- Change the grammar to add a new operator such as %.

```c
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT,
  "                                                           \
    number   : /-?[0-9]+/ ;                                   \
    operator : '+' | '-' | '*' | '/' | '%' ;                  \
    expr     : <number> | '(' <operator> <expr>+ ')' ;        \
    lispy    : /^/ <operator> <expr>+ /$/ ;                   \
  ",
  Number, Operator, Expr, Lispy);
```

-  Change the grammar to recognise operators written in textual format add, sub, mul, div.

```c
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT,
  "                                                           \
    number   : /-?[0-9]+/ ;                                   \
    operator : '+' | '-' | '*' | '/' | '%' | \"add\" | \"sub\" | \"mul\" | \"div\" ;                  \
    expr     : <number> | '(' <operator> <expr>+ ')' ;        \
    lispy    : /^/ <operator> <expr>+ /$/ ;                   \
  ",
  Number, Operator, Expr, Lispy);
```

- Change the grammar to recognize decimal numbers such as 0.01, 5.21, or 10.2.

```c
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");

  /* Allow new operators %, mul, add, sub, div */
  mpca_lang(MPCA_LANG_DEFAULT,
  "                                                           \
    number   : /-?([0-9]+.[0-9]+|[0-9]+)/ ;                                   \
    operator : '+' | '-' | '*' | '/' | '%' | \"add\" | \"sub\" | \"mul\" | \"div\" ;                  \
    expr     : <number> | '(' <operator> <expr>+ ')' ;        \
    lispy    : /^/ <operator> <expr>+ /$/ ;                   \
  ",
  Number, Operator, Expr, Lispy);
```

- Change the grammar to make the operators written conventionally, between two expressions.



