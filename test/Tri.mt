extern fn malloc;
extern fn free;
extern fn printf;

struct tri_node {
    node [26] *mut tri_node,
    is_leaf bool
}

interface tri_node {

    fn new_node() -> *mut tri_node {
        let mut node = malloc(@szof(tri_node)) as *mut tri_node;
        for i in 0..26..1 {
            (*node).node[i] = null;
        }
        (*node).is_leaf = false;
        return node;
    }


    fn print(mut self) {
        if (*self).is_leaf {
            return;
        }
        for i in 0..26..1 {
            if (*self).node[i] != null {
                printf("%c",'a' + i as i8);
                self = (*self).node[i];
                (*self).print();
                printf("\n");
            }
        }
    }


    fn search(mut self, _str *mut i8) -> bool {
        for i in 0..26..1 {
            let mut k = 0;
            if _str[i] > 65 {
                k = (_str[i] - 'A') as i32;
            }else {
                k = (_str[i] - 'a') as i32;
            }
            if (*self).node[k] == null {
                return false;
            }
            self = (*self).node[k];
        }
        return true;
    }


    fn insert(mut self, _str *mut i8, len ui32) {
        for let mut i ui32 = 0; i < len; i+=1 {
            let mut k = (_str[i] - 'a');
            if (*self).node[k] == null {
               (*self).node[k] = tri_node::new_node();
            }
            self = (*self).node[k];
            printf("%c\n", _str[i]);
        }
        (*self).is_leaf = true;
    }


    fn erase(mut self) {
        if (*self).is_leaf {
            free(@asVoidPtr(self));
            return;
        }
        for i in 0..26..1 {
            erase((*self).node[i]);
        }
    }

}

fn main() -> i32 {
    let mut node = tri_node::new_node();
    (*node).insert("apple", 5);
    (*node).insert("orange", 6);
    (*node).insert("colour", 6);
    (*node).insert("ready", 5);
    (*node).insert("select", 6);
    (*node).print();
    return 0;
}