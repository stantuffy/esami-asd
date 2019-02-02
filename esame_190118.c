

grafo_array *componente_connessa(grafo_oggetti *g, nodo *n) {

    if(g == NULL) {
        return NULL;
    }

    elem_nodi *nodi = g->nodi;
    while(nodi != NULL) {
        nodi->info->color = 0;
        nodi = nodi->next;
    }

    DFS(n);

    int i = 0;
    nodi = g->nodi;
    htable *ht = crea_tabella();
    while(nodi != NULL) {
        if(nodi->info->color != 0) {
            aggiungi_elemento(ht, nodi->info, i);
            i++;
        }
        nodi = nodi->next;
    }

    grafo_array *ga = (grafo_array *)calloc(1, sizeof(grafo_array));
    ga->numero_nodi = i;
    ga->A = (elem_int **)calloc(ga->numero_nodi, sizeof(elem_int *));
    
    nodi = g->nodi;
    while(nodi != NULL) {
        if(nodi->info->color != 0) {
            elem_archi *archi = nodi->info->archi;
            while(archi != NULL) {
                nodo *v = opposto(archi->info, nodi->info);
                if(v->color != 0)
                    aggiungi_arco(ga, trova_valore(ht, nodi->info), trova_valore(ht, v));
                
                archi = archi->next;
            }

            nodi = nodi->next;
        }
    }

    distruggi_tabella(ht);

    return ga;
}