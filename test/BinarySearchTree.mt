extern fn printf;
extern fn malloc;
extern fn free;

struct TreeNode {
    Val i32,
    Left *mut TreeNode,
    Right *mut TreeNode,
}

interface TreeNode{
    fn newObj(val i32) -> *mut TreeNode {
        let temp = malloc(@szof(TreeNode)) as *mut TreeNode;
        (*temp).Val = val;
        (*temp).Left = null;
        (*temp).Right = null;
        return temp;
    }

    fn insert(mut self, val i32) {
        while self != null && ((*self).Left != null && (*self).Right != null) {
            let V = (*self).Val;
            if V > val {
                self = (*self).Left;
            }else {
                self = (*self).Right;
            }
        }

        while ((*self).Left != null) && (*(*self).Left).Val > val {
            self = (*self).Left;
        }

        while ((*self).Right != null) && (*(*self).Right).Val < val {
            self = (*self).Right;
        }
        let newNode = TreeNode::newObj(val);
        if (*self).Val > val {
            if (*self).Left != null {
                let L = (*self).Left;
                let R = (*L).Right;
                (*L).Right = null;
                (*newNode).Left = L;
                (*newNode).Right = R;
            } 
            (*self).Left = newNode;
        }else if (*self).Val < val {
            if (*self).Right != null {
                let R = (*self).Right;
                let L = (*R).Left;
                (*R).Left = null;
                (*newNode).Right = R;
                (*newNode).Left = L;
            } 
            (*self).Right = newNode;
        }
    }

    fn inoreder_treverser(mut self) {
        if self == null {
            return;
        }
        printf("%d -> ", (*self).Val);
        inoreder_treverser((*self).Left);
        printf("\n");
        inoreder_treverser((*self).Right);
        return;
    }

    fn delete(mut self, mut Tree *mut *mut TreeNode, val i32) {
        if self == null {
            return;
        }

        let mut parent *mut TreeNode = null;
        
        while self != null && (*self).Val != val {
            let V = (*self).Val;
            parent = self;
            if V > val {
                self = (*self).Left;
            }else if V < val {
                self = (*self).Right;
            }
        }
        
        if (*self).Val != val {
            return;
        }

        if (*self).Left == null || (*self).Right == null {
            let mut newNode *mut TreeNode = null;
            if (*self).Left != null {
                newNode = (*self).Left;
            }else {
                newNode = (*self).Right;
            }


            if parent == null {
                *Tree = newNode;
                free(@asVoidPtr(self));
                return;
            }

            if self == (*parent).Left {
                (*parent).Left = newNode;
            }else {
                (*parent).Right = newNode;
            }
            free(@asVoidPtr(self));
        }else {
            let mut succ = (*self).Right;
            let mut pred = self;
            while (*succ).Left != null {
                pred = succ;
                succ = (*succ).Left;
            }
            if self == pred {
                (*self).Val = (*succ).Val;
            }else {
                (*self).Val = (*pred).Val;
            }
            free(@asVoidPtr(succ));
        }

    }
}


fn main() -> i32 {
    let mut Tree = TreeNode::newObj(0);

    for let mut i = 0; i < 10; i += 1 {
        (*Tree).insert(i);
    }
    (*Tree).inoreder_treverser();
    for let mut i = 0; i < 10; i += 1 {
        (*Tree).delete(&mut Tree, i);
        printf("\n");
    }
    return 0;
}