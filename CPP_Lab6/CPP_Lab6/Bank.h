//
//  Bank.h
//  CPP_Lab6
//
//  Created by Danil Morozov on 16.05.2023.
//

#ifndef Bank_h
#define Bank_h

#include "helper.h"

using namespace std;

class BankAccount {
    private:

        string accountNumber;
        double balance;
    
    public:
    
    BankAccount(string accountNumber, double balance) {
        this -> accountNumber = accountNumber;
        this -> balance = balance;
    }
    
// Собственные методы
    string getAccName() {
        return this -> accountNumber;
    }
    
    
    int getBalance() {
        return this -> balance;
    }
    
    void setAccName(string name) {
        this -> accountNumber = name;
    }
    
    void decFromBalance(double amount) {
        this -> balance -= amount;
    }
    
    void addToBalance(double amount) {
        this -> balance -= amount;
    }
    
    void setBalance(int amount) {
        this -> balance = amount;
    }
    
// Методы которые будут переопределены
    virtual void displayAccountInfo() {
        cout << "Номер счета: " << getAccName() << endl;
        cout << "Баланс: " << to_string(getBalance()) << endl;
    }
    
    virtual void deposit(double amount) {
        this -> balance += amount;
    }
    
    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            cout << "На счету недостаточно средств. Операция отклонена!" << endl;
        };
    }
    
    virtual void update() {
            string newValue;
            int state;
            cout << "1: Изменить номер счета" << endl;
            cout << "2: Изменить баланс" << endl;
            cout << "3: Внести депозит" << endl;
            cout << "4: Вывести средства" << endl;
            state = input();

            cout << "Введите новое значение: ";
            cin >> newValue;

            switch (state)
            {
            case 1:
                setAccName(newValue);
                break;
            case 2:
                    if (check(newValue)) {
                        setBalance(stod(newValue));
                    }
                    else {
                        cout<< "Ошибка при выполнении операции!" << endl << endl;
                    }
                    break;
            case 3:
                    if (check(newValue)) {
                        deposit(stod(newValue));
                    }
                    else {
                        cout<< "Ошибка при выполнении операции!" << endl << endl;
                    }
                    break;
            case 4:
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
    
    // Методы которые будут унаследованы
    void calcProcentage(){
        cout << "Введите предполагаемый годовой процентной ставки по вкладу: ";
        double prc = input();
        cout << "Выберете кол-во месяцев" << endl;
        cout << "1. 6 месяцев" << endl;
        cout << "2. 12 месяцев" << endl;
        cout << "3. 24 месяца" << endl;
        
        double resultProc = 0.0;
        int months = input();
        
        switch (months) {
            case 1:
                resultProc = (getBalance() * prc * 6 * 30) / (365 * 100);
                break;
            case 2:
                resultProc = (getBalance() * prc * 6 * 30) / (365 * 100);
                break;
            case 3:
                resultProc = (getBalance() * prc * 6 * 30) / (365 * 100);
                break;
            default:
                cout << "Неверный выбор количества месяцев." << endl;
                break;
        }
        cout << "Предполагаемые проценты по вкладу: " << resultProc << endl << endl;

    }
    
    void currencyCheck(){

        double eurRate = 0.85;    // Курс обмена Евро к Доллару США
        double usdRate = 1.18;    // Курс обмена Доллара США к Евро
        double cnyRate = 6.47;    // Курс обмена Юаня к Евро
        double gbpRate = 0.71;    // Курс обмена Фунта к Евро
        double rubRate = 86.36;   // Курс обмена Рубля к Евро
        
        cout << "Введите сумму для перевода валюты: ";
        int amount = input();
        cout << "Выберете исходную валюту для перевода" << endl;
        cout << "1. Евро" << endl;
        cout << "2. Доллар" << endl;
        cout << "3. Юань" << endl;
        cout << "4. Фунт" << endl;
        cout << "5. Рубль" << endl;
        int newCurrency = input();
        
        cout << "Выберете финальную валюту для перевода" << endl;
        cout << "1. Евро" << endl;
        cout << "2. Доллар" << endl;
        cout << "3. Юань" << endl;
        cout << "4. Фунт" << endl;
        cout << "5. Рубль" << endl;
        
        int oldCurrency = input();
        
        double conversionRate = 0.0;

            // Установка курса конверсии на основе выбранных валют
            switch (oldCurrency) {
                case 1: // Исходная валюта: Евро
                    switch (newCurrency) {
                        case 1:
                            conversionRate = 1.0;
                            break;
                        case 2:
                            conversionRate = eurRate / usdRate;
                            break;
                        case 3:
                            conversionRate = eurRate / cnyRate;
                            break;
                        case 4:
                            conversionRate = eurRate / gbpRate;
                            break;
                        case 5:
                            conversionRate = eurRate / rubRate;
                            break;
                        default:
                            cout << "Неверный выбор финальной валюты" << endl;
                            break;
                            
                    }
                    break;
                case 2: // Исходная валюта: Доллар
                    switch (newCurrency) {
                        case 1:
                            conversionRate = usdRate / eurRate;
                            break;
                        case 2:
                            conversionRate = 1.0;
                            break;
                        case 3:
                            conversionRate = usdRate / cnyRate;
                            break;
                        case 4:
                            conversionRate = usdRate / gbpRate;
                            break;
                        case 5:
                            conversionRate = usdRate / rubRate;
                            break;
                        default:
                            cout << "Неверный выбор финальной валюты" << endl;
                            break;
                    }
                    break;
                case 3: // Исходная валюта: Юань
                    switch (newCurrency) {
                        case 1:
                            conversionRate = cnyRate / eurRate;
                            break;
                        case 2:
                            conversionRate = cnyRate / usdRate;
                            break;
                        case 3:
                            conversionRate = 1;
                            break;
                        case 4:
                            conversionRate = cnyRate / gbpRate;
                            break;
                        case 5:
                            conversionRate = cnyRate / rubRate;
                            break;
                        default:
                            cout << "Неверный выбор финальной валюты" << endl;
                            break;
                    }
                    break;
                case 4: // Исходная валюта: Фунт
                    switch (newCurrency) {
                        case 1:
                            conversionRate = gbpRate / eurRate;
                            break;
                        case 2:
                            conversionRate = gbpRate / usdRate;
                            break;
                        case 3:
                            conversionRate = gbpRate / cnyRate;
                            break;
                        case 4:
                            conversionRate = 1;
                            break;
                        case 5:
                            conversionRate = gbpRate / rubRate;
                            break;
                        default:
                            cout << "Неверный выбор финальной валюты" << endl;
                            break;
                    }
                    break;
                case 5: // Исходная валюта: Рубль
                    switch (newCurrency) {
                        case 1:
                            conversionRate = rubRate / eurRate;
                            break;
                        case 2:
                            conversionRate = rubRate / usdRate;
                            break;
                        case 3:
                            conversionRate = rubRate / cnyRate;
                            break;
                        case 4:
                            conversionRate = rubRate / gbpRate;
                            break;
                        case 5:
                            conversionRate = 1;
                            break;
                        default:
                            cout << "Неверный выбор финальной валюты" << endl;
                            break;
                    }
                    break;
                default:
                    cout << "Неверный выбор изначальной валюты" << endl;
                    break;
            };

        // Вычисление конвертированной суммы
        double convertedAmount = amount * conversionRate;
        cout << "Результат перевода: " << convertedAmount << endl << endl;
    }
};


#endif /* Bank_h */
