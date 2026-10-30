#include <iostream>
#include "Input.h"
using namespace std;

int inputInt(const string& prompt, int minValue, int maxValue) {
    int value = 0;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.good() && cin.peek() == '\n' && value >= minValue && value <= maxValue) {
            cin.ignore(100, '\n');
            break;
        }
        cin.clear();
        cout << "\nнеправильный ввод данных\n";
        cin.ignore(100, '\n');
    }
    return value;
}


float inputFloat(const string& prompt, float minValue, float maxValue) {
    float value = 0;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.good() && cin.peek() == '\n' && value >= minValue && value <= maxValue) {
            cin.ignore(100, '\n');
            break;
        }
        cin.clear();
        cout << "\nнеправильный ввод данных\n";
        cin.ignore(100, '\n');
    }
    return value;
}

// убирает пробелы в начале и в конце строки
static string trim(const string& text) {
    size_t first = text.find_first_not_of(" \t");
    if (first == string::npos) return "";
    size_t last = text.find_last_not_of(" \t");
    return text.substr(first, last - first + 1);
}

// ввод непустой строки 
string inputString(const string& prompt, int maxLength) {
    string text;
    while (true) {
        cout << prompt;
        getline(cin, text);
        text = trim(text);
        if (cin.good() && !text.empty() && (int)text.length() <= maxLength) break;
        cin.clear();
        cout << "\nнеправильный ввод данных\n";
    }
    return text;
}

// выбор да/нет: 1 - да, 0 - нет
bool inputYesNo(const string& prompt) {
    return inputInt(prompt + "(1 - да, 0 - нет)-> ", 0, 1) == 1;
}


void inputDate(const string& prompt, int& day, int& month, int& year) {
    char firstDot = 0;
    char secondDot = 0;
    while (true) {
        cout << prompt;
        cin >> day >> firstDot >> month >> secondDot >> year;
        if (cin.good() && cin.peek() == '\n' && firstDot == '.' && secondDot == '.'
            && WorkRecord::isValidDate(day, month, year)) {
            cin.ignore(100, '\n');
            break;
        }
        cin.clear();
        cout << "\nнеправильный ввод данных\n";
        cin.ignore(100, '\n');
    }
}

string inputFullName() {
    return inputString("введите фио (до " + to_string(MAX_NAME_LENGTH) + " символов)-> ", MAX_NAME_LENGTH);
}

string inputPosition() {
    return inputString("введите должность (до " + to_string(MAX_POSITION_LENGTH) + " символов)-> ", MAX_POSITION_LENGTH);
}

string inputDepartment() {
    return inputString("введите отделение (до " + to_string(MAX_DEPARTMENT_LENGTH) + " символов)-> ", MAX_DEPARTMENT_LENGTH);
}

float inputHours() {
    return inputFloat("введите количество часов (от 0.5 до 24)-> ", 0.5f, 24.0f);
}

WorkRecord inputRecord() {
    WorkRecord rec;
    rec.setFullName(inputFullName());
    rec.setPosition(inputPosition());
    rec.setDepartment(inputDepartment());
    int day, month, year;
    inputDate("введите дату смены (дд.мм.гггг)-> ", day, month, year);
    rec.setDate(day, month, year);
    rec.setHours(inputHours());
    return rec;
}