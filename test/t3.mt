extern fn printf;

let v [2][2]i32 =  [[2,1],[3,4]];

fn main() ->  i32 {
    printf("%d\n", v[0][0] );
    printf("%d\n", v[1][1] );
   return 0; 
}