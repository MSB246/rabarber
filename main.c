enum Token {
    IncP,
    DecP,
    IncD,
    DecD,
    In,
    Out,
};

struct Vm {
    char data[3000];
    char *ops;
    char *dptr;
    int optr;
};

void vm_next(struct Vm *vm) {
    switch (vm->ops[vm->optr]) {
        case (IncP):
            ++vm->dptr;
            break;
        case (DecP):
            --vm->dptr;
            break;
        case (IncD):
            ++*vm->dptr;
            break;
        case (DecD):
            --*vm->dptr;
            break;
        default:
            break;
    }
    
    vm->optr++;
}

int main() {
    char *source = "";

    return 0;
}