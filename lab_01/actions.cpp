#include "actions.h"

app_error_t process_request(Request &req)
{
    static figure_t figure = figure_init();
    app_error_t rc = OK;

    switch (req.action)
    {
    case LOAD:
        rc = read_figure(figure, req.file_name);
        break;
    case SAVE:
        rc = write_figure(figure, req.file_name);
        break;
    case QUIT:
        figure_free(figure);
        break;
    case DRAW:
        rc = draw_figure(figure, req.draw_view);
        break;
    case MOVE:
        rc = figure_move(figure, req.move);
        break;
    case ROTATE:
        rc = figure_rotate(figure, req.rotate);
        break;
    case SCALE:
        rc = figure_scale(figure, req.scale);
        break;
    default:
        rc = ERROR_UNKNOWN_ACTION;
        break;
    }

    return rc;
}
