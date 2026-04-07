#include <stdio.h>

#define MAX_NODES 3005
#define MAX_EDGES 10005
#define MAX_EDGES_STORAGE (2 * MAX_EDGES + 5)

int node_count;
int edge_count;
int graph_type;
int source_node;
int target_node;
int edge_from[MAX_EDGES];
int edge_to[MAX_EDGES];
int first_edge_id[MAX_EDGES];

int node_first_arc[MAX_NODES];
int node_last_arc[MAX_NODES];
int next_arc[MAX_EDGES_STORAGE];
int arc_target[MAX_EDGES_STORAGE];
int arc_capacity[MAX_EDGES_STORAGE];
int reverse_arc[MAX_EDGES_STORAGE];
int arc_counter;

int node_first_used[MAX_NODES];
int node_last_used[MAX_NODES];
int next_used[MAX_EDGES];
int used_u[MAX_EDGES];
int used_v[MAX_EDGES];
int used_id[MAX_EDGES];
int used_alive[MAX_EDGES];
int used_counter;

int bfs_queue[MAX_NODES];
int parent_vertex[MAX_NODES];
int parent_edge_index[MAX_NODES];
int visited_flag[MAX_NODES];
int visit_timer;
int current_path[MAX_EDGES];
int path_length;

void add_to_vertex_list(int vertex, int edge_index, int first[], int last[], int next[]) {
    if (first[vertex] == -1) first[vertex] = edge_index;
    else next[last[vertex]] = edge_index;
    last[vertex] = edge_index;
    next[edge_index] = -1;
}

void add_directed_arc(int from_vertex, int to_vertex, int edge_id) {
    int forward_arc = arc_counter, backward_arc = arc_counter + 1;
    arc_target[forward_arc] = to_vertex;
    arc_capacity[forward_arc] = 1;
    reverse_arc[forward_arc] = backward_arc;
    arc_target[backward_arc] = from_vertex;
    arc_capacity[backward_arc] = 0;
    reverse_arc[backward_arc] = forward_arc;
    add_to_vertex_list(from_vertex, forward_arc, node_first_arc, node_last_arc, next_arc);
    add_to_vertex_list(to_vertex, backward_arc, node_first_arc, node_last_arc, next_arc);
    first_edge_id[edge_id] = forward_arc;
    arc_counter += 2;
}

void add_undirected_arc(int from_vertex, int to_vertex, int edge_id) {
    int forward_arc = arc_counter, backward_arc = arc_counter + 1;
    arc_target[forward_arc] = to_vertex;
    arc_capacity[forward_arc] = 1;
    reverse_arc[forward_arc] = backward_arc;
    arc_target[backward_arc] = from_vertex;
    arc_capacity[backward_arc] = 1;
    reverse_arc[backward_arc] = forward_arc;
    add_to_vertex_list(from_vertex, forward_arc, node_first_arc, node_last_arc, next_arc);
    add_to_vertex_list(to_vertex, backward_arc, node_first_arc, node_last_arc, next_arc);
    first_edge_id[edge_id] = forward_arc;
    arc_counter += 2;
}

int breadth_first_augment() {
    int queue_start = 0, queue_end = 0;
    for (int i = 1; i <= node_count; i++) parent_vertex[i] = -1;
    bfs_queue[queue_end++] = source_node;
    parent_vertex[source_node] = source_node;

    while (queue_start < queue_end && parent_vertex[target_node] == -1) {
        int current_vertex = bfs_queue[queue_start++];
        for (int arc_index = node_first_arc[current_vertex]; arc_index != -1; arc_index = next_arc[arc_index]) {
            int neighbor = arc_target[arc_index];
            if (arc_capacity[arc_index] > 0 && parent_vertex[neighbor] == -1) {
                parent_vertex[neighbor] = current_vertex;
                parent_edge_index[neighbor] = arc_index;
                bfs_queue[queue_end++] = neighbor;
                if (neighbor == target_node) break;
            }
        }
    }

    if (parent_vertex[target_node] == -1) return 0;

    int current_vertex = target_node;
    while (current_vertex != source_node) {
        int arc_index = parent_edge_index[current_vertex];
        arc_capacity[arc_index]--;
        arc_capacity[reverse_arc[arc_index]]++;
        current_vertex = parent_vertex[current_vertex];
    }
    return 1;
}

void mark_as_used(int from_vertex, int to_vertex, int edge_id) {
    used_u[used_counter] = from_vertex;
    used_v[used_counter] = to_vertex;
    used_id[used_counter] = edge_id;
    used_alive[used_counter] = 1;
    add_to_vertex_list(from_vertex, used_counter, node_first_used, node_last_used, next_used);
    used_counter++;
}

int depth_first_search_path(int current_vertex) {
    if (current_vertex == target_node) return 1;
    visited_flag[current_vertex] = visit_timer;

    for (int used_index = node_first_used[current_vertex]; used_index != -1; used_index = next_used[used_index]) {
        if (!used_alive[used_index]) continue;
        int next_vertex = used_v[used_index];
        if (visited_flag[next_vertex] == visit_timer) continue;
        if (depth_first_search_path(next_vertex)) {
            used_alive[used_index] = 0;
            current_path[path_length++] = used_index;
            return 1;
        }
    }
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d%d%d", &node_count, &edge_count, &graph_type);
    scanf("%d%d", &source_node, &target_node);

    for (int i = 1; i <= node_count; i++) {
        node_first_arc[i] = node_last_arc[i] = -1;
        node_first_used[i] = node_last_used[i] = -1;
    }

    arc_counter = 0;
    for (int i = 1; i <= edge_count; i++) {
        scanf("%d%d", &edge_from[i], &edge_to[i]);
        if (graph_type == 1) add_directed_arc(edge_from[i], edge_to[i], i);
        else add_undirected_arc(edge_from[i], edge_to[i], i);
    }

    int max_flow = 0;
    while (breadth_first_augment()) max_flow++;

    used_counter = 0;
    for (int i = 1; i <= edge_count; i++) {
        int forward_arc = first_edge_id[i];
        int backward_arc = reverse_arc[forward_arc];

        if (graph_type == 1) {
            if (arc_capacity[forward_arc] == 0) mark_as_used(edge_from[i], edge_to[i], i);
        } else {
            if (arc_capacity[forward_arc] == 0 && arc_capacity[backward_arc] == 2) mark_as_used(edge_from[i], edge_to[i], i);
            else if (arc_capacity[forward_arc] == 2 && arc_capacity[backward_arc] == 0) mark_as_used(edge_to[i], edge_from[i], i);
        }
    }

    printf("%d\n", max_flow);

    for (int flow_step = 0; flow_step < max_flow; flow_step++) {
        path_length = 0;
        visit_timer++;
        depth_first_search_path(source_node);

        printf("%d\n", path_length);
        for (int i = path_length - 1; i >= 0; i--) {
            int used_index = current_path[i];
            printf("%d %d %d\n", used_u[used_index], used_id[used_index], used_v[used_index]);
        }
    }

    return 0;
}