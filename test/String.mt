extern fn printf;
extern fn strlen;
extern fn free;
extern fn malloc;
extern fn realloc;
struct str{
    data *mut i8, 
    capacity ui64,
    size ui64,
    index ui64,
}

interface str{

fn new_str() -> *mut str {
    let str_obj *mut str = new(1, str);
    if str_obj == null{
        return null;
    }
    (*str_obj).size = 1;
    (*str_obj).capacity = 1;
    (*str_obj).index = 0;
    (*str_obj).data = malloc(@szof(i8)*(*str_obj).capacity) as *mut i8;
    (*str_obj).data[0] = '\0';
    return str_obj;
}
fn new_e() -> str {
    let mut str_obj str = str{data:null, size:1, capacity:1, index:0};
    str_obj.data = malloc(@szof(i8)*str_obj.capacity) as *mut i8;
    str_obj.data[0] = '\0';
    return str_obj;
}


fn erase(mut self) {
    (*self).size = 0;
    (*self).capacity = 0;
    (*self).index = 0;
    free(@asVoidPtr((*self).data));
    free(@asVoidPtr(self));
}

fn str_len(mut self) -> i32 {
    if self == null {
        printf("given str is null\n");
        return 0;
    }
    return (*self).size as i32;
}

fn append(mut self, s *const i8){
    if self == null {
        printf("given str is null\n");
        return;
    }
    if s == null {
        printf("given str is null\n");
        return;
    }
    let size ui64 = strlen(s)+1;
    if size == 0 {
        return;
    }
    if (*self).capacity <= (*self).index {
        (*self).capacity = ((*self).size + size - 1)*2;
        (*self).size = (*self).size + size - 1;
        (*self).data = realloc(@asVoidPtr((*self).data), (@szof(i8)*(*self).capacity)) as *mut i8;
    }
    for let mut i ui64 = (*self).index; i < (*self).index+size; i+=1 { 
        (*self).data[i] = s[i];
    }
    (*self).data[size] = '\0';
    (*self).index = (*self).index + size;
}

fn substr(mut self, begin ui64, end ui64) -> *mut str{
    if self == null {
        printf("given str is null\n");
        return null;
    }
    let newstr *mut str = str::new_str();
    if (*self).index < end ||  (*self).index < begin {
        (*newstr).erase();
        return null;
    }
    let mut i ui32 = 0;
    for let mut k ui64 = begin ; k < end;  k+=1 {
        if (*self).data[k] == '\0' {
            return newstr;
        }
        (*newstr).data[i] = (*self).data[k];
        i+=1;
    }
    (*newstr).data[end - begin] = '\0';
    (*newstr).index = end - begin;
    return newstr;
}

}
/*
fn main() -> i32{
    let str_obj *mut str = str::new_str();
    if(str_obj == null){
        printf("str_objing is null after ;;\n");
        return 0;
    }
    (*str_obj).append("hii i am not programmer");
    let bf *mut str = (*str_obj).substr(3, 10);
    printf("%s\n",(*str_obj).data);
    printf("%s\n",(*bf).data);
    //(*bf).erase();
    (*str_obj).erase();
    return 0;
}
*/

