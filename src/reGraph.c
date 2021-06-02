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

    //TODO
    edgeList el = init_edgeList(adl->n);
    int cur_u;
    int adjV = 0;
    int nextV = 0;
    int Va, Vb;
    dymArr pathc = init_Arr(INIT_ADJ_LEN); // record path
    
    for(int u=1;u<=adl->n;u++){
        cur_u = u;
        adjV = peek_que(&adl->ques[cur_u]);
        while(adjV!=EMTY_QUE_SIG){
            nextV = peek_que(&adl->ques[adjV]);

            //Check mutual link
            if( nextV == cur_u  ){ //valid edge
                // deque mutual list
                Va = deque(&adl->ques[cur_u]);
                Vb = deque(&adl->ques[adjV]);
                //record
                append_edge(&el, Va, Vb);

                //Clear path
                clear_Arr(&pathc);
            }
            else{//not valid edge
                append_dymArr(&pathc, cur_u);
                cur_u = nextV;
                adjV = peek_que(&adl->ques[cur_u]);
                while(adjV != EMTY_QUE_SIG){
                    nextV = peek_que(&adl->ques[adjV]);
                    if(nextV == cur_u){
                         // deque mutual list
                        Va = deque(&adl->ques[cur_u]);
                        Vb = deque(&adl->ques[adjV]);
                        //record
                        append_edge(&el, Va, Vb);
                        //Clear path
                        clear_Arr(&pathc);
                        break;
                    }
                    else{
                        append_dymArr(&pathc, cur_u);
                        cur_u = nextV;
                        adjV = peek_que(&adl->ques[cur_u]);

                        el.valid = is_circle(pathc);
                    }
                    cur_u = nextV;
                    adjV = peek_que(&adl->ques[u]);
                    if(!el.valid)
                            break;
                }
            }

            if(!el.valid)
                break;
        }

        adjV = peek_que(&adl->ques[u]);
        if(!el.valid)
                break;
    }

   
    return el;
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