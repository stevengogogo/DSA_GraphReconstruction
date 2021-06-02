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

bool is_circle(dymArr arr){
    if(arr.len<=1)
        return false;
    else{
        int first = arr.i[0];
        int last = arr.i[arr.len-1];

        if(first==last)
            return true;
        else    
            return false;
    }
}


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
    dymArr pathc = init_Arr(INIT_ADJ_LEN);
    
    for(int v=1;v<=adl->n;v++){
        deque_adjList(adl, &el, &pathc, v);
    }

    kill_dymArr(&pathc);
    return el;
}

void deque_adjList(adjlist* adl, edgeList* el, dymArr* pathc, int vtx){
    int adjV = peek_que(&adl->ques[vtx]);

    if (is_circle(*pathc)){//Circular
        el->valid=false;
        return;
    }
    if (adjV == EMTY_QUE_SIG){ //Empty 
        return;
    }

    int nextV = peek_que(&adl->ques[adjV]);
    if(adjV == nextV){
        append_edge(el, adjV, nextV);
        deque(&adl->ques[adjV]);
        deque(&adl->ques[vtx]);
    }
    else{
        append_dymArr(pathc, vtx);
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