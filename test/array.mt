extern fn printf;
extern fn malloc;
extern fn exit;

struct Foo {
    i i32, 
    link [2] *mut Foo,
}


interface Foo {
    fn get(mut self, i i32) -> *mut Foo {
        return self->link[i];
    }
    fn getv(mut self) -> i32{
        return self->i;
    }
}

fn main() -> i32 {
    let mut v *mut Foo = malloc(@szof(Foo)) as *mut Foo;
    v->i =0;
    v->link[0] = malloc(@szof(Foo)) as *mut Foo;
    v->link[0]->i = 1440;
    v->link[1] = malloc(@szof(Foo)) as *mut Foo;
    v->link[1]->i = 110;
    printf("%d\n", (*v).get(0)->getv());
    printf("%d\n", v->get(1)->getv());
    printf("hello");
    return 0;
}


