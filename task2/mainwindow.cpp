#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int mode = ui->comboBox->currentIndex();
    switch (mode)
    {
    case 0:
    {
        task1 a;
        a.exec();
        break;
    }
    case 1:
    {
        task2 a;
        a.exec();
        break;
    }
    case 2:
    {
        task3 a;
        a.exec();
        break;
    }
    }
}

