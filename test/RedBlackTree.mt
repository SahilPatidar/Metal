extern fn malloc;
extern fn free;
extern fn printf;
extern fn scanf;



enum Color {
  RED,
  BLACK
}

struct rbNode {
    data i32, 
    color Color,
    link [2] *mut rbNode,
}

let mut root *mut rbNode = null;

// Create a Color::RED-Color::BLACK tree
fn createNode(data i32) -> *mut rbNode {
  let newnode *mut rbNode = malloc(@szof(rbNode)) as *mut rbNode;
  (*newnode).data = data;
  (*newnode).color = Color::RED;
  (*newnode).link[1] = null;
  (*newnode).link[0] = null;
  return newnode;
}

// Insert an node
fn insertion(data i32) {
  let mut stack [98] *mut rbNode ;
  let mut ptr *mut rbNode = null;
  let mut newnode *mut rbNode = null;
  let mut xPtr *mut rbNode = null;
  let mut yPtr *mut rbNode = null;

  let mut dir [98]i32;
  let mut ht i32 = 0;
  let mut index i32 =0;
  ptr = root;
  if root == null{
    root = createNode(data);
    return;
  }
  stack[ht] = root;
  dir[ht] = 0;
  ht+=1;

  while ptr != null {

    if (*ptr).data == data {
      printf("Duplicates Not Allowed!!\n");
      return;
    }
    if (data - (*ptr).data) > 0 {
      index = 1;
    }else {
      index = 0;
    }

    stack[ht] = ptr;
    ptr = (*ptr).link[index];
    dir[ht] = index;
    ht+=1;

  }

  newnode = createNode(data);

  (*stack[ht - 1]).link[index] = newnode;
  while (ht >= 3) && ((*stack[ht - 1]).color == Color::RED) {

    if dir[ht - 2] == 0 {


      yPtr = (*stack[ht - 2]).link[1];

      if yPtr != null && (*yPtr).color == Color::RED {

        (*stack[ht - 2]).color = Color::RED;
        (*yPtr).color = Color::BLACK;
        (*stack[ht - 1]).color = (*yPtr).color;
        ht = ht - 2;

      } else {

        if (dir[ht - 1] == 0) {
          yPtr = stack[ht - 1];

        } else {

          xPtr = stack[ht - 1];
          yPtr = (*xPtr).link[1];
          (*xPtr).link[1] = (*yPtr).link[0];
          (*yPtr).link[0] = xPtr;
          (*stack[ht - 2]).link[0] = yPtr;

        }
        xPtr = stack[ht - 2];
        (*xPtr).color = Color::RED;
        (*yPtr).color = Color::BLACK;
        (*xPtr).link[0] = (*yPtr).link[1];
        (*yPtr).link[1] = xPtr;

        if xPtr == root {
          root = yPtr;

        } else {
          (*stack[ht - 3]).link[dir[ht - 3]] = yPtr;
        }

        break;
      }
    } else {


      yPtr = (*stack[ht - 2]).link[0];
      if (yPtr != null) && ((*yPtr).color == Color::RED) {

        (*stack[ht - 2]).color = Color::RED;
        (*yPtr).color = Color::BLACK;
        (*stack[ht - 1]).color = Color::BLACK;
        ht = ht - 2;

      } else {
        if dir[ht - 1] == 1 {
          yPtr = stack[ht - 1];

        } else {

          xPtr = stack[ht - 1];
          yPtr = (*xPtr).link[0];
          (*xPtr).link[0] = (*yPtr).link[1];
          (*yPtr).link[1] = xPtr;
          (*stack[ht - 2]).link[1] = yPtr;

        }
        xPtr = stack[ht - 2];
        (*yPtr).color = Color::BLACK;
        (*xPtr).color = Color::RED;
        (*xPtr).link[1] = (*yPtr).link[0];
        (*yPtr).link[0] = xPtr;
        if (xPtr == root) {
          root = yPtr;
        } else {
          (*stack[ht - 3]).link[dir[ht - 3]] = yPtr;
        }

        break;
      }
    }
  }

  (*root).color = Color::BLACK;
}


// Delete a node
fn deletion(data i32) {
  let mut stack[98] *mut rbNode;
  let mut ptr *mut rbNode;
  let mut xPtr *mut rbNode;
  let mut yPtr *mut rbNode;

  let mut pPtr *mut rbNode;
  let mut qPtr *mut rbNode;
  let mut rPtr *mut rbNode;

  let mut dir [98]i32;
  let mut ht  i32 = 0;
  let mut diff i32;
  let mut i i32;

    let mut color Color;

  if root == null {
    printf("Tree not available\n");
    return;
  }

  ptr = root;
  while ptr != null {
    if (data - (*ptr).data) == 0 {
      break;
    }
    if (data - (*ptr).data) > 0 {
      diff = 1;
    }else {
      diff = 0;
    }
    stack[ht] = ptr;
    dir[ht] = diff;
    ht+=1;
    ptr = (*ptr).link[diff];
  }

  if ((*ptr).link[1] == null) {
    if (((ptr == root) && ((*ptr).link[0] == null))) {
      free(@asVoidPtr(ptr));
      root = null;
    } else if (ptr == root) {
      root = (*ptr).link[0];
      free(@asVoidPtr(ptr));
    } else {
      (*stack[ht - 1]).link[dir[ht - 1]] = (*ptr).link[0];
    }
  } else {
    xPtr = (*ptr).link[1];
    if ((*xPtr).link[0] == null) {
      (*xPtr).link[0] = (*ptr).link[0];
      color = (*xPtr).color;
      (*xPtr).color = (*ptr).color;
      (*ptr).color = color;

      if (ptr == root) {
        root = xPtr;
      } else {
        (*stack[ht - 1]).link[dir[ht - 1]] = xPtr;
      }

      dir[ht] = 1;
      stack[ht] = xPtr;
      ht+=1;
    } else {
      i = ht;
      ht+=1;
      while true {
        dir[ht] = 0;
        stack[ht] = xPtr;
        ht+=1;
        yPtr = (*xPtr).link[0];
        if ((*yPtr).link[0] == null) {
          break;
        }
        xPtr = yPtr;
      }

      dir[i] = 1;
      stack[i] = yPtr;
      if (i > 0 ){
        stack[i - 1]->link[dir[i - 1]] = yPtr;
      }

      (*yPtr).link[0] = (*ptr).link[0];

      (*xPtr).link[0] = (*yPtr).link[1];
      (*yPtr).link[1] = (*ptr).link[1];

      if( ptr == root) {
        root = yPtr;
      }

      color = (*yPtr).color;
      (*yPtr).color = (*ptr).color;
      (*ptr).color = color;
    }
  }

  if (ht < 1) {
    return;
  }

  if ((*ptr).color == Color::BLACK) {
    while true {
      pPtr = (*stack[ht - 1]).link[dir[ht - 1]];
      if (pPtr != null && (*pPtr).color == Color::RED) {
        (*pPtr).color = Color::BLACK;
        break;
      }

      if (ht < 2) {
        break;
      }

      if (dir[ht - 2] == 0) {
        rPtr = (*stack[ht - 1]).link[1];

        if (rPtr == null) {
          break;
        }

        if ((*rPtr).color == Color::RED) {
          (*stack[ht - 1]).color = Color::RED;
          (*rPtr).color = Color::BLACK;
          (*stack[ht - 1]).link[1] = (*rPtr).link[0];
          (*rPtr).link[0] = stack[ht - 1];

          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            (*stack[ht - 2]).link[dir[ht - 2]] = rPtr;
          }
          dir[ht] = 0;
          stack[ht] = stack[ht - 1];
          stack[ht - 1] = rPtr;
          ht+=1;

          rPtr = (*stack[ht - 1]).link[1];
        }

        if (((*rPtr).link[0] == null || (*(*rPtr).link[0]).color == Color::BLACK) &&
          ((*rPtr).link[1] == null || (*(*rPtr).link[1]).color == Color::BLACK)) {
          (*rPtr).color = Color::RED;
        } else {
          if ((*rPtr).link[1] == null || (*(*rPtr).link[1]).color == Color::BLACK) {
            qPtr = (*rPtr).link[0];
            (*rPtr).color = Color::RED;
            (*qPtr).color = Color::BLACK;
            (*rPtr).link[0] = (*qPtr).link[1];
            (*qPtr).link[1] = rPtr;
            (*stack[ht - 1]).link[1] = qPtr;
            rPtr = qPtr;
          }
          (*rPtr).color = (*stack[ht - 1]).color;
          (*stack[ht - 1]).color = Color::BLACK;
          (*(*rPtr).link[1]).color = Color::BLACK;
          (*stack[ht - 1]).link[1] = (*rPtr).link[0];
          (*rPtr).link[0] = stack[ht - 1];
          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            (*stack[ht - 2]).link[dir[ht - 2]] = rPtr;
          }
          break;
        }
      } else {
        rPtr = (*stack[ht - 1]).link[0];
        if (rPtr == null) {
          break;
        }
        
        if ((*rPtr).color == Color::RED) {
          (*stack[ht - 1]).color = Color::RED;
          (*rPtr).color = Color::BLACK;
          (*stack[ht - 1]).link[0] = (*rPtr).link[1];
          (*rPtr).link[1] = stack[ht - 1];

          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            (*stack[ht - 2]).link[dir[ht - 2]] = rPtr;
          }
          dir[ht] = 1;
          stack[ht] = stack[ht - 1];
          stack[ht - 1] = rPtr;
          ht+=1;

          rPtr = (*stack[ht - 1]).link[0];
        }

        if ((!((*rPtr).link[0] != null) || (*(*rPtr).link[0]).color == Color::BLACK) &&
          (!((*rPtr).link[1] != null) || (*(*rPtr).link[1]).color == Color::BLACK)) {
          (*rPtr).color = Color::RED;
        } else {
          if (!((*rPtr).link[0] != null) || (*(*rPtr).link[0]).color == Color::BLACK) {
            qPtr = (*rPtr).link[1];
            (*rPtr).color = Color::RED;
            (*qPtr).color = Color::BLACK;
            (*rPtr).link[1] = (*qPtr).link[0];
            (*qPtr).link[0] = rPtr;
            (*stack[ht - 1]).link[0] = qPtr;
            rPtr = qPtr;
          }
          (*rPtr).color = (*stack[ht - 1]).color;
          (*stack[ht - 1]).color = Color::BLACK;
          (*(*rPtr).link[0]).color = Color::BLACK;
          (*stack[ht - 1]).link[0] = (*rPtr).link[1];
          (*rPtr).link[1] = stack[ht - 1];
          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            (*stack[ht - 2]).link[dir[ht - 2]] = rPtr;
          }
          break;
        }
      }
      ht-=1;
    }
  }
}

// Print the inorder traversal of the tree
fn inorderTraversal(node *mut rbNode) {
  if node != null{
    printf("%d  ", (*node).data);
    inorderTraversal((*node).link[0]);
    inorderTraversal((*node).link[1]);
  }
  return;
}

// Driver code
fn main() -> i32{
  let mut ch i32 = -1;
  let mut data i32 = -1;
  printf("sizeof = %d\n", @szof(rbNode) as i32);
  while true {
    printf("1. Insertion\t2. Deletion\n");
    printf("3. Traverse\t4. Exit");
    printf("\nEnter your choice:");
    scanf("%d", &ch);
    if ch == 1 {
        printf("Enter the element to insert:");
        scanf("%d", &data);
        printf("inserting..... %d\n", data);
        insertion(data);
    }else if ch == 2 {
        printf("Enter the element to delete:");
        scanf("%d", &data);
        deletion(data);
    }else if ch == 3 {
        inorderTraversal(root);
        printf("\n");
    }else if ch == 4 {
        break;
    }else {
        printf("Not available\n");
    }
    printf("................................................................\n");
}
  return 0;
}

