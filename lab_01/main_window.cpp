#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("3D Viewer");
    resize(1200, 800);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    scene = new QGraphicsScene(this);
    draw_widget = new QGraphicsView(scene, this);
    draw_widget->setMinimumSize(800, 600);

    spinRotX = new QDoubleSpinBox;
    spinRotX->setRange(-360.0, 360.0);
    spinRotX->setValue(0.0);
    spinRotX->setSuffix("°");
    spinRotX->setSingleStep(5.0);

    spinRotY = new QDoubleSpinBox;
    spinRotY->setRange(-360.0, 360.0);
    spinRotY->setValue(0.0);
    spinRotY->setSuffix("°");
    spinRotY->setSingleStep(5.0);

    spinRotZ = new QDoubleSpinBox;
    spinRotZ->setRange(-360.0, 360.0);
    spinRotZ->setValue(0.0);
    spinRotZ->setSuffix("°");
    spinRotZ->setSingleStep(5.0);

    spinScaleX = new QDoubleSpinBox;
    spinScaleX->setRange(0.01, 100.0);
    spinScaleX->setValue(1.0);
    spinScaleX->setSingleStep(0.1);

    spinScaleY = new QDoubleSpinBox;
    spinScaleY->setRange(0.01, 100.0);
    spinScaleY->setValue(1.0);
    spinScaleY->setSingleStep(0.1);

    spinScaleZ = new QDoubleSpinBox;
    spinScaleZ->setRange(0.01, 100.0);
    spinScaleZ->setValue(1.0);
    spinScaleZ->setSingleStep(0.1);

    spinMoveX = new QDoubleSpinBox;
    spinMoveX->setRange(-1000.0, 1000.0);
    spinMoveX->setValue(0.0);
    spinMoveX->setSingleStep(10.0);

    spinMoveY = new QDoubleSpinBox;
    spinMoveY->setRange(-1000.0, 1000.0);
    spinMoveY->setValue(0.0);
    spinMoveY->setSingleStep(10.0);

    spinMoveZ = new QDoubleSpinBox;
    spinMoveZ->setRange(-1000.0, 1000.0);
    spinMoveZ->setValue(0.0);
    spinMoveZ->setSingleStep(10.0);

    QPushButton *btn_load = new QPushButton("Загрузить модель");
    QPushButton *btn_save = new QPushButton("Сохранить модель");
    QPushButton *btn_rotate = new QPushButton("Повернуть");
    QPushButton *btn_scale = new QPushButton("Масштабировать");
    QPushButton *btn_move = new QPushButton("Переместить");

    QGroupBox *groupRotate = new QGroupBox("Поворот");
    QGridLayout *rotLayout = new QGridLayout;
    rotLayout->addWidget(new QLabel("X:"), 0, 0);
    rotLayout->addWidget(spinRotX, 0, 1);
    rotLayout->addWidget(new QLabel("Y:"), 1, 0);
    rotLayout->addWidget(spinRotY, 1, 1);
    rotLayout->addWidget(new QLabel("Z:"), 2, 0);
    rotLayout->addWidget(spinRotZ, 2, 1);
    rotLayout->addWidget(btn_rotate, 3, 0, 1, 2);
    groupRotate->setLayout(rotLayout);

    QGroupBox *groupScale = new QGroupBox("Масштабирование");
    QGridLayout *scaleLayout = new QGridLayout;
    scaleLayout->addWidget(new QLabel("X:"), 0, 0);
    scaleLayout->addWidget(spinScaleX, 0, 1);
    scaleLayout->addWidget(new QLabel("Y:"), 1, 0);
    scaleLayout->addWidget(spinScaleY, 1, 1);
    scaleLayout->addWidget(new QLabel("Z:"), 2, 0);
    scaleLayout->addWidget(spinScaleZ, 2, 1);
    scaleLayout->addWidget(btn_scale, 3, 0, 1, 2);
    groupScale->setLayout(scaleLayout);

    QGroupBox *groupMove = new QGroupBox("Перемещение");
    QGridLayout *moveLayout = new QGridLayout;
    moveLayout->addWidget(new QLabel("X:"), 0, 0);
    moveLayout->addWidget(spinMoveX, 0, 1);
    moveLayout->addWidget(new QLabel("Y:"), 1, 0);
    moveLayout->addWidget(spinMoveY, 1, 1);
    moveLayout->addWidget(new QLabel("Z:"), 2, 0);
    moveLayout->addWidget(spinMoveZ, 2, 1);
    moveLayout->addWidget(btn_move, 3, 0, 1, 2);
    groupMove->setLayout(moveLayout);

    QHBoxLayout *loadSaveLayout = new QHBoxLayout;
    loadSaveLayout->addStretch();
    loadSaveLayout->addWidget(btn_load);
    loadSaveLayout->addWidget(btn_save);
    loadSaveLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(draw_widget, 4);

    QVBoxLayout *rightPanel = new QVBoxLayout;
    rightPanel->addLayout(loadSaveLayout);
    rightPanel->addWidget(groupRotate);
    rightPanel->addWidget(groupScale);
    rightPanel->addWidget(groupMove);
    rightPanel->addStretch();

    mainLayout->addLayout(rightPanel, 1);
    central->setLayout(mainLayout);

    connect(btn_load, &QPushButton::clicked, this, &MainWindow::load_file);
    connect(btn_save, &QPushButton::clicked, this, &MainWindow::save_file);
    connect(btn_rotate, &QPushButton::clicked, this, &MainWindow::rotate);
    connect(btn_scale, &QPushButton::clicked, this, &MainWindow::scale);
    connect(btn_move, &QPushButton::clicked, this, &MainWindow::move);

    update_draw_widget();
}

MainWindow::~MainWindow()
{
    Request req;
    req.action = QUIT;
    process_request(req);
}

void MainWindow::load_file()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Открыть модель", "", "Text files (*.txt)");
    if (file_name.isEmpty())
    {
        return;
    }

    Request req;
    req.action = LOAD;
    req.file_name = file_name.toLocal8Bit().data();

    app_error_t rc = process_request(req);
    if (rc != OK)
    {
        QMessageBox::critical(this, "Ошибка", error_message(rc));
    }
    else
    {
        update_draw_widget();
    }
}

void MainWindow::save_file()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Сохранить модель", "", "Text files (*.txt)");
    if (file_name.isEmpty())
    {
        return;
    }

    Request req;
    req.action = SAVE;
    req.file_name = file_name.toLocal8Bit().data();

    app_error_t rc = process_request(req);
    if (rc != OK)
    {
        QMessageBox::critical(this, "Ошибка", error_message(rc));
    }
    else
    {
        QMessageBox::information(this, "Успех", "Модель успешно сохранена");
    }
}

static double convert_angle_to_rad(double angle)
{
    return angle * M_PI / 180.0;
}

void MainWindow::rotate()
{
    double ax = spinRotX->value();
    double ay = spinRotY->value();
    double az = spinRotZ->value();

    Request req;
    req.action = ROTATE;
    req.rotate.ax = convert_angle_to_rad(ax);
    req.rotate.ay = convert_angle_to_rad(ay);
    req.rotate.az = convert_angle_to_rad(az);

    app_error_t rc = process_request(req);
    if (rc != OK)
    {
        QMessageBox::warning(this, "Ошибка", error_message(rc));
    }
    else
    {
        update_draw_widget();
    }
}

void MainWindow::scale()
{
    double kx = spinScaleX->value();
    double ky = spinScaleY->value();
    double kz = spinScaleZ->value();

    Request req;
    req.action = SCALE;
    req.scale.kx = kx;
    req.scale.ky = ky;
    req.scale.kz = kz;

    app_error_t rc = process_request(req);
    if (rc != OK)
    {
        QMessageBox::warning(this, "Ошибка", error_message(rc));
    }
    else
    {
        update_draw_widget();
    }
}

void MainWindow::move()
{
    double dx = spinMoveX->value();
    double dy = spinMoveY->value();
    double dz = spinMoveZ->value();

    Request req;
    req.action = MOVE;
    req.move.dx = dx;
    req.move.dy = dy;
    req.move.dz = dz;

    app_error_t rc = process_request(req);
    if (rc != OK)
    {
        QMessageBox::warning(this, "Ошибка", error_message(rc));
    }
    else
    {
        update_draw_widget();
    }
}

void MainWindow::update_draw_widget()
{
    Request req;
    req.action = DRAW;
    req.draw_view.scene = scene;
    req.draw_view.width = draw_widget->width();
    req.draw_view.height = draw_widget->height();

    process_request(req);
    draw_widget->update();
}