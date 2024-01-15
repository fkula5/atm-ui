#include "card.h"

Card::Card(string cardNumber, string pin, bool isLocked, string ownerAccountNumber)
    : cardNumber(cardNumber), pin(pin), isLocked(isLocked), ownerAccountNumber(ownerAccountNumber) {}

string Card::getCardNumber() const {
    return this->cardNumber;
}

string Card::getPin() const {
    return this->pin;
}

bool Card::getIsLocked() const {
    return this->isLocked;
}

string Card::getOwnerAccountNumber() const {
    return this->ownerAccountNumber;
}

void Card::setPin(string newPin) {
    this->pin = newPin;
}

void Card::setLockStatus(bool newStatus) {
    this->isLocked = newStatus;
}
