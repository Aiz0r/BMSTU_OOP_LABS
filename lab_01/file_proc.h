#ifndef FILE_PROC_H__
#define FILE_PROC_H__

#include <stdio.h>
#include "figure_proc.h"

app_error_t read_figure(figure_t &figure, const char *file_name);
app_error_t write_figure(const figure_t &figure, const char *file_name);

#endif