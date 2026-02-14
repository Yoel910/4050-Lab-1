#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 10000

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct {
    int num_nodes;
    float density_threshold;

    // sparse representation
    Node* adj_list[MAX_NODES];

    // dense representation (matrix rows)
    bool* matrix_rows[MAX_NODES];

    bool is_dense[MAX_NODES];
} HybridGraph;

/* Utility */

Node* create_node(int dest) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->dest = dest;
    n->next = NULL;
    return n;
}

HybridGraph* create_graph(int num_nodes, float threshold) {
    HybridGraph* g = (HybridGraph*)malloc(sizeof(HybridGraph));

    g->num_nodes = num_nodes;
    g->density_threshold = threshold;

    for (int i = 0; i < num_nodes; i++) {
        g->adj_list[i] = NULL;
        g->matrix_rows[i] = NULL;
        g->is_dense[i] = false;
    }

    return g;
}

/* Density Check */

int degree(HybridGraph* g, int u) {
    int count = 0;
    Node* cur = g->adj_list[u];
    while (cur) {
        count++;
        cur = cur->next;
    }
    return count;
}

void promote_to_matrix(HybridGraph* g, int u) {
    g->matrix_rows[u] = calloc(g->num_nodes, sizeof(bool));

    Node* cur = g->adj_list[u];
    while (cur) {
        g->matrix_rows[u][cur->dest] = true;
        Node* tmp = cur;
        cur = cur->next;
        free(tmp);
    }

    g->adj_list[u] = NULL;
    g->is_dense[u] = true;
}

/* Add Edge */

void add_edge(HybridGraph* g, int u, int v) {

    if (g->is_dense[u]) {
        g->matrix_rows[u][v] = true;
        return;
    }

    Node* n = create_node(v);
    n->next = g->adj_list[u];
    g->adj_list[u] = n;

    // check local density
    float density = (float)degree(g, u) / (g->num_nodes - 1);

    if (density >= g->density_threshold) {
        promote_to_matrix(g, u);
    }
}

/* Edge Lookup */

bool has_edge(HybridGraph* g, int u, int v) {

    if (g->is_dense[u]) {
        return g->matrix_rows[u][v];
    }

    Node* cur = g->adj_list[u];
    while (cur) {
        if (cur->dest == v)
            return true;
        cur = cur->next;
    }

    return false;
}

/* Example */

int main() {

    HybridGraph* g = create_graph(100, 0.1);

    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 0, 3);

    printf("Edge 0->2: %d\n", has_edge(g,0,2));

    return 0;
}
