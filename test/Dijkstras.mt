extern fn malloc;
extern fn free;
extern fn printf;

mod NewG;

use NewG::Graph;
const INT_MAX i32 = 320000;
const V i32 = 10;


fn get_min(dist [V]i32, visit [V]bool) -> i32 {
    let mut min = INT_MAX;
    let mut min_u = -1;
    for i in 0..V {
        if !visit[i] && dist[i] < min {
            min = dist[i];
            min_u = i;
        }
    }
    return min_u;
}

fn printSolution(dist [V]i32) {
    printf("Vertex \t Distance from Source\n");
    for i in  0..V {
        printf("%d \t %d\n", i, dist[i]);
    }
}

fn Dijkstra(mut graph *mut Graph, k i32) {
    let mut visit [V]bool;
    let mut dist [V]i32;
    
    for i in 0..V {
        visit[i] = false;
        dist[i] = INT_MAX;
    }

    dist[k] = 0;

    for i in 0..V {

        let mut u = get_min(dist, visit);
        visit[u]  = true;
        let mut list = graph->array[u].head;
        while list != null {
            let weight = list->weight;
            let v = list->dest;
            if !visit[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v] {
                dist[v] = dist[u] + weight;
            }
    
            list = list->next;
        }
    }
    printSolution(dist);

}

fn main() -> i32 {
    let mut graph *mut Graph = Graph::create_graph(V); 
    graph->add_edge(0, 1, 4);
    graph->add_edge(0, 7, 8);
    graph->add_edge(1, 2, 8);
    graph->add_edge(1, 7, 11);
    graph->add_edge(2, 3, 7);
    graph->add_edge(2, 8, 2);
    graph->add_edge(2, 5, 4);
    graph->add_edge(3, 4, 9);
    graph->add_edge(3, 5, 14);
    graph->add_edge(4, 5, 10);
    graph->add_edge(5, 6, 2);
    graph->add_edge(6, 7, 1);
    graph->add_edge(6, 8, 6);
    graph->add_edge(7, 8, 7);
    Dijkstra(graph, 0);
    graph->delete_graph();
    return 0;
}

