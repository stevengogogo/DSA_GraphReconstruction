#include "utils.h"

//Choose the bigger one
int argmax(int a, int b){
    if (a>b)
        return 0;
    else 
        return 1;
}


dymArr init_Arr(int size){
    assert(size>=0);
    int* is = (int*)malloc(size*sizeof(int));
    dymArr arr = {
        .i = is,
        .len = -1,
        .size = size
    };
    return arr;
}

void kill_dymArr(dymArr* arr){
    arr->size=0;
    arr->len=-1;
    free(arr->i);
};


void append_dymArr(dymArr* arr, int val){
    //Augement size
    if((arr->len+1) > arr->size){
      int new_size = (arr->size)*2 + 1;
      arr->i = realloc(arr->i, sizeof(int)*new_size);
      arr->size = new_size;
    }

    ++(arr->len);
    arr->i[arr->len] = val;
}

int get_item(dymArr arr, int i){
    return arr.i[i];
}