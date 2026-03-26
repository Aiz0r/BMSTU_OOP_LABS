#ifndef APP_ERRORS_H
#define APP_ERRORS_H

enum errors
{
    OK = 0,
    ERROR_OPEN_FILE,
    ERROR_READ_FILE,
    ERROR_WRITE_FILE,
    ERROR_MEM,
    ERROR_LOAD,
    ERROR_DRAW,
    ERROR_NOT_LOADED,
    ERROR_SCENE,
    ERROR_UNKNOWN_ACTION,
};

using app_error_t = errors;

const char *error_message(app_error_t err);

#endif