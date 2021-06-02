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

//Path

path init_path(int size);
void kill_path(path*);
void append_path(path*, int u);
void clear_path(path*);
bool is_circle(path, int val);

//validation
edgeList init_edgeList(int size){
    edgeList el;
    el.u = init_Arr(size);
    el.v = init_Arr(size);
    el.valid = true;
    return el;
}

void kill_edgeList(edgeList* el){
    kill_dymArr(&el->u);
    kill_dymArr(&el->v);
}

void print_edgeList(edgeList el){
    if(el.valid){
        printf("Yes\n");
        for (int i=0;i<el.u.len;i++){
            printf("%d %d", get_item(el.u,i), get_item(el.v,i));
            if(i!= el.u.len-1)
                printf("\n");
        }
    }
    else{
        printf("No");
    }
};

void append_edge(edgeList* el, int u, int v){
    append_dymArr(&el->u,u);
    append_dymArr(&el->v,v);
}


edgeList GraphReconstruct(adjlist* adl){
    edgeList el=init_edgeList(adl->n);
    path pathc = init_path(INIT_ADJ_LEN);
    bool res = true;
    int cur;

    //Pop all the ques to empty
    for(int v=1;v<=adl->n;v++){
        res = deque_adjList(adl, &el, &pathc, v);
        if (!res)
            break;

        cur = peek_que(&adl->ques[v]);
        while(res && cur!=EMTY_QUE_SIG){
            res = deque_adjList(adl, &el, &pathc, v);
            cur = peek_que(&adl->ques[v]);
        }
    }

    kill_path(&pathc);
    return el;
}

bool deque_adjList(adjlist* adl, edgeList* el, path* pathc, int vtx){
    int adjV = peek_que(&adl->ques[vtx]);

    if (adjV == EMTY_QUE_SIG){ //Empty 
        return true;
    }

    int nextV = peek_que(&adl->ques[adjV]);

    if (nextV == EMTY_QUE_SIG){ //partner is absent
        el->valid=false;
        return false;
    }

    if(vtx == nextV){
        append_edge(el, adjV, nextV);
        deque(&adl->ques[adjV]);
        deque(&adl->ques[nextV]);
        clear_Arr(pathc);
    }
    else{
        append_path(pathc, vtx);
        if (is_circle(*pathc, vtx)){//Circular
            el->valid=false;
            return false;
        }
    }

    deque_adjList(adl, el, pathc, adjV);
}



int interface(void){
    int N;//Number of nodes
    int numV; // number of adjacent nodes
    int Vi; // index of node
    
    //Set Problem
    scanf("%d", &N);

    adjlist adl = init_adjlist(N);

    for(int u=1;u<=N;u++){
        scanf("%d", &numV);
        for(int v=1;v<=numV;v++){
            scanf("%d", &Vi);
            add_edge(&adl, u, Vi);
        }
    }

    //Solve
    edgeList el = GraphReconstruct(&adl);

    //Print
    print_edgeList(el);

    //GC
    kill_edgeList(&el);
    kill_adjlist(&adl);

    return 0;
}   