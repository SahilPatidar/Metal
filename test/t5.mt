extern fn printf;


fn bar() -> i32{
    let mut a [2] *mut i32 = [null, null];
    let mut vp1 = 0;
    let mut vp2 = 0;
    a[0] = &mut vp1;
    a[1] = &mut vp2;
    *a[0] = 10;
    *a[1] = 11;
    printf("%d\n", vp1);
    printf("%d\n", vp2);
    return 0;
}

fn main() -> i32 {
    bar();
   return 0;
}