/**
 * @file utils.h
 * @author Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief General Utilities for C language
 * @version 0.1
 * @date 2021-03-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <assert.h>

/**
 * @brief Argmax function with intergers
 * 
 * @param a 
 * @param b 
 * @return int 0 when a is larger than b. Otherwise, 0.
 */
int argmax(int a, int b);


//dynamic array
typedef struct{
    int len;
    int size;
    int* i;
} dymArr;

//init and kill
dymArr init_Arr(int size);
void kill_dymArr(dymArr*);

//append
void append_dymArr(dymArr*, int val);
int get_item(dymArr, int i);





#endif