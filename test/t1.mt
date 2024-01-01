extern fn printf;
struct Foo {
    i i32
}

fn bar() -> [2]i32{
    return [1,2];
}
let mut v4 [2]Foo = [Foo{i:10}, Foo{i:5}];
fn main() -> i32 {
    let v fn()->[2]i32 = bar;
    let v2 = &v;
    //v();
    printf("%d\n", v()[0]);
    printf("%d\n", (*v2)()[1]);
    printf("%d\n", v4[0].i);
    printf("%d\n", v4[1].i);
    return 0;
}