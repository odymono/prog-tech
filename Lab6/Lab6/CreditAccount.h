//
//  CreditAccount.h
//  CPP_Lab6
//
//  Created by Danil Morozov on 17.05.2023.
//

#ifndef CreditAccount_h
#define CreditAccount_h

#include "Bank.h"
#include "helper.h"

using namespace std;

class CreditAccount : public BankAccount {
private:
    
    double creditAmount;
    bool hasCredit;
    
public:
    
    CreditAccount(double creditAmount, bool hasCredit, string accountNumber, double balance) : BankAccount(accountNumber, balance) {
        this -> creditAmount = creditAmount;
        this -> hasCredit = hasCredit;
    }
    
    bool getHasCredit() {
        if (creditAmount == 0) {
            this->hasCredit = false;
        }
        return this->hasCredit;
    }
    
    double getCreditAmount() {
        return this-> creditAmount;
    }
    
    void takeCredit(double amount) {
        this -> creditAmount = (amount * 1.10);
    }
    
    void setCreditAmount(double amount) {
        this -> creditAmount = amount;
    }
    
    void pay(double amount) {
        this -> creditAmount -=  amount;
    }
    
    void setCredit() {
        this -> hasCredit = true;
    }
    
    // Перекрытые методы
    void displayAccountInfo() override {
            cout << "Информация о кредитном счете" << endl;
            cout << "Номер счета: " << getAccName() << endl;
            cout << "Баланс: " << getBalance() << " RUB" << endl;
            cout << "Ваш кредитный процент - 10%" << endl;
            cout << "Статус кредита: " << (getHasCredit() ? "Имеется" : "Не имеется") << endl;
            cout << "Размер заема: " << getCreditAmount() << " RUB" << endl;
    }
    
    void deposit(double amount) override {
        if (hasCredit) {
            if (amount > getBalance()) {
                cout << "Недостаточно средств для пополнения кредитного счета" << endl;
            } else {
                if (amount == creditAmount) {
                    setCreditAmount(0);
                    decFromBalance(amount);
                    hasCredit = false;
                } else if (amount < creditAmount) {
                    decFromBalance(amount);
                    pay(amount);
                } else {
                    cout << "Вы не можете внести платеж превышающий заем" << endl;
                };
            };

        } else {
            cout << "У вас нет задолжностей" << endl;
        }
        }

    void withdraw(double amount) override {
        if (getHasCredit()){
            cout << "Вы не можете взять заем, имеется задолженность!" << endl;
        } else {
            if (amount >= 50000) {
                cout << "Вы не можете взять заем выше 50000 RUB" << endl;
            } else {
                setCredit();
                takeCredit(amount);
                addToBalance(amount);
                cout << "Кредит на сумму " << amount << " RUB был взят" << endl;
            };
        };
        }
    
    void update() override {
            string newValue;
            int state;
            cout << "1: Изменить номер счета" << endl;
            cout << "2: Изменить баланс" << endl;
            cout << "3: Проверить наличие кредита" << endl;
            cout << "4: Взять кредит" << endl;
            cout << "5: Депозит средств на кредитный счет" << endl;
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
                    cout << "Статус кредита: " << (getHasCredit() ? "Имеется" : "Не имеется") << endl;
                    break;
            case 4:
                    cout << "Введите значение: ";
                    cin >> newValue;
                    if (check(newValue)) {
                        withdraw(stod(newValue));
                    }
                    else {
                        cout<< "Ошибка при выполнении операции!" << endl << endl;
                    }
                    break;
            case 5:
                    cout << "Введите значение: ";
                    cin >> newValue;
                    if (check(newValue)) {
                        deposit(stod(newValue));
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

#endif /* CreditAccount_h */
