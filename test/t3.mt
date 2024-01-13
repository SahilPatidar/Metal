extern fn printf;

struct foo {
    i i32
}

fn bar(mut i i64) -> i64 {
    if(i == 1){
        return 1;
    }
    return i*bar(i-1);
}

fn foo_bar(mut i [2] *mut i32){
    *i[0] = 10;
    *i[1] = 11;
}

fn main() -> i32{
    let mut v foo = foo{i:1};
    @print("%d\n", v.i);

    while v.i <= 10 {
        @print("mul=%lld\n", bar(v.i as i64));
        if v.i == 6 {
            @print("break == %d\n", v.i);
            v.i+=1;
            continue;
        }else if v.i == 9{
            break;
        }
        v.i += 1;
        @print("%d\n", v.i);
    }
    let mut v2 = 0;
    let mut v3 = 0;
    let v4 = &mut v2;
    let v5 = &mut v3;
    foo_bar([v4, v5]);
    printf("%d\n",v2);
    printf("%d\n",v3);
    return 0;
}