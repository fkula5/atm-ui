#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    atm = new ATM({{200, 5},{100, 5}, {50, 10}, {20, 15}, {10, 0}});
    user = nullptr;
    card = nullptr;
    database = nullptr;
    ui->setupUi(this);
    int defaultIndex = 1;
    ui->stackedWidget->setCurrentIndex(defaultIndex);
    ui->stackedWidget_2->setCurrentIndex(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeKeyboardTarget(int currectIndex, QString value){
    switch(currectIndex){
    case 3:
        ui->withdrawnInput->insert(value);
        break;
    case 5:
        ui->pin->insert(value);
        break;
    }
}

void MainWindow::withdrawPipeLine(double withdrawnValue){
    this->valueToWithdrawn = withdrawnValue;
    map<int,int> banknotes =  this->atm->withdrawn(*this->user, this->valueToWithdrawn);
    QMessageBox::information(this, "title", QString::number(this->user->getBalance()));
    if(banknotes.empty()){
        ui->stackedWidget->setCurrentIndex(1);
        return;
    }
    ui->banknote10->insert(QString::number(banknotes[10]));
    ui->banknote20->insert(QString::number(banknotes[20]));
    ui->banknote50->insert(QString::number(banknotes[50]));
    ui->banknote100->insert(QString::number(banknotes[100]));
    ui->banknote200->insert(QString::number(banknotes[200]));
    ui->banknote500->insert(QString::number(banknotes[500]));
    card=nullptr;
    user=nullptr;
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidget->setCurrentIndex(1);
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
    if(ui->stackedWidget->currentIndex()==3){
        this->withdrawPipeLine(ui->withdrawnInput->text().toDouble());
        return;
    }

    if(ui->stackedWidget->currentIndex()==4){
        map<int, int> insertBanknotes;
        double amountToDepo=0;
        insertBanknotes.insert({10, ui->amount10->text() != "" ?  ui->amount10->text().toDouble(): 0});
        insertBanknotes.insert({20,ui->amount20->text() != "" ?  ui->amount20->text().toDouble(): 0});
        insertBanknotes.insert({50, ui->amount50->text() != "" ?  ui->amount50->text().toDouble(): 0});
        insertBanknotes.insert({100, ui->amount100->text() != "" ?  ui->amount100->text().toDouble(): 0});
        insertBanknotes.insert({200, ui->amount200->text() != "" ?  ui->amount200->text().toDouble(): 0});
        insertBanknotes.insert({500, ui->amount500->text() != "" ?  ui->amount500->text().toDouble(): 0});

        for (const auto& pair : insertBanknotes) {
            amountToDepo = amountToDepo + (pair.first * pair.second);
        }

        this->atm->deposit(*this->user, amountToDepo, insertBanknotes);
        QMessageBox::information(this, "title", QString::number(this->user->getBalance()));
        card=nullptr;
        user=nullptr;
        ui->stackedWidget->setCurrentIndex(1);
        return;
    }

    if(ui->stackedWidget->currentIndex() == 5){
        if(ui->pin->text().toStdString() == card->getPin()){

            QMap<QString, QVariant> params = {{":accountNumber", QString::fromStdString(this->card->getOwnerAccountNumber())}};

            QSqlQuery query = this->database->executeQuery("SELECT * FROM users WHERE account_number = :accountNumber", params);

            if(!query.next()){
                return;
            }

            this->card->incorrectPinAttemps = 0;
            this->user = new User(query.value(0).toInt(), query.value(1).toString().toStdString(), query.value(2).toDouble(), query.value(3).toDouble(), query.value(4).toDouble(), query.value(5).toDouble(), query.value(6).toDouble());
            ui->pin->clear();
            ui->stackedWidget->setCurrentIndex(0);
        }
        else{
            this->card->incorrectPinAttemps++;
            if(this->card->incorrectPinAttemps >=3){
                this->card->setLockStatus(true);
                QString dirPath = "C:/Users/f3kul/Desktop/Folderki/atm-ui/cards";
                QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), dirPath, tr("Files (*.*)*"));
                QFile file(fileName);
                if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QTextStream out(&file);

                    stringstream ss;

                    ss<<boolalpha<<this->card->getIsLocked();

                    out << QString::fromStdString(this->card->getCardNumber()) << '\n';
                    out << QString::fromStdString(this->card->getPin()) << '\n';
                    out << QString::fromStdString(ss.str()) << '\n';
                    out << QString::fromStdString(this->card->getOwnerAccountNumber()) << '\n';

                    file.close();
                }
                ui->stackedWidget->setCurrentIndex(1);
            }else{
                ui->pin->clear();
            }
        }
        return;
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
    card=nullptr;
    user=nullptr;
    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget_2->setCurrentIndex(2);
}


void MainWindow::on_pushButton_10_clicked()
{
    this->changeKeyboardTarget(ui->stackedWidget->currentIndex(), "0");
}


void MainWindow::on_pushButton_22_clicked()
{
    if(ui->stackedWidget->currentIndex()==0){
        ui->stackedWidget->setCurrentIndex(4);
        return;
    }

    if(ui->stackedWidget->currentIndex()==2){
        this->withdrawPipeLine(20.0);
    }
}


void MainWindow::on_pushButton_20_clicked()
{
    if(ui->stackedWidget->currentIndex()==0){
        ui->stackedWidget->setCurrentIndex(2);
        return;
    }

    if(ui->stackedWidget->currentIndex()==2){
        this->withdrawPipeLine(200.0);
    }
}


void MainWindow::on_pushButton_24_clicked()
{
    if(ui->stackedWidget->currentIndex()==2){
        ui->stackedWidget->setCurrentIndex(3);
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
        card=nullptr;
        user=nullptr;
        ui->stackedWidget_2->setCurrentIndex(0);
        ui->stackedWidget->setCurrentIndex(1);
    }

    if(ui->stackedWidget->currentIndex()==2){
        this->withdrawPipeLine(10.0);
    }
}


void MainWindow::on_pushButton_25_clicked()
{
    ui->banknote10->clear();
    ui->banknote20->clear();
    ui->banknote50->clear();
    ui->banknote100->clear();
    ui->banknote200->clear();
    ui->banknote500->clear();

    if(ui->stackedWidget->currentIndex()==1){

        this->database = new Database("C:/Users/f3kul/Desktop/Folderki/atm-ui/bank.db");

        QString dirPath = "C:/Users/f3kul/Desktop/Folderki/atm-ui/cards";

        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), dirPath, tr("Files (*.*)*"));

        QFile file(fileName);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            string data[4];
            int i = 0;
            QTextStream in(&file);
            while(!in.atEnd()){
                string line = in.readLine().toStdString();
                data[i] = line;
                i++;
            }
            if(!this->database->open()){
                QMessageBox::warning(this, "title", this->database->lastError());
                return;
            }

            QMap<QString, QVariant> params = {{":accountNumber", QString::fromStdString(data[3])}};

            QSqlQuery query = this->database->executeQuery("SELECT * FROM users WHERE account_number = :accountNumber", params);

            if(!query.next()){
                return;
            }

            bool isCardLocked;
            istringstream(data[2]) >> isCardLocked;

            if(isCardLocked){
                return;
            }

            this->card = new Card(data[0], data[1], isCardLocked, data[3]);
            file.close();
        }
        ui->stackedWidget->setCurrentIndex(5);
        ui->stackedWidget_2->setCurrentIndex(2);
    }
}


void MainWindow::on_pushButton_17_clicked()
{
    if(ui->stackedWidget->currentIndex()==2){
        this->withdrawPipeLine(500.0);
    }
}


void MainWindow::on_pushButton_19_clicked()
{
    if(ui->stackedWidget->currentIndex()==2){
        this->withdrawPipeLine(400.0);
    }
}


void MainWindow::on_pushButton_21_clicked()
{
    if(ui->stackedWidget->currentIndex()==2){
        this->withdrawPipeLine(100.0);
    }
}


void MainWindow::on_pushButton_18_clicked()
{
    if(ui->stackedWidget->currentIndex()==2){
        this->withdrawPipeLine(50.0);
    }
}
