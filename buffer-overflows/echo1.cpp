#include <stdio.h>
#include <stdlib.h>

void give_shell() {
  system("/bin/sh");
}

void echo() {
  char buffer[16];
  printf("Echo: ");
  gets(buffer); //get some input from stdin
  puts(buffer); //echo it back
}

int main() {
  printf("By the way, give_shell is at %p\n", &give_shell);
  
  while(true) {
    echo();
  }
}

