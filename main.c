#include <stdint.h>
#include <stdio.h>
#include <malloc.h>

#define DATA_AMOUNT 30000
#define TOKEN_AMOUNT 128

typedef enum Token {
    Eof,
    IncP,
    DecP,
    IncD,
    DecD,
    Out,
    In,
    IfB,
    IfE,
} Token;

typedef struct Vm {
    char *data;
    char *ops;
} Vm;

Vm vm_new(char *tokens) {
    char *data = (char*)malloc(sizeof(char)*DATA_AMOUNT);
    char *ops = tokens;

    return (Vm){ .data = data, .ops = ops };
}

void vm_eval(Vm vm) {
    while (*vm.ops != Eof) {
	switch (*vm.ops) {
    	    case (IncP):
    	        ++vm.data;
    	        break;
    	    case (DecP):
    	        --vm.data;
    	        break;
    	    case (IncD):
    	        ++*vm.data;
    	        break;
    	    case (DecD):
    	        --*vm.data;
    	        break;
    	    case (Out):
    	        putchar(*vm.data);
    	        break;
    	    case (Out):
    	        *vm.data = getchar();
    	        break;
	    case (IfB):
		if (!*vm.data) {
		    uint32_t offset = 1;
		    while (offset) {
			vm.ops++;
			if (*vm.ops == IfB) offset++; else if (*vm.ops == IfE) offset--;
		    }
		}
		break;
	    case (IfE):
		if (*vm.data) {
		    uint32_t offset = 1;
		    while (offset) {
			vm.ops--;
			if (*vm.ops == IfE) offset++; else if (*vm.ops == IfB) offset--;
		    }
		}
		break;
    	    default:
    	        break;
    	}

	vm.ops++;
    }
}

char *scan(char *source) {
    char *tokens = malloc(sizeof(Token)*TOKEN_AMOUNT);
    uint32_t length = 0;
    char *ptr = source;

    while (*ptr != '\0') {
	if (*ptr == ' ') {
	    ptr++;
	    continue;
	}

	switch (*ptr) {
	    case ('>'):
		tokens[length++] = IncP;
		break;
	    case ('<'):
		tokens[length++] = DecP;
		break;
	    case ('+'):
		tokens[length++] = IncD;
		break;
	    case ('-'):
		tokens[length++] = DecD;
		break;
	    case ('.'):
		tokens[length++] = Out;
		break;
	    case (','):
		tokens[length++] = In;
		break;
	    case ('['):
		tokens[length++] = IfB;
		break;
	    case (']'):
		tokens[length++] = IfE;
		break;
	    default:
		break;
	}

	ptr++;
    }

    tokens[length] = Eof;
    return tokens;
}

int main() {
    char *source = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
    char *tokens = scan(source);
    
    Vm vm = vm_new(tokens);
    vm_eval(vm);

    free(vm.data);
    free(tokens);
    return 0;
}
