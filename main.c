#include <stdio.h>

#define BF_CHR "><+-.,[]"
#define DATA_AMOUNT 30000
#define CHAR_AMOUNT 1024*1024

void eval(char *source) {
    char data[DATA_AMOUNT] = {0};
    char *optr = source;
    char *dptr = data;

    while (*optr != EOF) {
	switch (*optr) {
    	    case ('>'):
    	        ++dptr;
    	        break;
    	    case ('<'):
    	        --dptr;
    	        break;
    	    case ('+'):
    	        ++*dptr;
    	        break;
    	    case ('-'):
    	        --*dptr;
    	        break;
    	    case ('.'):
    	        putchar(*dptr);
    	        break;
    	    case (','):
    	        *dptr = getchar();
    	        break;
	    case ('['):
		if (!*dptr) {
		    int offset = 1;
		    while (offset) {
			optr++;
			if (*optr == '[') offset++; else if (*optr == ']') offset--;
		    }
		}
		break;
	    case (']'):
		if (*dptr) {
		    int offset = 1;
		    while (offset) {
			optr--;
			if (*optr == ']') offset++; else if (*optr == '[') offset--;
		    }
		}
		break;
    	    default:
    	        break;
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
    eval(chars);

    fclose(source);
    return 0;
}
