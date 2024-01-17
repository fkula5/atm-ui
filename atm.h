#ifndef ATM_H
#define ATM_H
#include "User.h"
#include <map>

class ATM
{
public:
    void deposit(User& user, double amount, map<int, int>& banknoteStock);
    bool withdrawn(User& user, double amount);
    void bankStatement(User& user);
    void checkCardStatus();
    ATM(const map<int, int>& initialCapacity);
    ATM();
    void showBankotes();
private:
    map<int, int> banknoteCapacity;
};

#endif // ATM_H
