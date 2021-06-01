/**
 * @file reGraph.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef REGRAPH_H
#define REGRAPH_H
#define INIT_ADJ_LEN 1000
#include "utils.h"

/**
 * @brief Adjacency list
 * @param lists lists of vertexes. Neighbor are stored at list[0,..n] 
 * @param n number of vertexes
 */
typedef struct {
    dymArr* lists;
    int n; 
} adjlist;

// Init and kill
adjlist init_adjlist(int n);
void kill_adjlist(adjlist*);

//Add edge
/**
 * @brief Add edge to link v to u
 * 
 * @param u starting vertex [1, N]
 * @param v ending vertex
 */
void add_edge(adjlist*, int u, int v);

void interface(void);


#endif 