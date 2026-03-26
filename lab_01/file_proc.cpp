#include "file_proc.h"

static app_error_t read_point(point_t &point, FILE *file)
{
    app_error_t rc = OK;
    double x, y, z;
    if (!file)
        rc = ERROR_OPEN_FILE;
    else if (fscanf(file, "%lf %lf %lf", &x, &y, &z) == 3)
        point_init(point, x, y, z);
    else
        rc = ERROR_READ_FILE;
    return rc;
}

static app_error_t read_size(size_t &size, FILE *file)
{
    if (!file)
    {
        return ERROR_READ_FILE;
    }
    if (fscanf(file, "%zu", &size) != 1 || size <= 0)
    {
        return ERROR_READ_FILE;
    }
    return OK;
}

static app_error_t read_points(point_arr_t &point_arr, FILE *file)
{
    if (!file)
        return ERROR_OPEN_FILE;
    app_error_t rc = read_size(point_arr.n, file);
    if (rc == OK)
    {
        rc = alloc_points_arr(&point_arr.arr, point_arr.n);
        for (size_t i = 0; i < point_arr.n && rc == OK; ++i)
        {
            rc = read_point(point_arr.arr[i], file);
        }
        if (rc != OK)
            free_points_arr(point_arr);
    }
    return rc;
}

static app_error_t read_edge(edge_t &edge, FILE *file)
{
    app_error_t rc = OK;
    size_t first, sec;
    if (!file)
        rc = ERROR_OPEN_FILE;
    else if (fscanf(file, "%zu %zu", &first, &sec) == 2)
        edge_init(edge, first, sec);
    else
        rc = ERROR_READ_FILE;
    return rc;
}

static app_error_t read_edges(edge_arr_t &edge_arr, FILE *file)
{
    if (!file)
        return ERROR_OPEN_FILE;
    app_error_t rc = read_size(edge_arr.n, file);
    if (rc == OK)
    {
        rc = alloc_edge_arr(&edge_arr.arr, edge_arr.n);
        for (size_t i = 0; i < edge_arr.n && rc == OK; ++i)
        {
            rc = read_edge(edge_arr.arr[i], file);
        }
        if (rc != OK)
            free_edge_arr(edge_arr);
    }
    return rc;
}

static app_error_t file_read_figure(figure_t &figure, FILE *file)
{
    if (!file)
    {
        return ERROR_READ_FILE;
    }
    app_error_t rc = read_points(figure.points, file);
    if (rc == OK)
    {
        rc = read_edges(figure.edges, file);
        if (rc != OK)
        {
            free_points_arr(figure.points);
        }
    }
    return rc;
}

app_error_t read_figure(figure_t &figure, const char *file_name)
{
    app_error_t rc = OK;
    FILE *file = fopen(file_name, "r");
    if (!file)
        rc = ERROR_OPEN_FILE;
    else
    {
        figure_t temp_fig = figure_init();
        rc = file_read_figure(temp_fig, file);
        fclose(file);
        if (rc == OK)
        {
            figure_free(figure);
            figure = temp_fig;
        }
    }
    return rc;
}

static app_error_t write_size_to_file(const size_t size, FILE *file)
{
    if (!file)
    {
        return ERROR_WRITE_FILE;
    }
    app_error_t rc = OK;
    if (fprintf(file, "%zu\n", size) < 0)
    {
        rc = ERROR_WRITE_FILE;
    }
    return rc;
    
}

static app_error_t write_point_to_file(const point_t &point, FILE *file)
{
    if (!file)
    {
        return ERROR_WRITE_FILE;
    }
    app_error_t rc = OK;
    if (fprintf(file, "%lf %lf %lf\n", point.x, point.y, point.z) < 0)
        rc = ERROR_WRITE_FILE;
    return rc;
}

static app_error_t write_points_to_file(const point_arr_t &point_arr, FILE *file)
{
    if (!file)
    {
        return ERROR_WRITE_FILE;
    }
    app_error_t rc = write_size_to_file(point_arr.n, file);
    for (size_t i = 0; i < point_arr.n && rc == OK; ++i)
    {
        rc = write_point_to_file(point_arr.arr[i], file);
    }
    return rc;
}

static app_error_t write_edge_to_file(const edge_t &edge, FILE *file)
{
    if (!file)
    {
        return ERROR_WRITE_FILE;
    }
    app_error_t rc = OK;
    if (fprintf(file, "%zu %zu\n", edge.first_ind, edge.sec_ind) < 0)
    {
        rc = ERROR_WRITE_FILE;
    }
    return rc;
}

static app_error_t write_edges_to_file(const edge_arr_t &edge_arr, FILE *file)
{
    if (!file)
    {
        return ERROR_WRITE_FILE;
    }
    app_error_t rc = write_size_to_file(edge_arr.n, file);
    for (size_t i = 0; i < edge_arr.n && rc == OK; ++i)
    {
        rc = write_edge_to_file(edge_arr.arr[i], file);
    }
    return rc;
}

static app_error_t file_write_figure(const figure_t &figure, FILE *file)
{
    if (!file)
        return ERROR_WRITE_FILE;
    app_error_t rc = write_points_to_file(figure.points, file);
    if (rc == OK)
        rc = write_edges_to_file(figure.edges, file);
    return rc;
}

app_error_t write_figure(const figure_t &figure, const char *file_name)
{
    if (!point_arr_has_data(figure.points) || !edge_arr_has_data(figure.edges))
        return ERROR_WRITE_FILE;

    FILE *file = fopen(file_name, "w");
    if (!file)
    {
        return ERROR_OPEN_FILE;
    }
    app_error_t rc = file_write_figure(figure, file);
    fclose(file);
    return rc;
}