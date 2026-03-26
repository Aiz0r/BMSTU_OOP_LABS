#include "figure_proc.h"

figure_t figure_init()
{
    figure_t fig;
    fig.points.arr = nullptr;
    fig.points.n = 0;
    fig.edges.arr = nullptr;
    fig.edges.n = 0;
    return fig;
}

void figure_free(figure_t &fig)
{
    free_points_arr(fig.points);
    free_edge_arr(fig.edges);
}

app_error_t figure_has_data(const figure_t &fig)
{
    app_error_t rc = OK;
    if (!(point_arr_has_data(fig.points) && edge_arr_has_data(fig.edges)))
    {
        rc = ERROR_NOT_LOADED;
    }
    return rc;
}

app_error_t figure_rotate(figure_t &figure, rotate_t &rotate)
{
    return rotate_points(figure.points, rotate);
}

app_error_t figure_move(figure_t &figure, move_t &move)
{
    return move_points(figure.points, move);
}

app_error_t figure_scale(figure_t &figure, scale_t &scale)
{
    return scale_points(figure.points, scale);
}

size_t figure_points_count(const figure_t &fig)
{
    return point_arr_amount_get(fig.points);
}

size_t figure_edges_count(const figure_t &fig)
{
    return edge_arr_amount_get(fig.edges);
}

point_t figure_get_point(const figure_t &fig, size_t idx)
{
    return point_arr_get(fig.points, idx);
}

edge_t figure_get_edge(const figure_t &fig, size_t idx)
{
    return edge_arr_get(fig.edges, idx);
}
