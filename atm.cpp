#include "atm.h"
#include <iostream>
#include <algorithm>

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

bool ATM::withdrawn(User& user, double amount)
{
    if (amount <= 0) {
        return false;
    }

    if (user.getMonthlyWithdrawn() > user.getMonthtlyLimit() || (user.getMonthlyWithdrawn() + amount) > user.getMonthtlyLimit()) {
        return false;
    }

    if (user.getDailyWithdrawn() > user.getDailyLimit() || (user.getDailyWithdrawn() + amount) > user.getDailyLimit()) {
        return false;
    }

    if (user.getBalance() - amount < 0) {
        return false;
    }

    vector<int> denominations;
    for (auto& pair : this->banknoteCapacity) {
        denominations.push_back(pair.first);
    }

    sort(denominations.rbegin(), denominations.rend());

    map<int, int> toWithdraw;

    double amountToWitdraw = amount;

    for (int denom : denominations) {
        int count = min((int)(amountToWitdraw / denom), this->banknoteCapacity[denom]);
        if (count > 0) {
            toWithdraw[denom] = count;
            amountToWitdraw -= count * denom;
        }
    }

    for (auto& pair : toWithdraw) {
        this->banknoteCapacity[pair.first] -= pair.second;
    }

    double newUserBalance = user.getBalance() - amount;
    double newUserDailyWithdrawn = user.getDailyWithdrawn() + amount;
    double newUserMonthlyWithdrawn = user.getMonthlyWithdrawn() + amount;

    user.setBalance(newUserBalance);
    user.setDailyWithdrawn(newUserDailyWithdrawn);
    user.setMonthlyWithdrawn(newUserMonthlyWithdrawn);

    return true;
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
