#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User
{
private:
    int userID;
    string accountNumber;
    double balance, dailyLimit, monthlyLimit, dailyWithdrawn, monthlyWithdrawn;

public:
    User();
    User(int id, string accountNumber, double balance, double dailyLimit, double monthlyLimit, double dailyWithdrawn, double monthlyWithdrawn);
    int getUserID();
    string getAccountNumber();
    double getBalance();
    void setBalance(double amount);
    double getDailyLimit();
    double getMonthtlyLimit();
    double getDailyWithdrawn();
    void setDailyWithdrawn(double amount);
    double getMonthlyWithdrawn();
    void setMonthlyWithdrawn(double amount);
};

#endif // USER_H
