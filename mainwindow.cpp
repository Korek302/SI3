#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(released()),this,SLOT(onPushButtonClick()));
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(hide()));

    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(onPushButton_2Click()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(hide()));
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

void MainWindow::onPushButton_2Click()
{
    int dim = ui->spinBox->value();
    gameWindowPvE = new GameWindowPvE(this, dim);
    gameWindowPvE->show();
}
