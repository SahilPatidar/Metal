extern fn printf;
extern fn malloc;
extern fn exit;

struct Foo {
    i i32, 
    link [2] *mut Foo,
}

fn bar() {
  //let mut v = 1 == 0 && 1 > 0 && (1> -1 || 2 >1);
  let mut c = 0;
  let mut b = 9;
  let mut d = 4;
  //scanf("%d\n", &c);
  //scanf("%d\n", &b);

  printf("true = %d\n", (c == b || (d < 9 && c > -b) ) && (c == b || (d < 9 && c > -b)) && (c != b && (d < 9 && c > -b)));
  if(c == b || d < 9) {
     c = 0;
     printf("true");
  }
}


fn main() -> i32 {
    let mut v *mut Foo = malloc(@szof(Foo)) as *mut Foo;
    if v != null && v->i != 0 {
      v->i = 0;
    }
    printf("%d\n",v->i);
    bar();
    return 0;
}