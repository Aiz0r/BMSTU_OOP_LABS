#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "actions.h"
#include "draw.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void load_file();
    void save_file();
    void rotate();
    void scale();
    void move();

private:
    void update_draw_widget();

    QDoubleSpinBox *spinRotX, *spinRotY, *spinRotZ;
    QDoubleSpinBox *spinScaleX, *spinScaleY, *spinScaleZ;
    QDoubleSpinBox *spinMoveX, *spinMoveY, *spinMoveZ;
    QGraphicsView *draw_widget;
    QGraphicsScene *scene;
};

#endif