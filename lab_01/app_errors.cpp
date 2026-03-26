#include "app_errors.h"

const char *error_message(app_error_t err)
{
    switch (err)
    {
    case OK:
        return "Успешно";
    case ERROR_OPEN_FILE:
        return "Ошибка открытия файла";
    case ERROR_READ_FILE:
        return "Ошибка чтения файла";
    case ERROR_WRITE_FILE:
        return "Ошибка записи в файл";
    case ERROR_MEM:
        return "Ошибка выделения памяти";
    case ERROR_LOAD:
        return "Ошибка загрузки модели";
    case ERROR_DRAW:
        return "Ошибка отрисовки";
    case ERROR_NOT_LOADED:
        return "Фигура не загружена";
    case ERROR_UNKNOWN_ACTION:
        return "Неизвестное действие";
    case ERROR_SCENE:
        return "Ошибка рисования сцены";
    default:
        return "Неизвестная ошибка";
    }
}