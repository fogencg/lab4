#include <windows.h>
#include <iostream>
#include "Storages.h"
#include "Input.h"
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    MapStorage mapStorage;
    SetStorage setStorage;
    MultimapStorage multimapStorage;
    MultisetStorage multisetStorage;
    UnorderedMapStorage unorderedMapStorage;
    UnorderedSetStorage unorderedSetStorage;
    UnorderedMultimapStorage unorderedMultimapStorage;
    UnorderedMultisetStorage unorderedMultisetStorage;

    const int COUNT = 8;
    Storage* storages[COUNT] = {
        &mapStorage, &setStorage, &multimapStorage, &multisetStorage,
        &unorderedMapStorage, &unorderedSetStorage,
        &unorderedMultimapStorage, &unorderedMultisetStorage
    };

    while (true) {
        cout << "\n~~~ учет рабочего времени медицинских работников ~~~\n";
        cout << "выберите контейнер:\n";
        for (int i = 0; i < COUNT; i++)
            cout << i + 1 << " - " << storages[i]->getTitle()
            << "\n";
        cout << "0 - выход из программы\n";
        int choice = inputInt("выберите действие-> ", 0, COUNT);
        if (choice == 0) {
            if (inputYesNo("\nвы действительно хотите выйти? ")) break;
        }
        else {
            storages[choice - 1]->run();
        }
    }
    cout << "\nработа программы завершена\n";
    return 0;
}