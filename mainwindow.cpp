#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(released()),this,SLOT(onPushButtonClick()));
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(hide()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPushButtonClick()
{
    int dim = ui->spinBox->value();
    gameWindow = new GameWindow(this, dim);
    gameWindow->show();
}
