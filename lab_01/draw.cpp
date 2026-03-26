#include "draw.h"

static point_t to_scene_coords(point_t point, const DrawView &view)
{
    point.x = view.width / 2.0 + point.x;
    point.y = view.height / 2.0 - point.y;
    return point;
}

static app_error_t draw_line(const DrawView &view, const point_t &point_1, const point_t &point_2)
{
    app_error_t rc = OK;
    if (!view.scene)
    {
        rc = ERROR_DRAW;
    }
    else
    {
        view.scene->addLine(point_1.x, point_1.y, point_2.x, point_2.y);
    }
    return rc;
}


app_error_t clear_scene(const DrawView &view)
{
    app_error_t rc = ERROR_DRAW;
    if (view.scene)
    {
        view.scene->clear();
        rc = OK;
    }
    return rc;
}

static line_t points_to_line(const edge_t &edge, const point_arr_t &point_arr)
{
    line_t line;
    line.first = point_arr.arr[edge.first_ind];
    line.second = point_arr.arr[edge.sec_ind];
    return line;
}

static void center_line(line_t &line, const DrawView &view)
{
    line.first = to_scene_coords(line.first, view);
    line.second = to_scene_coords(line.second, view);
}

static app_error_t draw_lines(const DrawView &view, const point_arr_t &point_arr, const edge_arr_t &edge_arr)
{
    app_error_t rc = OK;
    line_t line;
    for (size_t i = 0; rc == OK && i < edge_arr.n; i++)
    {
        line = points_to_line(edge_arr.arr[i], point_arr);
        center_line(line, view);
        rc = draw_line(view, line.first, line.second);
    }
    return rc;
}

app_error_t draw_figure(const figure_t &figure, const DrawView &view)
{
    if (!view.scene)
    {
        return ERROR_SCENE;
    }
    if (clear_scene(view) != OK || figure_has_data(figure) != OK)
    {
        return ERROR_DRAW;
    }
   return draw_lines(view, figure.points, figure.edges);
}