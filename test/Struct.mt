
extern fn printf;

fn bar() {
    let mut var = 5;
    let mut ptr = &mut var;
    let mut ptrptr = &mut ptr;
    let mut ptrptrptr = &mut ptrptr;
    printf("var = %d\n", var);
    *ptr = 4;
    printf("var = %d\n", var);
    **ptrptr = 3;
    printf("var = %d\n", var);
    ***ptrptrptr = 2;
    printf("var = %d\n", var);
}

fn main() -> i32 {
    bar();
    return 0;
}