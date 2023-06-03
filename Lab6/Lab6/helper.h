//
//  helper.h
//  CPP_Lab6
//
//  Created by Danil Morozov on 16.05.2023.
//

#ifndef helper_h
#define helper_h

#include <iostream>
#include <string>

using namespace std;

bool checkDouble(string inp) {
    for (char c : inp) {
        if (!(c == '.' or isdigit(c) or c == '-')) {
            return false;
        }
    }
    return true;
}

bool check(string inp) {
    for (char c : inp) {
        if (!isdigit(c) or c == '-') {
            return false;
        }
    }
    return true;
}

int checkYN(char inp) {
    if (!(inp == 'Y' or inp == 'N' or inp == 'y' or inp == 'n')) {
        return 0;
    } else {
        if (inp == 'Y' or inp == 'y') {
            return 1;
        } else {
            return 2;
        };
    };
}

int input() {
    string inp;
    cin >> inp;
    while (!check(inp)) {
        cout << "Ошибка ввода! \n" << "Повторите: ";
        cin.clear();
        cin >> inp;
    }
    return stoi(inp);
}

double inputDouble() {
    string inp;
    cin >> inp;
    while (!checkDouble(inp)) {
        cout << "Ошибка ввода! \n" << "Повторите: ";
        cin.clear();
        cin >> inp;
    }
    return stod(inp);
}

bool inputYesOrNo() {
    char inp;
    cin >> inp;
    while (checkYN(inp) == 0) {
        cout << "Ошибка ввода! \n" << "Повторите: ";
        cin.clear();
        cin >> inp;
    }
    if (inp == 'Y' or inp == 'y') {
        return true;
    } else {
        return false;
    };
}

void header_start() {
    cout << "Выберите класс, с которым хотите работать:" << endl;
    cout << "1) Банк" << endl;
    cout << "2) Сберегательный счет" << endl;
    cout << "3) Кредитный аккаунт" << endl;
}

void header() {
    cout << endl << "1) Вывести поля объекта" << endl;
    cout << "2) Изменить поле объекта" << endl;
    cout << "3) Расчитать проценты" << endl;
    cout << "4) Перевести валюты" << endl;
    cout << "5) Вывести собственные поля класса" << endl;
    cout << "6) Выйти в меню" << endl;
    cout << "7) Закрыть программу" << endl;
}


#endif /* helper_h */
