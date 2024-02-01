extern fn printf;
const SIZE i32 = 10;

fn binary_search(array [SIZE]i32, key i32) -> i32{
    let siz i32 = @szof(array)/@szof(i32);
    let mut l = 0;
    let mut r = siz- 1;
    while l <= r {
        let mut m = 1 + (l + r)/2;
        if key == array[m]{
            return m;
        }
        if key > array[m]{
            l = l + 1;
        }else {
            r = r - 1;
        }
    }
    return -1;
}

fn insertion_sort(array *mut [SIZE]i32) {
    for i in 1..SIZE {
        let mut k = (*array)[i];
        let mut j = i - 1;
        while j >= 0 && k < (*array)[j] {
            (*array)[j + 1] = (*array)[j];
            j -= 1;
        }
        (*array)[j + 1] = k;
    }
}
fn print(array *mut [SIZE]i32) {
    for i in 0..SIZE {
        printf("%d ", (*array)[i]);
    }
    printf("\n");
}

fn main() -> i32 {
    let mut array = [6,3,8,4,1,7,2,9,3,5];
    print(&mut array);
    insertion_sort(&mut array);
    print(&mut array);
    printf("%d\n", binary_search(array,5));
    return 0;
}