#include "reGraph.h"

adjlist init_adjlist(int n){
    adjlist adl;
    adl.n = n;
    adl.ques = (que*)malloc((n+1)*sizeof(que));

    for (int i=1;i<=n;i++){
        adl.ques[i] = init_que(INIT_ADJ_LEN);
    }

    return adl;
}

void kill_adjlist(adjlist* adl){
    for(int i=0;i<=adl->n;i++){
        kill_que(&adl->ques[i]);
    }
    free(adl->ques);
    adl->n = 0;
}

void add_edge(adjlist* adl, int u, int v){
    enque(&adl->ques[u], v);
}