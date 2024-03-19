#include <stdio.h>

void output_hello_world(int times) {
    while(times > 0) {
	puts("Hello world");
	times -= 1;
    }
}

int main(int argc, char** argv) {
    // use for loop to print out "Hello world!" five times
    for(int i = 0; i < 5; i++) {
        puts("Hello world");
    }

    // use while loop to print out "Hello world!" five times
    int i = 0;
    while(i < 5) {
	puts("Hello world");
	i++;
    }

    // declare a function that outputs Hello World! n number of times
    output_hello_world(2);

    // 
}
