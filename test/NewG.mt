use malloc;
use free;

struct Node {
    dest i32,
    weight i32,
    next *mut Node
}
// Structure to represent the adjacency list
struct List {
    head *mut Node
}

// Structure to represent the graph
struct Graph {
    V i32,
    array *mut List
}

interface Graph {
    fn new_node(dest i32, weight i32) -> *mut Node {
        let mut node = malloc(@szof(Node)) as *mut Node;
        node->dest = dest;
        node->weight = weight;
        node->next = null;
        return node;
    }

    // Function to create a graph with V vertices
    fn create_graph(V i32) -> *mut Graph {
        let graph = malloc(@szof(Graph)) as *mut Graph;
        graph->V = V;
        
        // Create an array of adjacency lists, size of V
        graph->array = malloc(V as ui64 * @szof(List)) as *mut List;
        
        // Initialize each adjacency list as empty by making head as null
        for i in 0..V {
            graph->array[i].head = null;
        }
        return graph;
    }

    // Function to add an edge to an undirected graph
    fn add_edge(mut self, src i32, dest i32, weight i32) {
        // Add an edge from src to dest
        let mut node *mut Node = Graph::new_node(dest, weight);
        node->next = self->array[src].head;
        self->array[src].head = node;

        // Add an edge from dest to src since the graph is undirected
        node = Graph::new_node(src, weight);
        node->next = self->array[dest].head;
        self->array[dest].head = node;
    }


    fn delete_graph(mut self) {
        for i in 0..self->V {
            let mut list = self->array[i].head;
            while list != null {
                let ptr = list;
                list = ptr->next;
                free(@asVoidPtr(ptr));
            }
            self->array[i].head = list;
        }
        free(@asVoidPtr(self));
    }
}