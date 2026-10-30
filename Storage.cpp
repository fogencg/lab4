#include <iostream>
#include <fstream>
#include "Storage.h"
#include "Input.h"
#include "Table.h"
using namespace std;

bool matchesFilter(const WorkRecord& rec, int mode, const string& text, float from, float to) {
    switch (mode) {
    case 1: return rec.getDepartment() == text;
    case 2: return rec.getPosition() == text;
    case 3: return rec.getHours() >= from && rec.getHours() <= to;
    case 4: return rec.getOvertime() > 0;
    }
    return false;
}

Storage::Storage(const string& title) : title(title), nextId(1) {}

Storage::~Storage() {}

const string& Storage::getTitle() const {
    return title;
}

// добавление записей
void Storage::addInteractive() {
    while (true) {
        cout << "\nввод новой записи\n";
        WorkRecord rec = inputRecord();
        rec.setId(nextId);
        if (add(rec)) {
            nextId++;
            cout << "\nзапись добавлена, номер записи: " << rec.getId() << "\n";
        }
        else {
            cout << "\nзапись не добавлена: в контейнере уже есть запись с таким фио и датой\n";
        }
        if (!inputYesNo("\nдобавить еще одну запись? ")) break;
    }
}

void Storage::removeInteractive() {
    if (size() == 0) {
        cout << "\nконтейнер пуст\n";
        return;
    }
    print(cout);
    int id = inputInt("\nвведите номер записи для удаления (0 - отмена)-> ", 0, MAX_ID);
    if (id == 0) return;
    WorkRecord rec;
    if (!findById(id, rec)) {
        cout << "\nзапись с номером " << id << " не найдена\n";
        return;
    }
    printTableSingle(cout, rec);
    if (inputYesNo("\nудалить эту запись? ")) {
        removeById(id);
        cout << "\nзапись удалена\n";
    }
    else {
        cout << "\nудаление отменено\n";
    }
}


void Storage::editInteractive() {
    if (size() == 0) {
        cout << "\nконтейнер пуст\n";
        return;
    }
    print(cout);
    int id = inputInt("\nвведите номер записи для редактирования (0 - отмена)-> ", 0, MAX_ID);
    if (id == 0) return;
    WorkRecord original;
    if (!findById(id, original)) {
        cout << "\nзапись с номером " << id << " не найдена\n";
        return;
    }

    WorkRecord edited = original;
    while (true) {
        cout << "\nтекущие данные записи:\n";
        printTableSingle(cout, edited);
        cout << "\nвыберите поле для изменения:\n";
        cout << "1 - фио\n";
        cout << "2 - должность\n";
        cout << "3 - отделение\n";
        cout << "4 - дата\n";
        cout << "5 - часы\n";
        cout << "6 - сохранить изменения\n";
        cout << "0 - отменить редактирование\n";
        int field = inputInt("выберите действие-> ", 0, 6);
        if (field == 0) {
            cout << "\nредактирование отменено\n";
            return;
        }
        if (field == 6) break;
        if (field == 1) {
            edited.setFullName(inputFullName());
        }
        else if (field == 2) {
            edited.setPosition(inputPosition());
        }
        else if (field == 3) {
            edited.setDepartment(inputDepartment());
        }
        else if (field == 4) {
            int day, month, year;
            inputDate("введите дату смены (дд.мм.гггг)-> ", day, month, year);
            edited.setDate(day, month, year);
        }
        else if (field == 5) {
            edited.setHours(inputHours());
        }
    }

    removeById(id);
    if (add(edited)) {
        cout << "\nзапись изменена\n";
    }
    else {
        add(original);
        cout << "\nизменения не применены: запись с таким фио и датой уже есть в контейнере\n";
    }
}

void Storage::showOnScreen() const {
    cout << "\nсодержимое контейнера " << title << ":\n";
    if (size() == 0) {
        cout << "\nконтейнер пуст\n";
        return;
    }
    print(cout);
}

void Storage::saveToFile() const {
    string fileName = title + ".txt";
    ofstream file(fileName.c_str());
    if (!file.is_open()) {
        cout << "\nне удалось открыть файл " << fileName << "\n";
        return;
    }
    file << "содержимое контейнера " << title << ":\n";
    if (size() == 0) {
        file << "\nконтейнер пуст\n";
    }
    else {
        print(file);
    }
    file.close();
    cout << "\nсодержимое контейнера сохранено в файл " << fileName << "\n";
}

void Storage::sortInteractive() const {
    if (size() == 0) {
        cout << "\nконтейнер пуст\n";
        return;
    }
    cout << "\nсортировать по:\n";
    cout << "1 - фио\n";
    cout << "2 - отделению\n";
    cout << "3 - дате\n";
    cout << "4 - количеству часов\n";
    cout << "0 - отмена\n";
    int field = inputInt("выберите действие-> ", 0, 4);
    if (field == 0) return;
    cout << "\nпорядок сортировки:\n";
    cout << "1 - по возрастанию\n";
    cout << "2 - по убыванию\n";
    int order = inputInt("выберите действие-> ", 1, 2);
    printSorted(field, order == 1);
}

void Storage::filterInteractive() const {
    if (size() == 0) {
        cout << "\nконтейнер пуст\n";
        return;
    }
    cout << "\nпоказать записи:\n";
    cout << "1 - по отделению\n";
    cout << "2 - по должности\n";
    cout << "3 - по количеству часов (диапазон)\n";
    cout << "4 - только со сверхурочной работой (больше 8 часов)\n";
    cout << "0 - отмена\n";
    int mode = inputInt("выберите действие-> ", 0, 4);
    if (mode == 0) return;

    string text;
    float from = 0;
    float to = 0;
    if (mode == 1) {
        text = inputDepartment();
    }
    else if (mode == 2) {
        text = inputPosition();
    }
    else if (mode == 3) {
        from = inputFloat("введите нижнюю границу часов-> ", 0, 24);
        to = inputFloat("введите верхнюю границу часов-> ", from, 24);
    }
    printFiltered(mode, text, from, to);
}


void Storage::fillTestData() {
    const int COUNT = 8;
    const char* names[COUNT] = {
        "Иванов Иван Петрович", "Иванов Иван Петрович", "Сидорова Анна Сергеевна",
        "Петров Олег Николаевич", "Козлова Мария Андреевна", "Смирнов Дмитрий Игоревич",
        "Орлова Елена Викторовна", "Петров Олег Николаевич"
    };
    const char* positions[COUNT] = {
        "врач-терапевт", "врач-терапевт", "медсестра", "хирург",
        "медсестра", "анестезиолог", "врач-терапевт", "хирург"
    };
    const char* departments[COUNT] = {
        "терапия", "терапия", "хирургия", "хирургия",
        "терапия", "реанимация", "терапия", "хирургия"
    };
    int days[COUNT] = { 5, 6, 5, 5, 6, 7, 7, 7 };
    int months[COUNT] = { 10, 10, 10, 10, 10, 10, 10, 10 };
    int years[COUNT] = { 2026, 2026, 2026, 2026, 2026, 2026, 2026, 2026 };
    float hours[COUNT] = { 8.0f, 12.0f, 8.0f, 10.5f, 8.0f, 12.0f, 7.5f, 8.0f };

    int added = 0;
    for (int i = 0; i < COUNT; i++) {
        WorkRecord rec(nextId, names[i], positions[i], departments[i],
            days[i], months[i], years[i], hours[i]);
        if (add(rec)) {
            nextId++;
            added++;
        }
    }
    cout << "\nдобавлено записей: " << added << " из " << COUNT << "\n";
}


void Storage::run() {
    while (true) {
        cout << "\n~~~ контейнер " << title << " ~~~\n";
        cout << "1 - добавить запись\n";
        cout << "2 - удалить запись\n";
        cout << "3 - редактировать запись\n";
        cout << "4 - вывести содержимое на экран\n";
        cout << "5 - сохранить содержимое в файл\n";
        cout << "6 - поиск\n";
        cout << "7 - сортировка\n";
        cout << "8 - фильтр\n";
        cout << "9 - заполнить тестовыми данными\n";
        cout << "0 - назад к выбору контейнера\n";
        int choice = inputInt("выберите действие-> ", 0, 10);
        switch (choice) {
        case 1: addInteractive(); break;
        case 2: removeInteractive(); break;
        case 3: editInteractive(); break;
        case 4: showOnScreen(); break;
        case 5: saveToFile(); break;
        case 6: search(); break;
        case 7: sortInteractive(); break;
        case 8: filterInteractive(); break;
        case 9: fillTestData(); break;
        case 0: return;
        }
    }
}