#include "points_proc.h"

app_error_t alloc_points_arr(point_t **points_arr, size_t amount)
{
    if (amount <= 0)
    {
        return ERROR_MEM;
    }
    app_error_t rc = OK;
    *points_arr = (point_t *)malloc(amount * sizeof(point_t));
    if (!*points_arr)
        rc = ERROR_MEM;
    return rc;
}

void free_points_arr(point_arr_t &points_arr)
{
    free(points_arr.arr);
    points_arr.arr = NULL; 
    points_arr.n = 0;
}

point_t point_arr_get(const point_arr_t &arr, size_t idx)
{
    return arr.arr[idx];
}

size_t point_arr_amount_get(const point_arr_t &arr)
{
    return arr.n;
}

bool point_arr_has_data(const point_arr_t &arr)
{
    return (arr.arr != NULL && arr.n > 0);
}

app_error_t rotate_points(point_arr_t &points_arr, rotate_t &rotate)
{
    app_error_t rc = OK;
    point_t center_point;
    rc = find_center_point(center_point, points_arr);
    if (points_arr.arr == NULL || points_arr.n <= 0)
        rc = ERROR_LOAD;
    else
    {
        for (size_t i = 0; i < points_arr.n; i++)
        {
            point_rotate(points_arr.arr[i], center_point, rotate);
        }
    }
    return rc;
}

app_error_t scale_points(point_arr_t &points_arr, scale_t &scale)
{
    app_error_t rc = OK;
    point_t center_point;
    rc = find_center_point(center_point, points_arr);
    if (points_arr.arr == NULL || points_arr.n <= 0)
        rc = ERROR_LOAD;
    else
    {
        for (size_t i = 0; i < points_arr.n; i++)
        {
            point_scale(points_arr.arr[i], center_point, scale);
        }
    }
    return rc;
}

app_error_t move_points(point_arr_t &points_arr, move_t &move)
{
    app_error_t rc = OK;
    if (points_arr.arr == NULL || points_arr.n <= 0)
        rc = ERROR_LOAD;
    else
    {
        for (size_t i = 0; i < points_arr.n; i++)
        {
            point_move(points_arr.arr[i], move);
        }
    }
    return rc;
}

app_error_t find_center_point(point_t &center_point, const point_arr_t &points_arr)
{
    app_error_t rc = OK;
    if (points_arr.arr == NULL || points_arr.n <= 0)
    {
        rc = ERROR_LOAD;
    }
    else
    {
        basic_point_init(center_point);
        double sum_x = 0.0;
        double sum_y = 0.0;
        double sum_z = 0.0;
        point_t cur_point;
        for (size_t i = 0; i < points_arr.n; i++)
        {
            cur_point = point_arr_get(points_arr, i);
            sum_x += cur_point.x;
            sum_y += cur_point.y;
            sum_z += cur_point.z;
        }
        center_point.x = sum_x / points_arr.n;
        center_point.y = sum_y / points_arr.n;
        center_point.z = sum_z / points_arr.n;
    }
    return rc;
}