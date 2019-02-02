#include "ads-graph/graph.h"
#include "ads-graph/queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef graph grafo_oggetti;

typedef struct nodo_albero {
    struct nodo_albero *left_child;
    struct nodo_albero *right_sibling;
    int info;
} nodo_albero;

int foglie_comp(grafo_oggetti *g, nodo_albero *a);
void conta_foglie(nodo_albero *a, int *count);
void DFS_conta_dimensione_cc(node *n, int *dim, int mark);

int foglie_comp(grafo_oggetti *g, nodo_albero *a) {
    if(g == NULL && a == NULL)
        return 1;
    if(g == NULL || a == NULL)
        return 0;

    int num_foglie = 0;
    conta_foglie(a, &num_foglie);

    node_list *nodi = g->nodes;
    while(nodi != NULL) {
        nodi->info->color = 0;
        nodi = nodi->next;
    }

    nodi = g->nodes;
    int mark = 0;
    while(nodi != NULL) {
        int dim = 0;
        DFS_conta_dimensione_cc(nodi->info, &dim, ++mark);
        if(dim == num_foglie)
            return 1;

        nodi = nodi->next;
    }

    return 0;
}

void conta_foglie(nodo_albero *a, int *count) {
    if(a == NULL)
        return;

    if(a->left_child == NULL)
        (*count)++;

    nodo_albero *figlio = a->left_child;
    while(figlio != NULL) {
        conta_foglie(figlio, count);
        figlio = figlio->right_sibling;
    }
}

void DFS_conta_dimensione_cc(node *n, int *dim, int mark) {
    n->color = mark;
    (*dim)++;

    edge_list *archi = n->edges;
    while(archi != NULL) {
        node *v = node_opposite(archi->info, n);
        if(v->color != mark)
            DFS_conta_dimensione_cc(v, dim, mark);

        archi = archi->next;
    }
}

int main() {
    grafo_oggetti *g = new_graph();
    int n = 7;
    node *nodes[n];

    for(int i=0; i<n; i++) {
        add_node_to_graph(g, i);
        nodes[i] = graph_get_node_by_id(g, i);
    }

    add_edge_to_graph(g, nodes[0], nodes[1], 1, 0);
    add_edge_to_graph(g, nodes[0], nodes[2], 1, 0);
    //add_edge_to_graph(g, nodes[1], nodes[3], 1, 0);

    add_edge_to_graph(g, nodes[4], nodes[5], 1, 0);
    add_edge_to_graph(g, nodes[5], nodes[6], 1, 0);

    nodo_albero *b;
    nodo_albero *a = (nodo_albero *)calloc(1, sizeof(nodo_albero));
    a->right_sibling = NULL;
    a->left_child = (nodo_albero *)calloc(1, sizeof(nodo_albero));
    b = a->left_child;
    b->right_sibling = (nodo_albero *)calloc(1, sizeof(nodo_albero));
    b->left_child = (nodo_albero *)calloc(1, sizeof(nodo_albero));
    b = b->left_child;
    b->right_sibling = (nodo_albero *)calloc(1, sizeof(nodo_albero));
    b->right_sibling->right_sibling = (nodo_albero *)calloc(1, sizeof(nodo_albero));

    printf("Verifica = %d\n", foglie_comp(g, a));

    return 0;
}