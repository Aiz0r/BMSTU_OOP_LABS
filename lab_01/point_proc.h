#ifndef POINT_PROC_H__
#define POINT_PROC_H__

#include "app_errors.h"
#include "actions_type.h"
#include <math.h>

struct point
{
    double x;
    double y;
    double z;
};
using point_t = point;

void point_init(point_t &point, double x, double y, double z);

void basic_point_init(point_t &point);

void point_scale(point_t &point, const point_t &center_point, const scale_t &scale);

void point_move(point_t &point, const move_t &move);

void point_rotate(point_t &point, const point_t &center_point, const rotate_t &rotate);
#endif