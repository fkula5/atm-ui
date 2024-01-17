#include "user.h"

User::User(){

}

User::User(int id, string accountNumber, double balance, double dailyLimit, double monthlyLimit, double dailyWithdrawn, double monthlyWithdrawn)
{
    this->userID = id;
    this->accountNumber = accountNumber;
    this->balance = balance;
    this->dailyLimit = dailyLimit;
    this->monthlyLimit = monthlyLimit;
    this->dailyWithdrawn = dailyWithdrawn;
    this->monthlyWithdrawn = monthlyWithdrawn;
}

int User::getUserID()
{
    return this->userID;
}


string User::getAccountNumber()
{
    return string(this->accountNumber);
}


double User::getBalance()
{
    return this->balance;
}


void User::setBalance(double amount)
{
    this->balance = amount;
}


double User::getDailyLimit()
{
    return this->dailyLimit;
}


double User::getMonthtlyLimit()
{
    return this->monthlyLimit;
}


double User::getDailyWithdrawn()
{
    return this->dailyWithdrawn;
}


void User::setDailyWithdrawn(double amount)
{
    this->dailyWithdrawn = amount;
}


double User::getMonthlyWithdrawn()
{
    return this->monthlyWithdrawn;
}


void User::setMonthlyWithdrawn(double amount)
{
    this->monthlyWithdrawn = amount;
}
