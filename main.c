#include <stdio.h>
#include <stdlib.h>

#define BF_CHR "><+-.,[]"
#define DATA_AMOUNT 30000
#define CHAR_AMOUNT 1024 * 1024

void eval(char *source, char **loop) {
  char data[DATA_AMOUNT] = {0};
  char *optr = source;
  char *dptr = data;
  char c;

  while ((c = *optr) != EOF) {
    if (c == '>') {
      dptr++;
    } else if (c == '<') {
      dptr--;
    } else if (c == '+') {
      ++*dptr;
    } else if (c == '-') {
      --*dptr;
    } else if (c == '.') {
      putchar(*dptr);
    } else if (c == ',') {
      *dptr = getchar();
    } else if (c == '[' && !*dptr) {
      optr = loop[optr - source];
    } else if (c == ']' && *dptr) {
      optr = loop[optr - source];
    }

    optr++;
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Not enough arguments!\n");
    return 1;
  } else if (argc > 2) {
    printf("Too many arguments!\n");
    return 1;
  }

  FILE *source = fopen(argv[1], "r");
  if (!source) {
    printf("Couldn't open file: \"%s\"\n", argv[1]);
    fclose(source);
    return 1;
  }

  char chars[CHAR_AMOUNT] = {0};
  size_t length = fread(chars, sizeof(char), CHAR_AMOUNT, source);
  chars[length] = EOF;

  char **loop = malloc(sizeof(char *) * CHAR_AMOUNT);
  for (int p = 0; p < CHAR_AMOUNT; p++) {
    if (chars[p] == '[') {
      int q = p;

      int offset = 1;
      while (offset) {
        q++;
        if (chars[q] == '[')
          offset++;
        else if (chars[q] == ']')
          offset--;
      }

      loop[p] = chars + q;
      loop[q] = chars + p;
    }
  }

  eval(chars, loop);

  fclose(source);
  return 0;
}
