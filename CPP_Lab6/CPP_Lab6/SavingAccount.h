//
//  SavingAccount_h
//  CPP_Lab6
//
//  Created by Danil Morozov on 16.05.2023.
//

#ifndef SavingAccount_h
#define SavingAccount_h

#include "Bank.h"
#include "helper.h"

using namespace std;

class SavingAccount: public BankAccount {
    private:
    
        double interestRate;
        bool isLocked;
        double savedBalance;
    
    public:
    
    SavingAccount(double interestRate, bool isLocked, double savedBalance, string accountNumber, double balance) : BankAccount(accountNumber, balance) {
        this->interestRate = interestRate;
        this->isLocked = isLocked;
        this->savedBalance = savedBalance;
    }
    
    // Собственные методы
        double getInterestRate() const {
            return this->interestRate;
        }
    
        double getSavedBalance() {
            return this->savedBalance;
        }
    
        void addToSavedBalance(double amount) {
            this-> savedBalance += amount;
        }
    
    
    void decFromSavedBalance(double amount) {
        this-> savedBalance -= amount;
    }

        void setInterestRate(double rate) {
            interestRate = rate;
        }

        bool isAccountLocked() {
            return this->isLocked;
        }


        void lockAccount() {
            isLocked = !isLocked;
        }
        
        void calculateInterest() {
            double interest = savedBalance * (interestRate / 100);
            cout << "Процентное начисление: " << interest << endl;
            savedBalance += interest;
        }
    
    // Переопределенные методы из родительского класса
    
    void displayAccountInfo() override {
            cout << "Информация о сберегательном счете" << endl;
            cout << "Номер счета: " << getAccName() << endl;
            cout << "Баланс: " << getBalance() << " RUB" << endl;
            cout << "Баланс счета вклада: " << getSavedBalance() << " RUB" << endl;
            cout << "Процент начисления: " << getInterestRate() << "%" << endl;
            cout << "Статус счета: " << (isAccountLocked() ? "Заблокирован" : "Разблокирован") << endl;
    }
    
    void deposit(double amount) override {
            if (isLocked) {
                cout << "Счет заблокирован. Операция депозита невозможна." << endl;
            } else {
                if (getBalance() < amount) {
                    cout << "Вывод средств невозможен, на счету недостаточно денег!" << endl;
                } else {
                    decFromBalance(amount);
                    addToSavedBalance(amount);
                }
            }
    }

    void withdraw(double amount) override {
            if (isLocked) {
                cout << "Счет заблокирован. Операция депозита невозможна." << endl;
            } else {
                if (savedBalance < amount) {
                    cout << "Вывод средств невозможен, на сберегательном счету недостаточно денег!" << endl;
                } else {
                    decFromSavedBalance(amount);
                    addToBalance(amount);
                }
            }
    }
    
    void update() override {
            string newValue;
            int state;
            cout << "1: Изменить номер счета" << endl;
            cout << "2: Изменить баланс" << endl;
            cout << "3: Заблокировать/Разблокировать сберегательный счет" << endl;
            cout << "4: Указать процентную ставку" << endl;
            cout << "5: Провести процентное начисление" << endl;
            cout << "6: Депозит средств на сберегательный счет" << endl;
            cout << "7: Вывести средства со сберегательного счета" << endl;
            state = input();


            switch (state)
            {
            case 1:
                    cout << "Введите значение: ";
                    cin >> newValue;
                setAccName(newValue);
                break;
            case 2:
                    cout << "Введите значение: ";
                    cin >> newValue;
                    if (check(newValue)) {
                        setBalance(stod(newValue));
                    }
                    else {
                        cout<< "Ошибка при выполнении операции!" << endl << endl;
                    }
                    break;
            case 3:
                    lockAccount();
                    break;
            case 4:
                    cout << "Введите значение: ";
                    cin >> newValue;
                    if (check(newValue)) {
                        setInterestRate(stod(newValue));
                    }
                    else {
                        cout<< "Ошибка при выполнении операции!" << endl << endl;
                    }
                    break;
            case 5:
                    calculateInterest();
                    break;
                    
            case 6:
                    cout << "Введите значение: ";
                    cin >> newValue;
                    if (check(newValue)) {
                        deposit(stod(newValue));
                    }
                    else {
                        cout<< "Ошибка при выполнении операции!" << endl << endl;
                    }
                    break;
            case 7:
                    cout << "Введите значение: ";
                    cin >> newValue;
                    if (check(newValue)) {
                        withdraw(stod(newValue));
                    }
                    else {
                        cout<< "Ошибка при выполнении операции!" << endl << endl;
                    }
                    break;
            default:
                cout<< "Ошибка при выполнении операции!" << endl << endl;
                break;
            }
        }
};


#endif /* SavingAccount_h */
