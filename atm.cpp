#include "atm.h"
#include <iostream>
#include <algorithm>
#include <cmath>
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

    int totalAmount = 0;\
    vector<int> denominations;
    vector<int> smallDenominations;


    for (const auto& pair : this->banknoteCapacity) {
        int denomination = pair.first;
        int quantity = pair.second;
        totalAmount += denomination * quantity;
        denominations.push_back(pair.first);
        if(pair.first <= 50){
            smallDenominations.push_back(pair.first);
        }
    }

    map<int, int> tempBanknoteCapacity = this->banknoteCapacity;

    if(totalAmount < amount){
        return toWithdraw;
    }

    sort(denominations.rbegin(), denominations.rend());
    sort(smallDenominations.rbegin(), smallDenominations.rend());

    double amountToWithdrawnBigger = amount - fmod(amount,100.00);

    double amountToWithdrawnSmaller = fmod(amount,100.00);

    for (int denom : denominations) {
        int count = min((int)(amountToWithdrawnBigger / denom), tempBanknoteCapacity[denom]);
        if (count > 0) {
            toWithdraw[denom] = count;
            amountToWithdrawnBigger -= count * denom;
            tempBanknoteCapacity[denom] -= count;
        }
    }

    map<int, int> tempWithdrawn;

    for(int startingDenom =0; startingDenom<smallDenominations.size();++startingDenom){
        double tempSmallWithdrawn = amountToWithdrawnSmaller;
        tempWithdrawn.clear();

        for(int i = startingDenom; i<smallDenominations.size(); ++i){
            int denom = smallDenominations[i];
            int count = min((int)(tempSmallWithdrawn / denom), tempBanknoteCapacity[denom]);
            if(count>0){
                tempWithdrawn[denom] = count;
                tempSmallWithdrawn-=count*denom;
            }
        }

        if(tempSmallWithdrawn == 0){
            break;
        }
    }

    if(amountToWithdrawnBigger > 0 || amountToWithdrawnSmaller > 0){
        toWithdraw.clear();
        return toWithdraw;
    }

    for (const auto& pair : tempWithdrawn) {
        int denomination = pair.first;
        int count = pair.second;

        if (toWithdraw.find(denomination) != toWithdraw.end()) {
            toWithdraw[denomination] += count;
        } else {
            toWithdraw[denomination] = count;
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
