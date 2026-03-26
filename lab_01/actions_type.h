#ifndef ACTIONS_TYPE_H__
#define ACTIONS_TYPE_H__

struct Move
{
    double dx;
    double dy;
    double dz;
};
using move_t = Move;

struct Rotate
{
    double ax;
    double ay;
    double az;
};
using rotate_t = Rotate;

struct Scale
{
    double kx;
    double ky;
    double kz;
};
using scale_t = Scale;

#endif