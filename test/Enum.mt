extern fn printf;

enum OS {
    MAC_OS = 1 - 5,
    LINUX_OS = 1<<1,
}

fn main()-> i32 {
    const v1 i32 = 1;
    const b flt32 = v1 as flt32 + 0.45 + 5.45;
    printf("f32 = %f\n", b);
    let mut v = OS::MAC_OS;
    let mut x OS = v;
    if 4 == OS::MAC_OS {
        printf("hello os = %d\n", OS::MAC_OS as i32);
    }
    if 2 == OS::MAC_OS {
        printf("hello os = %d\n", OS::LINUX_OS as i32);
    }
    return 0;
}