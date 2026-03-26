#ifndef OBJ_PROC_H__
#define OBJ_PROC_H__

#include "points_proc.h"
#include "edges_proc.h"
#include "actions_type.h"
#include <cstdlib>

struct figure
{
    point_arr_t points;
    edge_arr_t edges;
};
using figure_t = figure;

figure_t figure_init();

void figure_free(figure_t &fig);

app_error_t figure_rotate(figure_t &figure, rotate_t &rotate);

app_error_t figure_move(figure_t &figure, move_t &move);

app_error_t figure_scale(figure_t &figure, scale_t &scale);

app_error_t figure_has_data(const figure_t &fig);

size_t figure_points_count(const figure_t &fig);

size_t figure_edges_count(const figure_t &fig);

point_t figure_get_point(const figure_t &fig, size_t idx);

edge_t figure_get_edge(const figure_t &fig, size_t idx);

#endif