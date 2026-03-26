#include "edges_proc.h"

void edge_init(edge_t &edge, size_t first, size_t second)
{
    edge.first_ind = first;
    edge.sec_ind = second;
}

void edge_arr_init(edge_arr_t &edges_arr)
{
    edges_arr.arr = nullptr;
    edges_arr.n = 0;
}

app_error_t alloc_edge_arr(edge **edges_arr, size_t amount)
{
    if (amount <= 0)
    {
        return ERROR_MEM;
    }
    app_error_t rc = OK;
    *edges_arr =  (edge_t *)malloc(amount * sizeof(edge_t));
    if (!*edges_arr)
    {
        rc = ERROR_MEM;
    }
    return rc;
}

void free_edge_arr(edge_arr_t &edges_arr)
{
    free(edges_arr.arr);
    edges_arr.arr = nullptr;
    edges_arr.n = 0;
}

edge_t edge_arr_get(const edge_arr_t &arr, size_t idx)
{
    return arr.arr[idx];
}

size_t edge_arr_amount_get(const edge_arr_t &arr)
{
    return arr.n;
}

bool edge_arr_has_data(const edge_arr_t &arr)
{
    return (arr.arr != nullptr && arr.n > 0);
}
