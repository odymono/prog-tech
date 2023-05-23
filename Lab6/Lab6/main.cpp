//
//  main.cpp
//  CPP_Lab6
//
//  Created by Danil Morozov on 12.05.2023.
//

#include <iostream>
#include "Bank.h"
#include "SavingAccount.h"
#include "CreditAccount.h"
#include "helper.h"

using namespace std;

int main() {

    bool flag = false;
    string accName;
    bool YN;
    double bal, savBal, creBal, procVal;
    string b, m, o, e, g;
    int y, p, type, msg;

    //заренее создаются указатели на классы, которые, в зависимости от выбора, будут инициализированы
    BankAccount* bank = nullptr;
    header_start();
    

    //пока не будет выбран класс
    while (!flag) {
        type = input();
        switch (type)
        {
        case 1:
            cout << "Введите номер счета" << endl;
            cin >> accName;
            cout << "Введите исходный баланс" << endl;
            bal = inputDouble();
            bank = new BankAccount(accName, bal);
            flag = true;
            break;
        case 2:
            cout << "Введите номер счета" << endl;
            cin >> accName;
            cout << "Введите исходный баланс" << endl;
            bal = inputDouble();
            cout << "Введите процентную ставку" << endl;
            procVal = inputDouble();
            cout << "Аккаунт будет с блокировкой? (Y/N)" << endl;
            YN = inputYesOrNo();
            cout << "Введите исходный баланс на сберегательном счету" << endl;
            savBal = inputDouble();
            bank = new SavingAccount(procVal, YN, savBal, accName, bal);
            flag = true;
            break;
        case 3:
            cout << "Введите номер счета" << endl;
            cin >> accName;
            cout << "Введите исходный баланс" << endl;
            bal = inputDouble();
            cout << "Аккаунт будет иметь кредит? (Y,N)" << endl;
            YN = inputYesOrNo();
            if (YN) {
                cout << "Размер кредита" << endl;
                creBal = inputDouble();
            } else {
                creBal = 0;
            };
            bank = new CreditAccount(creBal*1.10, YN, accName, bal);
            flag = true;
            break;
        default:
            cout << "Произошла ошибка!" << endl;
            flag = false;
            break;
        }
    }

    flag = false;
    header();

    //цикл обработки сообщений для работы с методами класса
    while (!flag) {
        
        cout << "Выберите метод: ";
        msg = input();
        cout << endl;
        //не смотря на то, что объекты имеют разные классы - методы их одинаковы
        //это связано с тем, что некоторые методы являются переопределенными, а некоторые
        // унаследованными от родительского класса
        switch (msg)
        {
        case 1: //вывод всех полей
            bank->displayAccountInfo();
            break;
        case 2:
            bank->update(); //обновление одного поля
            break;
        case 3:
            bank->calcProcentage(); //расситать проценты
            break;
        case 4:
            bank->currencyCheck(); //перевод валют
            break;
        case 5:
            //переопределение типов
            //нужно это для того, чтобы можно было обращатся к собственным методам каждого класса класса
            if (type == 1) {
                //собственные методы класса BankAccount
                cout << "Номер счета: " << bank->getAccName() << endl;
                cout << "Баланс: " << bank->getBalance() << " RUB" << endl;
            }
            if (type == 2) {
                
                bool locked = ((SavingAccount*)bank)->isAccountLocked();
                cout << "Процентная ставка: " << ((SavingAccount*)bank)->getInterestRate() << endl;
                cout << "Статус счета: " << (locked ? "Заблокирован" : "Разблокирован") << endl;
                cout << "Баланс сберегательного счета: " << ((SavingAccount*)bank)->getSavedBalance() << endl;
            }
            if (type == 3) {
                //собственные методы класса CreditAccount
                cout << "Наличие кредита: " << (((CreditAccount*)bank)->getHasCredit() ? "Имеется" : "Не имеется") << endl;
                cout << "Размер кредита: " << ((CreditAccount*)bank)->getCreditAmount() << endl;
            }
            break;
        case 6:
                flag = false;
                header_start();
                type = input();
                switch (type)
                {
                case 1:
                    cout << "Введите номер счета" << endl;
                    cin >> accName;
                    cout << "Введите исходный баланс" << endl;
                    bal = inputDouble();
                    bank = new BankAccount(accName, bal);
                    flag = false;
                        header();
                    break;
                case 2:
                    cout << "Введите номер счета" << endl;
                    cin >> accName;
                    cout << "Введите исходный баланс" << endl;
                    bal = inputDouble();
                    cout << "Введите процентную ставку" << endl;
                    procVal = inputDouble();
                    cout << "Аккаунт будет с блокировкой? (Y/N)" << endl;
                    YN = inputYesOrNo();
                    cout << "Введите исходный баланс на сберегательном счету" << endl;
                    savBal = inputDouble();
                    bank = new SavingAccount(procVal, YN, savBal, accName, bal);
                    flag = false;
                        header();
                    break;
                case 3:
                    cout << "Введите номер счета" << endl;
                    cin >> accName;
                    cout << "Введите исходный баланс" << endl;
                    bal = inputDouble();
                    cout << "Аккаунт будет иметь кредит? (Y,N)" << endl;
                    YN = inputYesOrNo();
                    if (YN) {
                        cout << "Размер кредита" << endl;
                        creBal = inputDouble();
                    } else {
                        creBal = 0;
                    };
                    bank = new CreditAccount(creBal*1.10, YN, accName, bal);
                    flag = false;
                        header();
                    break;
                default:
                    cout << "Произошла ошибка!" << endl;
                    flag = false;
                    break;
                }
                break;
        case 7:
            //очищение памяти происходит по такой логике, потому что не нужно очищать те указатели, которые не выбраны
            //то есть, очищается указатель только того класса, с которым велась работа
            delete bank;
            flag = true;
            break;
        default:
            cout << "Произошла ошибка!" << endl;
            break;
        }
    }
};
