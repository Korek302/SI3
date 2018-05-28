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

    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(onPushButton_3Click()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(hide()));

    QStringList list=(QStringList()<<"colorless"<<"colorful"<<"one-for-one");
    ui->comboBox->addItems(list);
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete gameWindowPvP;
    //delete gameWindowPvE;
    //delete gameWindowEvE;
}

void MainWindow::onPushButtonClick()
{
    int dim = ui->spinBox->value();
    gameWindowPvP = new GameWindowPvP(this, dim);
    gameWindowPvP->show();
}

void MainWindow::onPushButton_2Click()
{
    int dim = ui->spinBox->value();
    int depth = ui->spinBox_2->value();
    bool aiStart = ui->checkBox->isChecked();
    bool alfabeta = ui->checkBox_2->isChecked();
    int gameMode = ui->comboBox->currentIndex();
    int nodeTraversal = ui->comboBox_2->currentIndex();
    gameWindowPvE = new GameWindowPvE(this, dim, aiStart, depth, alfabeta, gameMode, nodeTraversal);
    gameWindowPvE->show();
}

void MainWindow::onPushButton_3Click()
{
    int dim = ui->spinBox->value();
    int depth = ui->spinBox_2->value();
    bool aiStart = ui->checkBox->isChecked();
    bool alfabeta = ui->checkBox_2->isChecked();
    int gameMode = ui->comboBox->currentIndex();
    int nodeTraversal = ui->comboBox_2->currentIndex();
    gameWindowEvE = new GameWindowEvE(this, dim, aiStart, depth, alfabeta, gameMode, nodeTraversal);
    gameWindowEvE->show();
}
