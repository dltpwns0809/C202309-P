#include<stdio.h>
#define MAX_CHAR 30

void website_print(char website_name[][MAX_CHAR], int y, int list_length) {
  for (int i = 0; i < list_length; i++) {
    if (y == i) {
      printf("> ");
    } else {
      printf("   ");
    }
    printf("(%d) %s\n", i + 1, website_name[i]);
  }
}