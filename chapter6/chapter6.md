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


