extern fn printf;
fn swap(mut heap *mut [10]i32, i1 ui32, i2 ui32) {
    let temp = (*heap)[i1];
    (*heap)[i1] = (*heap)[i2];
    (*heap)[i2] = temp;
}

fn heapify(mut heap *mut [10]i32, n ui32, idx ui32) {
    let lhs_child ui32 = 2*idx + 1;
    let rhs_child ui32 = 2*idx + 2;
    let mut swap_idx ui32 = idx;

    if lhs_child < n && (*heap)[lhs_child] > (*heap)[idx] {
        swap_idx = lhs_child;
    }else if rhs_child < n && (*heap)[rhs_child] > (*heap)[idx] {
        swap_idx = rhs_child;
    }

    if swap_idx != idx {
        swap(heap, swap_idx, idx);
        heapify(heap, n, swap_idx);
    }
}

fn print(mut heap *mut [10]i32) {
    for let mut i ui32 = 0; i < 4; i+=1 {
        let lhs_child ui32 = 2*i + 1;
        let rhs_child ui32 = 2*i + 2;
        printf("%d - \n", (*heap)[i]);
        printf("\t\t - %d\n", (*heap)[lhs_child]);
        printf("\t\t - %d\n", (*heap)[rhs_child]);
        printf("\n");
    }
}

fn heap_sort(mut heap *mut [10]i32) {
    for let mut i ui32 = 0; i < 10; i+=1 {
        heapify(heap, 10, i);
    }
    printf("%d\n", (*heap)[8]);
    for let mut i ui32 = 0; i < 10; i+=1 {
        swap(heap, 0, i);
        heapify(heap, 10, i);
    }
}

fn main() -> i32{
    let mut a [10]i32 = [6,8,10,9,5,1,7,2,4,3];
    heap_sort(&mut a);
    print(&mut a);
    return 0;
}