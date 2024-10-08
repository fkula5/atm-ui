#include "atm.h"
#include <iostream>
#include <algorithm>
#include <QMessageBox>

ATM::ATM(){

}

ATM::ATM(const map<int, int>& initialCapacity) {
    this->banknoteCapacity = initialCapacity;
}

void ATM::showBankotes()
{
    for (const auto& pair : this->banknoteCapacity) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

void ATM::deposit(User& user, double amount, map<int, int>& banknoteStock)
{
    if (amount <= 0) {
        return;
    }

    for (const auto& pair : banknoteStock) {
        this->banknoteCapacity[pair.first] += pair.second;
    }

    double newUserBalance = user.getBalance() + amount;
    user.setBalance(newUserBalance);
}

map<int, int> ATM::withdrawn(User& user, double amount)
{
    map<int, int> toWithdraw;

    if (amount <= 0) {
        return toWithdraw;;
    }

    if (user.getMonthlyWithdrawn() > user.getMonthtlyLimit() || (user.getMonthlyWithdrawn() + amount) > user.getMonthtlyLimit()) {
        return toWithdraw;
    }

    if (user.getDailyWithdrawn() > user.getDailyLimit() || (user.getDailyWithdrawn() + amount) > user.getDailyLimit()) {
        return toWithdraw;
    }

    if (user.getBalance() - amount < 0) {
        return toWithdraw;
    }

    vector<int> denominations;

    for(auto & pair : this->banknoteCapacity){
        denominations.push_back(pair.first);
    }

    sort(denominations.rbegin(), denominations.rend());

    map<int, int> tempWithdrawn;
    double tempAmount;
    map<int, int> correctWithdraw;

    for(int startingDenom = denominations.size()-1; startingDenom >= 0; startingDenom--){
        tempWithdrawn.clear();
        tempAmount = amount;

        for(int i = startingDenom; i < denominations.size(); i++){
            int denom = denominations[i];
            int count = min((int)(tempAmount/denom), this->banknoteCapacity[denom]);
            if(count>0){
                tempWithdrawn[denom] = count;
                tempAmount -= count*denom;
            }
        }

        if(tempAmount == 0){
            correctWithdraw = tempWithdrawn;
        }
    }

    toWithdraw = correctWithdraw;

    for (auto& pair : toWithdraw) {
        this->banknoteCapacity[pair.first] -= pair.second;
    }

    double newUserBalance = user.getBalance() - amount;
    double newUserDailyWithdrawn = user.getDailyWithdrawn() + amount;
    double newUserMonthlyWithdrawn = user.getMonthlyWithdrawn() + amount;

    user.setBalance(newUserBalance);
    user.setDailyWithdrawn(newUserDailyWithdrawn);
    user.setMonthlyWithdrawn(newUserMonthlyWithdrawn);

    return toWithdraw;
}

void ATM::bankStatement(User& user)
{
    cout << "Account number: " << user.getAccountNumber() << endl;
    cout << "Balance: " << user.getBalance() << endl;
    cout << "Daily limit: " << user.getDailyLimit() << endl;
    cout << "Monthly limit: " << user.getMonthtlyLimit() << endl;
    cout << "Daily withdrawn: " << user.getDailyWithdrawn() << endl;
    cout << "Monthly withdrawn: " << user.getMonthlyWithdrawn() << endl;

    this->showBankotes();
}
