#ifndef CARD_H
#define CARD_H
#include <string>
using namespace std;

class Card
{
private:
    string cardNumber;
    string pin;
    bool isLocked;
    string ownerAccountNumber;
public:
    Card();
    Card(string cardNumber, string pin, bool isLocked, string ownerAccountNumber);
    string getCardNumber() const;
    string getPin() const;
    bool getIsLocked() const;
    string getOwnerAccountNumber() const;
    void setPin(std::string newPin);
    void setLockStatus(bool newStatus);
};

#endif // CARD_H
