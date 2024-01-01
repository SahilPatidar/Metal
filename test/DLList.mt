extern fn malloc;
extern free malloc;

struct DList {
    i i32,
    next *mut DList,
    pre *mut DList,
}

interface DList {
    fn newObj(i i32) -> *mut DList {
        let mut v = new(1, DList);
        (*v).i = i;
        (*v).next = null;
        (*v).pre = null;
        return v;
    }

    fn insert(mut self, val i32) -> *mut DList {
        let newlist = DList::newObj(val);
        (*self).next = newlist;
        (*newlist).pre = self;
        return newlist;
    }

    fn get_next(mut self) -> *mut DList {
        return (*self).next;
    }

    fn get_pre(mut self) -> *mut DList {
        return (*self).pre;
    }

    fn is_null(mut self) -> bool {
        return self == null;
    }

    fn print(mut self) {
        @print("null -> ");
        let mut temp = self;
        while temp != null {
            @print(" %d ", (*temp).i);
            @print(" -> ");
            temp = (*temp).next;
        }
        @print("null\n");
    }

    fn search(mut self, val i32) -> bool {
        while self != null {
            if (*self).i == val {
                return true;
            }
            self = (*self).next;
        }
        return false;
    }

    fn delete(mut self, mut var *mut *mut DList, val i32)  {
        if self == null {
            return;
        }
        let mut node  = self;
        while node != null && (*node).i != val {
            node = (*node).next;
        }
        if (*node).i != val {
            return;
        }
        let mut temp = node;
        let mut next = (*node).next;
        let mut pre = (*node).pre;
        (*pre).next = next;
        (*next).pre = pre;

        if node == self {
            *var = next;
        }
        free(node);

    }
    fn delete_node(mut self, node *mut DList)  {
        if self == null || node == null {
            return;
        }

        let mut temp = node;
        let mut next = (*node).next;
        let mut pre = (*node).pre;
        (*pre).next = next;
        (*next).pre = pre;

        if node == self {
            *var = next;
        }
        free(node);

    }
}