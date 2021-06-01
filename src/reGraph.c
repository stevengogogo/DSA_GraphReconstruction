#include "reGraph.h"

adjlist init_adjlist(int n){
    adjlist adl;
    adl.n = n;
    adl.lists = (dymArr*)malloc((n+1)*sizeof(dymArr));

    for (int i=1;i<=n;i++){
        adl.lists[i] = init_Arr(INIT_ADJ_LEN);
    }

    return adl;
}

void kill_adjlist(adjlist* adl){
    for(int i=0;i<=adl->n;i++){
        kill_dymArr(&adl->lists[i]);
    }
    free(adl->lists);
    adl->n = 0;
}

void add_edge(adjlist* adl, int u, int v){
    append_dymArr(&adl->lists[u], v);
}