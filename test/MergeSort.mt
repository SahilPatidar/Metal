extern fn printf;
extern fn malloc;
extern fn free;
const SIZE i32 = 10;

fn merge(array *mut [SIZE]i32, begin i32, mid i32, end i32) {
    let arr_one = mid - begin + 1;
    let arr_two = end - mid;

    let mut left_arr *mut i32 = malloc(@szof(i32) * arr_one as ui64) as *mut i32;
    let mut right_arr *mut i32 = malloc(@szof(i32) * arr_two as ui64) as *mut i32;
    
    for i in 0..arr_one{
        left_arr[i] = (*array)[begin + i];
    }
    for i in 0..arr_two{
        right_arr[i] = (*array)[mid + 1 + i];
    }
    
    let mut index_one_array = 0;
    let mut index_two_array = 0;
    let mut index_merge_array = begin;
    
    while index_one_array < arr_one && 
            index_two_array < arr_two {
        if left_arr[index_one_array] >= right_arr[index_two_array] {
            (*array)[index_merge_array] = right_arr[index_two_array];
            index_two_array += 1;
        }else{
            (*array)[index_merge_array] = left_arr[index_one_array];
            index_one_array += 1;
        }
        index_merge_array += 1;
    }
    
    while index_one_array < arr_one  {
        (*array)[index_merge_array] = left_arr[index_one_array];
        index_one_array += 1;
        index_merge_array += 1;
    }

    while index_two_array < arr_two {
        (*array)[index_merge_array] = right_arr[index_two_array];
        index_two_array += 1;
        index_merge_array += 1;
    }
    free(@asVoidPtr(left_arr));
    free(@asVoidPtr(right_arr));
}

fn merge_sort(array *mut [SIZE]i32, begin i32, end i32) {
    if begin >= end {
        return;
    }
    let n = begin + (end - begin) / 2;
    merge_sort(array, begin, n);
    merge_sort(array, n + 1, end);
    merge(array, begin, n, end);
}

fn print(array *mut [SIZE]i32) {
    for i in 0..SIZE {
        printf("%d ", (*array)[i]);
    }
    printf("\n");
}

fn main() -> i32 {          
    let mut array = [6,3,8,4,1,7,2,9,3,5];
    const size i32 = @szof(array) / @szof(i32);
    print(&mut array);
    printf("%llu\n", size);
    merge_sort(&mut array, 0, size - 1);
    print(&mut array);
    return 0;
}