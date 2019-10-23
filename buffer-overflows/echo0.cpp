#include <stdio.h>


void echo() {
  char input[16];
  printf("Echo: ");
  gets(input); //get some input from stdin
  puts(input); //echo it back
}


int main() {
  printf("Welcome to my echo server!\n");
  while(true) {
    echo();
  }
}

