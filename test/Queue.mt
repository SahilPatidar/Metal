

use LinkedList::LinkedList::LinkedList as LinkedList;
use printf;
use free;
use malloc;

/*
mod LinkedList;
extern fn malloc;
extern fn free;
extern fn printf;
*/
struct queue {
    front *mut LinkedList::LinkedList,
    top *mut LinkedList::LinkedList,
}


interface queue {
    fn new_qeue(val i32) -> *mut queue {
        //let mut q = malloc(@szof(queue));
        let mut q = malloc(@szof(queue)) as *mut queue;
        (*q).front = LinkedList::LinkedList::new_list(val);
        (*q).top = (*q).front;
        return q;
    }

    fn push(mut self, val i32) {
        if (*self).empty() {
            (*self).front = LinkedList::LinkedList::new_list(val);
            (*self).top = (*self).front;
            return;
        }
        let mut top = (*self).top;
        (*top).insert(val);
        (*self).top = (*top).next();
    }

    fn front(mut self) -> i32 {
        if (*self).empty() {
            return -1;
        }
        return (*(*self).front).i;
    }

    fn empty(mut self) -> bool {
        return (*self).front == null;
    }

    fn pop(mut self) {
        if (*self).empty() {
            return;
        }

        let del_node = (*self).front;
        (*self).front = (*del_node).delete_root();
    }
}

/*
fn main() -> i32{
    let mut q = queue::new_qeue(0);
    for i in 0..100 {
        (*q).push(i);
        printf("%d\n", (*q).front());
    }
    printf("\n");
    for i in 0..101 {
        printf("%d\n", (*q).front());
        (*q).pop();
    }

    return 0;
}*/