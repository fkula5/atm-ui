#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    atm = new ATM({{100, 5}, {50, 10}, {20, 15}, {10, 20}});
    user = nullptr;
    card = nullptr;
    ui->setupUi(this);
    int defaultIndex = 1;
    ui->stackedWidget->setCurrentIndex(defaultIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeKeyboardTarget(int currectIndex, QString value){
    switch(currectIndex){
    case 2:
        ui->withdrawnInput->insert(value);
        break;
    case 5:
        ui->pin->insert(value);
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    this->changeKeyboardTarget(ui->stackedWidget->currentIndex(), "1");
}


void MainWindow::on_pushButton_12_clicked()
{
    this->changeKeyboardTarget(ui->stackedWidget->currentIndex(), "2");
}


void MainWindow::on_pushButton_13_clicked()
{

    this->changeKeyboardTarget(ui->stackedWidget->currentIndex(), "3");
}


void MainWindow::on_pushButton_14_clicked()
{
    if(ui->pin->text() == "2137"){
        this->user = new User(456, "XYZ7890", 500.0, 2000.0, 15000.0, 100.0, 1000.0);
        ui->pin->clear();
        ui->stackedWidget->setCurrentIndex(0);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    this->changeKeyboardTarget(ui->stackedWidget->currentIndex(), "4");
}


void MainWindow::on_pushButton_5_clicked()
{
    this->changeKeyboardTarget(ui->stackedWidget->currentIndex(), "5");
}


void MainWindow::on_pushButton_6_clicked()
{
    this->changeKeyboardTarget(ui->stackedWidget->currentIndex(), "6");
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->pin->clear();
}


void MainWindow::on_pushButton_4_clicked()
{
    this->changeKeyboardTarget(ui->stackedWidget->currentIndex(), "7");
}


void MainWindow::on_pushButton_8_clicked()
{
    this->changeKeyboardTarget(ui->stackedWidget->currentIndex(), "8");
}


void MainWindow::on_pushButton_9_clicked()
{
    this->changeKeyboardTarget(ui->stackedWidget->currentIndex(), "9");
}


void MainWindow::on_pushButton_15_clicked()
{
    //remove card, cancel transactions
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_10_clicked()
{
    this->changeKeyboardTarget(ui->stackedWidget->currentIndex(), "0");
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


void MainWindow::on_pushButton_23_clicked()
{
    if(ui->stackedWidget->currentIndex()==0){
        ui->accountNumber->insert(QString::fromStdString(this->user->getAccountNumber()));
        ui->balance->insert(QString::number(this->user->getBalance()));
        ui->dailyLimit->insert(QString::number(this->user->getDailyLimit()));
        ui->monthlyLimit->insert(QString::number(this->user->getMonthtlyLimit()));
        ui->dailyWithdrawn->insert(QString::number(this->user->getDailyWithdrawn()));
        ui->monthlyWithdrawn->insert(QString::number(this->user->getMonthlyWithdrawn()));
    }
}


void MainWindow::on_pushButton_25_clicked()
{
    if(ui->stackedWidget->currentIndex()==1){
        ui->stackedWidget->setCurrentIndex(5);
    }
}

