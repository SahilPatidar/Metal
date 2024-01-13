extern fn printf;
const SIZE i32 = 10;
<<<<<<< HEAD
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
=======
fn insertion_sort(array *mut [SIZE]i32) {
    for i in 1..SIZE {
        let mut j = i;
        while j >= 0 && (*array)[j] < (*array)[j - 1] {
            let tmp = (*array)[j];
            (*array)[j] = (*array)[j - 1];
            (*array)[j - 1] = tmp;
            j -= 1;
        }
    }
}
fn print(array *mut [SIZE]i32) {
    for i in 0..SIZE {
>>>>>>> testing
        printf("%d ", (*array)[i]);
    }
    printf("\n");
}

<<<<<<< HEAD
fn main() -> i32 {
=======
fn main() -> i32 {          
>>>>>>> testing
    let mut array = [6,3,8,4,1,7,2,9,3,5];
    print(&mut array);
    insertion_sort(&mut array);
    print(&mut array);
    return 0;
}