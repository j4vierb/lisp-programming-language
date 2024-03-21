# Chapter 7

## Trees

Add the code that evaluates this structure and actually performs the computations encoded within.

This internal structure is what we saw printed out by the program. It is called an Abstract Syntax Tree, and it represents the structure of the program based on the input entered by the user. The leaves of this tree are numbers and operators. At the branches are the rules used to produce this part of the tree - The information on how to traverse and evaluate it. 

```c
typedef struct mpc_ast_t {
  char *tag;
  char *contents;
  mpc_state_t state;
  int children_num;
  struct mpc_ast_t** children;
} mpc_ast_t;
```

The field `tag` has a list of all the rules used to parse the particular item. For example, `expr|number|reger`. The second field `contents` contain the actual contents of the node. The next field is `state` is the line and column number. The last field `children` has a double pointer, it's a list of child nodes of this tree.

We can access to a child node by accessing this field using array notation. To access a field in a pointer use `->` instead of `.`. To access a children we use `node->children[0]` notation.

## Evaluation

To evaluate a parse tree we are going to write a recursive function. 

```c
CMD> + 1 ( - 2 3 ( * 2 3 ) )
>
  regex
  operator|char:1:1 '+'
  expr|number|regex:1:3 '1'
  expr|>
    char:1:5 '('
    operator|char:1:7 '-'
    expr|number|regex:1:9 '2 3'
    expr|>
      char:1:13 '('
      operator|char:1:15 '*'
      expr|number|regex:1:17 '2 3'
      char:1:21 ')'
    char:1:23 ')'
  regex
```

1. If a node is tagged with number it is always a number, has no children, and we can convert the contents to an integer. 
2. If a node is tagged with expr and is not a numbr, we need to look at its second child, the first and last value are '(' and ')' always. 

## Bonus Marks

- Write a recursive function to compute the number of leaves of a tree.
- Write a recursive function to compute the number of branches of a tree.
- Write a recursive function to compute the most number of children spanning from one branch of a tree.
- How would you use strstr to see if a node was tagged as an expr?

`if(strstr(t->tag, "expr"))`, if `"expr"` is not a substring of `t->tag` it will be 0. 

- How would you use strcmp to see if a node had the contents '(' or ')'?

`if(strcmp(t->contents, '(') == 0 || strcmp(t->contents, ')') == 0)`.

- Add the operator %, which returns the remainder of division. For example % 10 6 is 4.

- Add the operator ^, which raises one number to another. For example ^ 4 2 is 16.

Change the grammar to add the new operator and add this new operator to `eval_op`.

- Add the function min, which returns the smallest number. For example min 1 5 3 is 1.

- Add the function max, which returns the biggest number. For example max 1 5 3 is 5.

- Change the minus operator - so that when it receives one argument it negates it.

## Resources

1. [Abstract syntax tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree)

