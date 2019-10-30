#include <stdio.h>

void echo() {
  char buff[16];
  printf("Echo: ");
  gets(buff); //get some input from stdin
  puts(buff); //echo it back
}


int main() {
  printf("Welcome to my echo server!\n");
  while(true) {
    echo();
  }
}

