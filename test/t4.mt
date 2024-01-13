extern fn printf;

struct foo {
    i i32
}

fn bar() -> i32{
    let mut a [2]i32 = [2,3];
    a[1] = 5;
    for let mut i = 0; i < 10; i+=1 {
        if i%2 == 0 {
            @print("even = %d\n", i);
        }else{
            @print("odd = %d\n", i);
        }
    }
    return 0;
}

interface foo {
    fn printf(a i32) {
        @print("%d\n", a);
    }

    fn caller(mut self) -> i32{
        self->i = 10;
        return self->i;
    }
}

fn main() -> i32 {
    //bar();
    let a i32 = 0;
    @scan("%d", &a);
    @print("val = %d\n", a);
    @scan("%d", &a);
    foo::printf(a);
    let mut v foo = foo{i:10};
    v.i = 9;
    foo::printf(v.caller());
    foo::printf(folder::faltu::getval());

   return 0;
}