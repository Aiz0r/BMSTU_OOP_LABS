#ifndef EDGES_PROC_H__
#define EDGES_PROC_H__

#include "points_proc.h"
#include <cstdlib>

struct edge
{
    size_t first_ind;
    size_t sec_ind;
};
using edge_t = edge;

struct edge_arr
{
    edge_t *arr;
    size_t n;
};
using edge_arr_t = edge_arr;

void edge_init(edge_t &edge, size_t first, size_t second);

void edge_arr_init(edge_arr_t &edges_arr);

app_error_t alloc_edge_arr(edge **edges_arr, size_t amount);

void free_edge_arr(edge_arr_t &edges_arr);

edge_t edge_arr_get(const edge_arr_t &arr, size_t idx);

size_t edge_arr_amount_get(const edge_arr_t &arr);

bool edge_arr_has_data(const edge_arr_t &arr);

#endif