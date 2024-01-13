/*mod LinkedList;
mod Queue;*/
use LinkedList::LinkedList as LL;
use Queue::queue;
/*
extern fn malloc;
extern fn free;
extern fn printf;
*/
use malloc;
use free;
use printf;
struct Graph{
    node [9]*mut LL
}

struct Node{
    edge *mut LL
}

interface Graph {
    fn new_graph() -> *mut Graph {
        let mut new_g = malloc(@szof(Graph)) as *mut Graph;
        for i in 0..9 {
            (*new_g).node[i] = null;
        }
        return new_g;
    }

    fn add_edge(mut self, v i32, e i32)  {
        if (*self).node[v] == null {
            (*self).node[v] = LL::new_list(e);
            printf("%d - %d\n", v, e);
            printf("%d - %d\n", v, (*(*self).node[v]).i);
        }else {
            let mut vert = (*self).node[v];
            (*vert).insert(e);
            printf("%d - %d\n", v, e);
            printf("%d - %d\n", v, (*(*self).node[v]).i);
        }
        printf("-------------\n");
    }

    fn delete_g(mut self) {
        for i in 0..9 {
            (*(*self).node[i]).delete_list();
            (*self).node[i] = null;
        }
    }

    fn bfs_search(mut self)  {
        let mut q  = queue::new_qeue(0);
        //let mut q = *_q;
        let mut visit [9]bool;
        for i in 0..9 {
            visit[i] = false;
        }

        while !(*q).empty() {
            let mut vert = (*q).front();
            (*q).pop();
            visit[vert] = true;
            let mut l = (*self).node[vert];
            for ; l != null; l = (*l).next {
                let mut i = (*l).i;
                if !visit[i] {
                    (*q).push(i);
                    printf("%d - %d\n", vert, i);
                    printf("\n-----------------------\n");
                }
            } 
        }
    }
}
/*
fn main() -> i32{
    let mut g = Graph::new_graph();
    (*g).add_edge(0, 1);
    (*g).add_edge(1, 2);
    (*g).add_edge(2, 4);
    (*g).add_edge(2, 3);
    (*g).add_edge(4, 5);
    (*g).add_edge(5, 3);
    (*g).add_edge(5, 7);
    (*g).add_edge(5, 8);
    (*g).add_edge(8, 7);
    (*g).add_edge(8, 9);
    (*g).bfs_search();  
    printf("\n");
    (*g).delete_g();  
    free(@asVoidPtr(g));
    
    return 0;
}
*/