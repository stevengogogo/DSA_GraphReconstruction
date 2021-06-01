#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "acutest.h"
#include "utils.h"

#define MAX_NODES 100000

void test_utils(void)
{
    int a, b;
    a = 1; b= 2;
    
    TEST_CHECK(argmax(a,b)  == 1 );
}

void test_array(void){
    dymArr arr = init_Arr(0);

    for(int i=0;i<MAX_NODES;i++)
        append_dymArr(&arr, i);

    for(int i=0;i<MAX_NODES;i++)
        TEST_CHECK(get_item(arr, i) == i);

    kill_dymArr(&arr);
}

#endif