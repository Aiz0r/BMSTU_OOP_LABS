#ifndef ACTIONS_H
#define ACTIONS_H

#include "draw.h"
#include "figure_proc.h"
#include "file_proc.h"
#include "points_proc.h"
#include "actions_type.h"
#include "app_errors.h"
#include <QGraphicsScene>

enum Action
{
    LOAD,
    SAVE,
    QUIT,
    DRAW,
    MOVE,
    ROTATE,
    SCALE
};

struct Request
{
    Action action;
    union
    {
        move_t move;
        rotate_t rotate;
        scale_t scale;
        const char *file_name;
        DrawView draw_view;
    };
};

app_error_t process_request(Request &req);

#endif