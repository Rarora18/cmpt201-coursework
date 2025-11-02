#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  // Declared array
  char *last5[5];
  int i = 0;
  int j = 0;
  while (true) {

    printf("Enter input: ");

    char *line = NULL;
    size_t len = 0;

    if (getline(&line, &len, stdin) != 1) {
      // If input equal to print, then stop break

      if (strcmp(line, "print\n\0") == 0) {
        // print first 5 values
        for (int i = 0; i < 5; i++) {
          printf("%s", last5[i]);
          printf("%d", i);
          return 0;
        }
      } else {

        for (int j = 0; j < 5; j++) {
          last5[j] = line;
          printf("%d", j);
        }
      }
    }
  }
}
