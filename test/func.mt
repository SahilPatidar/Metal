//mod folder;
/*
struct foo {
    i i32
}

struct foofoo {
    i [10]i32
}

struct foobar {
    i [10] *const i8
}
*/


/*



fn bar(mut i *mut [2]i32) {
    (*i)[0] = 0;
}

fn main() -> i32 {
    let mut v [2]i32 = [4,5];
    @print("%d\n", v[0]);
    bar(&mut v);
    @print("%d\n", v[0]);
   return 0;
}

struct _bar {
    i *mut i32
}

fn bar(mut f foo) {
    @print("%d\n", f.i);
    f.i = 3;
    @print("%d\n", f.i);
    let mut i3 = 0;
    let v _bar = _bar{i: &mut i3};
    @print("%d\n", *v.i);
    (*v.i) = 5565;
    @print("%d\n", *v.i);
}
*/
/*
fn bar(mut i i64) -> i64 {
    if(i == 1){
        return 1;
    }
    return i*bar(i-1);
}

fn main() {
    let mut v foo = foo{i:1};
    @print("%d\n", v.i);

    while v.i <= 10 {
        @print("mul=%lld\n", bar(v.i as i64));
        if v.i == 6 {
            @print("break == %d\n", v.i);
            v.i+=1;
            continue;
        }else if v.i == 9{
            break;
        }
        v.i += 1;
        @print("%d\n", v.i);
    }
}
*/
/*
fn main() {
    //let mut v2 *mut foo = new(1,foo);
    let mut v = new(5, i32);

    let mut v2 = &mut v;
    let mut v3 = &mut v2;
    for let mut i = 0; i < 5; i+=1 {
        v[i] = i;
    }
    for let mut i = 0; i < 5; i+=1 {
        @print("%d\n", (**v3)[i]);
    }
    
    del(**v3);
}
*/
/*
interface foofoo{
    fn newObj() -> *mut foofoo{
        let mut v = new(1,foofoo);
        return v;
    }
    fn getVal(mut self, _i i32) -> i32 {
        return (*self).i[_i];
    }
    fn setVal(mut self, _i i32, _val i32)  {
         (*self).i[_i] = _val;
    }
    fn delete(mut self) {
        del(self);
    }
}

fn main() {
    let mut v = foofoo::newObj();
    for let mut i = 0; i < 10; i+=1 {
        (*v).setVal(i, i+1);
        @print("value is `%d`\n", (*v).getVal(i));
    }
    for let mut i = 0; i < 10; i+=1 {
        @print("value is `%d`\n", (*v).getVal(i));
    }
    (*v).delete();
}
*/

/*
interface foobar{
    fn newObj() -> *mut foobar{
        let mut v = new(1,foobar);
        return v;
    }
    fn getVal(mut self, _i i32) -> *const i8 {
        return (*self).i[_i];
    }
    fn setVal(mut self, _i i32, _val *const i8)  {
         (*self).i[_i] = _val;
    }
    fn delete(mut self) {
        del(self);
    }
}

fn main() {
    let mut v = foobar::newObj();
    for let mut i = 0; i < 10; i+=1 {
        (*v).i[i] = "0";
        //let str = (*v).getVal(i);
       @print("value is `%s`\n", (*v).getVal(i));
   }
    for let mut i = 0; i < 10; i+=1 {
        @print("value is `%s`\n", (*v).getVal(i));
    }
    (*v).delete();
}
*/

/*
struct LinkedList {
    i i32,
    next *mut LinkedList
}

interface LinkedList {
    fn newObj(i i32) -> *mut LinkedList {
        let mut v = new(1, LinkedList);
        (*v).i = i;
        (*v).next = null;
        return v;
    }
    fn insert(mut self, val i32) {
        let mut temp *mut LinkedList = self;
        while (*temp).next != null {
            temp = (*temp).next;
        }
        let newlist = LinkedList::newObj(val);
        (*temp).next = newlist;
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

    fn deleteNode(mut head *mut *mut LinkedList, val i32) {
        if *head == null {
            return;
        }
        if (**head).i == val {
            let t = *head;
            *head = (**head).next;
            del(t);
            return;
        }
        LinkedList::deleteNode(&mut (**head).next, val);
    }

    fn delete(mut self, mut var *mut *mut LinkedList, val i32)  {
        if self == null {
            return;
        }
        let mut node  = self;
        let mut pre = self;
        while node != null && (*node).i != val {
            pre = node;
            node = (*node).next;
        }
        if (*node).i != val {
            return;
        }

        if pre == node {
            *var = (*self).next;
            del(node);
            return;
        }

        if (*node).next == null {
            del(node);
            return;
        }
        let next = (*node).next;
        del(node);
        (*pre).next = next;
    }
}


fn main() {
    let mut v = LinkedList::newObj(0);
    for let mut i = 1; i <= 10; i+=1 {
        (*v).insert(i);
   }
    (*v).print();
    (*v).reverse(&mut v);
    (*v).print();
    if (*v).search(86)  {
        @print("\ntrue\n\n");
    }

    for let mut i = 0; i <= 10; i+=1 {
        if v == null {
            @print("err :: nullptr");
        }
        (*v).delete(&mut v,i);
        //LinkedList::deleteNode(&mut v, i);
        @print("next\n");
   }
   if v == null {
    @print("errr null\n");
    return;
   }
    //(*v).print();
}*/

/*
fn factorial(n i32) -> i32{
	if n==0 {
		return 1;
	}
    return n * factorial(n - 1);
}

fn main(){
	@print("%d\n", factorial(5));
}
*/

