#ifndef POINTS_PROC_H__
#define POINTS_PROC_H__

#include "app_errors.h"
#include "actions_type.h"
#include "point_proc.h"
#include <math.h>

struct point_arr
{
    point_t *arr;
    size_t n;
};
using point_arr_t = point_arr;

app_error_t alloc_points_arr(point_t **points_arr, size_t amount);

void free_points_arr(point_arr_t &points_arr);

size_t point_arr_amount_get(const point_arr_t &arr);

point_t point_arr_get(const point_arr_t &arr, size_t idx);

bool point_arr_has_data(const point_arr_t &arr);

app_error_t rotate_points(point_arr_t &points_arr, rotate_t &rotate);

app_error_t scale_points(point_arr_t &points_arr, scale_t &scale);

app_error_t move_points(point_arr_t &points_arr, move_t &move);

app_error_t find_center_point(point_t &center_point, const point_arr_t &points_arr);

#endif