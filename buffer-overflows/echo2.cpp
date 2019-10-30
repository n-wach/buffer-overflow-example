#include <stdio.h>
#include <stdlib.h>

void echo() {
  char buffer[128];
  printf("I'm going to store your data at %p\n", &buffer);
  printf("Echo: ");
  gets(buffer); //get some input from stdin
  puts(buffer); //echo it to stdout
}

int main() {
  while(true) {
    echo();
  }
}

