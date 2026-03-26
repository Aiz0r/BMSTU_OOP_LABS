#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>
#include "figure_proc.h"
#include "app_errors.h"

struct DrawView
{
    QGraphicsScene *scene;
    double width;
    double height;
};

struct Line
{
    point_t first;
    point_t second;
};
using line_t = Line;

app_error_t clear_scene(const DrawView &view);
app_error_t draw_figure(const figure_t &figure, const DrawView &view);

#endif