# Chapter 2

1. Use a `for` loop to print out `Hello world!` five times.

```c
#include <stdio.h>

int main(int argc, char** argv) {
    for(int i = 0; i < 5; i++) {
        puts("Hello world!");
    }
    return 0;
}
```

2. Use a `while` loop to print out `Hello world!` five times.

```c
#include <stdio.h>

int main(int argc, char** argv) {
    int i = 0;
    while(i < 5) {
        puts("Hello world!");
	i++;
    }
    return 0;
}
```

3. Declare a function that outputs `Hello World!` n number of times. Call this from `main`.

```c
#include <stdio.h>

void print_hello_world(int times) {
    while(times > 0) {
        puts("Hello World!");
	times -= 1;
    }
}

int main(int argc, char** argv) {
    print_hello_world(5);
}
```

4. What does the `typedef keyword do exactly?`

How the documentations says `typedef` names are also commonly used to simplify the syntax of complex declarations. ([https://en.cppreference.com/w/c/language/typedef](https://en.cppreference.com/w/c/language/typedef))
