
use printf;
use free;
use malloc;
/*
extern fn malloc;
extern fn printf;
extern fn free;
*/
struct LinkedList {
    data i32,
    next *mut LinkedList
}

interface LinkedList {
    fn new_list(i i32) -> *mut LinkedList {
        //let mut v = new(1, LinkedList);
        let mut v = malloc(@szof(LinkedList)) as *mut LinkedList;
        (*v).data = i;
        (*v).next = null;
        return v;
    }

    fn insert(mut self, val i32) {
        let mut temp *mut LinkedList = self;
        while (*temp).next != null {
            temp = (*temp).next;
        }
        let newlist = LinkedList::new_list(val);
        (*temp).next = newlist;
    }

    fn next(mut self) -> *mut LinkedList {
        return (*self).next;
    }


    fn reverse(mut self, mut head *mut *mut LinkedList) {
        let mut next = self;
        let mut cur = self;
        let mut pre *mut LinkedList = null;
        while cur != null {
            cur = (*cur).next;
            (*next).next = pre;
            pre = next;
            next = cur;
        }
        *head = pre;
    }

    fn print(mut self) {
        printf("null -> ");
        let mut temp = self;
        while temp != null {
            printf(" %d ", (*temp).data);
            printf(" -> ");
            temp = (*temp).next;
        }
        printf("null\n");
    }

    fn search(mut self, val i32) -> bool {
        while self != null {
            if (*self).data == val {
                return true;
            }
            self = (*self).next;
        }
        return false;
    }

    fn deleteNode(mut head *mut *mut LinkedList, val i32) {
        if *head == null {
            return;
        }
        if (**head).data == val {
            let t = *head;
            *head = (**head).next;
            free(@asVoidPtr(t));
            return;
        }
        LinkedList::deleteNode(&mut (**head).next, val);
    }

    fn delete_root(mut self) -> *mut LinkedList {
        let var = (*self).next;
        free(@asVoidPtr(self));
        return var;
    }

    fn delete_list(mut self) {
        while self != null {
            self = (*self).delete_root();
        }
    }

    fn delete(mut self, mut var *mut *mut LinkedList, val i32)  {
        if self == null {
            return;
        }
        let mut node  = self;
        let mut pre = self;
        while node != null && (*node).data != val {
            pre = node;
            node = (*node).next;
        }
        if (*node).data != val {
            return;
        }

        if pre == node {
            *var = (*node).delete_root();
            return;
        }

        if (*node).next == null {
            free(@asVoidPtr(node));
            return;
        }
        let next = (*node).next;
        free(@asVoidPtr(node));
        (*pre).next = next;
    }
}

/*
fn main() -> i32{
    let mut q = LinkedList::new_list(0);
    for i in 0..100 {
        (*q).insert(i);
    }
    (*q).print();
    (*q).delete(&mut q, 0);
    for i in 0..100 {
        (*q).delete(&mut q, i);
    }
    return 0;
}
*/