#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "atm.h"
#include "card.h"
#include "user.h"
#include "atm.h"
#include "card.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_25_clicked();

private:
    Ui::MainWindow *ui;
    ATM *atm;
    User *user;
    Card *card;
    void changeKeyboardTarget(int currectIndex, QString value);
};
#endif // MAINWINDOW_H
