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


/**Path**/
path init_path(int size){
    path p;
    p.vs = (int*)malloc((size+1)*sizeof(int));

    //Initialize 
    for(int i=0;i<=size;i++){
        p.vs[i] = 0;
    }

    p.visited_v = init_Arr(size+1);
    p.len = 0;
    p.num_v = size;
    return p;
}

void kill_path(path* p){
    free(p->vs);
    kill_dymArr(&p->visited_v);
}

void append_path(path* p, int u){
    ++(p->vs[u]);
    append_dymArr(&p->visited_v, u);
    p->len = p->visited_v.len;
}

int pop_path(path* p){
    int v = pop_item(&p->visited_v);
    if(v==EMTY_QUE_SIG)
        return v;
    p->len = p->visited_v.len;
    p->vs[v] = 0;
    return v;
}

void clear_path(path* p){
    int Vi = pop_item(&p->visited_v);
    while(Vi!=EMTY_QUE_SIG){
        p->vs[Vi] = 0;
        Vi = pop_item(&p->visited_v);
    }
    
}



bool is_circle(path p, int val){
    if (p.vs[val] > 0)
        return true;
    else 
        return false;
}

/**validation**/
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
    edgeList el=init_edgeList(adl->n + 1);
    path pathc = init_path(adl->n + 1); //path can not solve not now
    path pathl = init_path(adl->n + 1); //path in waiting list
    bool res = true;
   
    //Pop all the ques to empty
    deque_adjList(adl, &el, &pathc, &pathl,1);



    kill_path(&pathc);
    kill_path(&pathl);
    return el;
}

bool deque_adjList(adjlist* adl, edgeList* el, path* pathc, path* pathl,int vtx){

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
        //clear_path(pathc);
    }
    else{
        if (is_circle(*pathc, vtx)){//Circular
            el->valid=false;
            return false;
        }
        append_path(pathc, vtx);
    } 
    
    deque_adjList(adl, el, pathc, pathl, adjV);
    deque_adjList(adl, el, pathc, pathl, vtx);

    //int savedV = pop_path(pathc);
    //if (savedV!=EMTY_QUE_SIG && el->valid)
        //deque_adjList(adl,el,pathc, pathl, savedV);
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