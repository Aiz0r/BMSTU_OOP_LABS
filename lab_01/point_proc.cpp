#include "point_proc.h"

void point_init(point_t &point, double x, double y, double z)
{
    point.x = x;
    point.y = y;
    point.z = z;
}

void basic_point_init(point_t &point)
{
    point_init(point, 0.0, 0.0, 0.0);
}

static void rotate(double &first_val, double &sec_val, const double sin_val, const double cos_val)
{
    double temp_first = first_val;
    first_val = first_val * cos_val + sec_val * sin_val;
    sec_val = sec_val * cos_val - temp_first * sin_val;
}

static void rotate_x(point_t &point, const double angle)
{
    double sin_val = sin(angle);
    double cos_val = cos(angle);
    rotate(point.y, point.z, sin_val, cos_val);
}

static void rotate_y(point_t &point, const double angle)
{
    double sin_val = sin(angle);
    double cos_val = cos(angle);
    rotate(point.x, point.z, sin_val, cos_val);
}

static void rotate_z(point_t &point, const double angle)
{
    double sin_val = sin(angle);
    double cos_val = cos(angle);
    rotate(point.x, point.y, sin_val, cos_val);
}

void point_move(point_t &point, const move_t &move)
{
    point.x += move.dx;
    point.y += move.dy;
    point.z += move.dz;
}

void point_scale(point_t &point, const point_t &center_point, const scale_t &scale)
{
    point_move(point, move_t{-center_point.x, -center_point.y, -center_point.z});
    point.x = point.x * scale.kx;
    point.y = point.y * scale.ky;
    point.z = point.z * scale.kz;
    point_move(point, move_t{center_point.x, center_point.y, center_point.z});
}

void point_rotate(point_t &point, const point_t &center_point, const rotate_t &rotate)
{
    point_move(point, move_t{-center_point.x, -center_point.y, -center_point.z});
    rotate_x(point, rotate.ax);
    rotate_y(point, rotate.ay);
    rotate_z(point, rotate.az);
    point_move(point, move_t{center_point.x, center_point.y, center_point.z});
}