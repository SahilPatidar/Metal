extern fn printf;
extern fn malloc;
extern fn exit;

struct rbNode {
    i i32, 
    link [2] *mut rbNode,
}


fn createNode(data i32) -> *mut rbNode {
  let newnode *mut rbNode = malloc(@szof(rbNode)) as *mut rbNode;
  (*newnode).i = data;
  (*newnode).link[1] = null;
  (*newnode).link[0] = null;
  return newnode;
}


fn main() -> i32 {
    let v [2]*mut rbNode = [createNode(0), createNode(1)];
    (*v[0]).link[0] = createNode(10);
    (*v[0]).link[1] = createNode(12);
    printf("%d\n", v[0]->link[0]->i);
    printf("%d\n", v[0]->link[1]->i);

    return 0;
}


