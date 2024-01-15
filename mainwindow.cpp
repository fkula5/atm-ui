#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int defaultIndex = 4;
    ui->stackedWidget->setCurrentIndex(defaultIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->pin->insert("1");
}


void MainWindow::on_pushButton_12_clicked()
{
    ui->pin->insert("2");
}


void MainWindow::on_pushButton_13_clicked()
{
    ui->pin->insert("3");
}


void MainWindow::on_pushButton_14_clicked()
{
    if(ui->pin->text() == "2137"){
        ui->stackedWidget->setCurrentIndex(0);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->pin->insert("4");
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->pin->insert("5");
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->pin->insert("6");
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->pin->clear();
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->pin->insert("7");
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->pin->insert("8");
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->pin->insert("9");
}


void MainWindow::on_pushButton_15_clicked()
{
    //remove card, cancel transactions
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->pin->insert("0");
}


void MainWindow::on_pushButton_22_clicked()
{
    if(ui->stackedWidget->currentIndex()==0){
        ui->stackedWidget->setCurrentIndex(3);
    }
}


void MainWindow::on_pushButton_20_clicked()
{
    if(ui->stackedWidget->currentIndex()==0){
        ui->stackedWidget->setCurrentIndex(1);
    }
}


void MainWindow::on_pushButton_24_clicked()
{
    if(ui->stackedWidget->currentIndex()==1){
        ui->stackedWidget->setCurrentIndex(2);
    }
}

