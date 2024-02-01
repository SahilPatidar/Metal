extern fn printf;
const SIZE i32 = 10;
fn insertion_sort(array *[SIZE]i32) {
    for i in 1..SIZE {
        let mut k = i;
        let v = (*array)[k];
        while k >= 1 && (*array)[k] > (*array)[k - 1] {
            (*array)[k] = (*array)[k - 1];
            k -= 1;
        }
        (*array)[k] = v;
    }
}
fn print(array *[SIZE]i32) {
    for i in 1..SIZE {
        printf("%d ", (*array)[i]);
    }
    printf("\n");
}

fn main() -> i32 {
    let mut array = [6,3,8,4,1,7,2,9,3,5];
    print(&mut array);
    insertion_sort(&mut array);
    print(&mut array);
    return 0;
}