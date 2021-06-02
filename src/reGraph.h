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
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "utils.h"


/**
 * @brief Adjacency list
 * @param lists lists of vertexes. Neighbor are stored at list[0,..n] 
 * @param n number of vertexes
 */
typedef struct {
    que* ques;
    int n; 
} adjlist;

// Init and kill
/**
 * @brief Create adjacency list with n vertexes
 * 
 * @param n number of vertexes
 * @return adjlist 
 */
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

/**
 * @brief Check circular reference. Compare i[0] and i[end]
 * 
 * @return true when i[0]==i[end] and len>1
 * @return false otherwise
 */
bool is_circle(dymArr);

//Validation
typedef struct {
    dymArr u;
    dymArr v;
    bool valid;
} edgeList;

edgeList init_edgeList(int size);
void kill_edgeList(edgeList*);
void print_edgeList(edgeList);
void append_edge(edgeList*, int u, int v);

edgeList GraphReconstruct(adjlist*);
void deque_adjList(adjlist*, edgeList*, dymArr* pathc, int vtx);

int interface(void);


#endif 