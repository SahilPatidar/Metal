extern fn malloc;
extern fn free;
extern fn printf;





/*enum Color{
    Color::RED,
    Color::BLACK,
}
struct Node{
    color Color,
    key i32,
    parent *mut Node,
    left *mut Node,
    right *mut Node,
}

interface Node {
    fn new_node(key i32) -> *mut Node {
        let mut node = new(1, Node);
        (*node).color = Color::Color::RED;
        (*node).key = key;
        (*node).parent = null;
        (*node).left = null;
        (*node).right = null;
        return node;
    }

    ///*
     x                 y
      \               / \
       y  -------->  x   b
      / \             \
     a   b             a

    //*/

    fn left_rotating(mut self) -> *mut Node {
        if (*self).right == null {
            return self;
        }

        let parent = self->parent;
        let mut right = self->right;
        let mut r_left = (*right).left;
        self->right = r_left;
        (*right).left = self;
        self->parent = right;
        if r_left != null {
            (*r_left).parent = self;
        }

        if parent == null {
            return right;
        }

        if (*parent).left == self {
            (*parent).left = right;
        }else {
            (*parent).right = right;
        }

        return right;
    }

   // /*
         x              y
        /              / \
       y  -------->   a   x   
      / \                / 
     a   b              b 

    //*/

    fn right_rotating(mut self) -> *mut Node  {
        if self == null {
            return self;
        }
        let parent = self->parent;

        let mut left = self->left;
        let mut l_right = (*left).right;
        self->left = l_right;
        (*left).right = self;
        (*self).parent = left;
        if l_right != null {
            (*l_right).parent = self;
        }
        if parent == null {
            return left;
        }
        if (*parent).left == self {
            (*parent).left = left;
        }else {
            (*parent).right = left;
        }

        return left;
    }

    fn uncle(mut self) -> *mut Node {
        if self->parent == null {
            return null;
        }
        if (*(*self).parent).left == self{
            return (*(*self).parent).right;
        }
        return (*(*self).parent).left;
    }



    fn fixup_tree(node *mut Node) {
        let mut parent = (*node).parent;
        while (*parent).color == Color::Color::RED {
            let mut uncle = (*parent).uncle();
            if (*uncle).color == Color::Color::RED {
                (*uncle).color = Color::Color::BLACK;
                (*parent).color = Color::Color::BLACK;
                (*(*parent).parent).color = Color::Color::RED;
                node = (*parent).parent;

            }else if (*parent).right == node {
                parent = (*parent).left_rotating();
                node = parent;

            }else if (*parent).left == node {
                parent = (*parent).right_rotating();
                node = parent;

            }else if parent == (*(*parent).parent).left {
                (*parent).color = Color::Color::BLACK;
                (*(*parent).parent).color = Color::Color::RED;
                (*(*parent).parent).right_rotating();

            }else if parent == (*(*parent).parent).right {
                (*parent).color = Color::Color::BLACK;
                (*(*parent).parent).color = Color::Color::RED;
                (*(*parent).parent).left_rotating();

            }

            parent = (*node).parent;
        }
    }

    fn fixup_tree(node *mut Node) {
        let mut parent = (*node).parent;
        while (*parent).color == Color::Color::RED {
            let mut uncle = (*parent).uncle();
            if (*uncle).color == Color::Color::RED {
                (*uncle).color = Color::Color::BLACK;
                (*parent).color = Color::Color::BLACK;
                (*(*parent).parent).color = Color::Color::RED;
                node = (*parent).parent;

            }else {
                if (*parent).right == node {
                    parent = (*parent).left_rotating();
                    node = parent;
                }

                (*parent).color = Color::Color::BLACK;
                (*(*parent).parent).color = Color::Color::RED;
                (*(*parent).parent).right_rotating();
            }else {
                if (*parent).left == node {
                    parent = (*parent).right_rotating();
                    node = parent;
                }

                (*parent).color = Color::Color::BLACK;
                (*(*parent).parent).color = Color::Color::RED;
                (*(*parent).parent).left_rotating();
            }
            if(root == node) {
                break;
            }
            parent = (*node).parent;
        }
        (*root).color = Color::Color::BLACK;
    }


    fn insert(mut self, key i32) {
        if(self == null) {
            return;
        }

        while self != null {
            let V = (*self).key;
            if V > key {
                self = (*self).left;
            }else {
                self = (*self).right;
            }
        }
        let newn = Node::new_node(key);
        if (*self).key > key {
            (*self).left = newn;
        }else {
            (*self).right = newn;
        }
        (*newn).parent = self;
        Node::fixup_tree(newn);
    }

    fn delete(mut self, key i32) {
        if self == null {
            return;
        }

        let mut parent *mut Node = null;
        
        while self != null && (*self).key != key {
            let V = (*self).key;
            parent = self;
            if V > key {
                self = (*self).left;
            }else if V < key {
                self = (*self).right;
            }
        }
        
        if (*self).key != key {
            return;
        }

        if (*self).left == null || (*self).right == null {
            let mut newNode *mut Node = null;
            if (*self).left != null {
                newNode = (*self).left;
            }else {
                newNode = (*self).right;
            }


            if parent != null {
                if self == (*parent).left {
                    (*parent).left = newNode;
                }else {
                    (*parent).right = newNode;
                }
            }
            (*newnode).parent = parent;
            del(self);
            self = newNode;
        }else {
            let mut succ = (*self).right;
            let mut pColor::RED = self;
            while (*succ).left != null {
                pColor::RED = succ;
                succ = (*succ).left;
            }
            if self == pColor::RED {
                (*self).key = (*succ).key;
            }else {
                (*self).key = (*pColor::RED).key;
            }
            del(succ);
        }

        Node::fixup_tree(self);
    }

    fn print(mut self) {
        printf("\n");
        printf("key = %d - ", (*self).key);
        if (*self).color == Color::Color::BLACK {
            printf("color = Color::BLACK ");
        }else {
            printf("color = Color::RED ");
        }
        printf("\n");
        print(self->left);
        print(self->right);
    }
}


fn main() -> i32 {
    let mut rbt = Node::new_node(5);
    (*rbt).insert(2);
    (*rbt).insert(6);
    (*rbt).insert(7);
    (*rbt).insert(3);
    (*rbt).insert(9);
    (*rbt).insert(4);
    (*rbt).insert(1);

    (*rbt).print();

    (*rbt).delete(2);
    (*rbt).delete(6);
    (*rbt).delete(7);
    (*rbt).delete(3);
    (*rbt).delete(9);
    (*rbt).delete(4);
    (*rbt).delete(1);
    (*rbt).delete(5);
    return 0;
}
*/