#include <iostream>
#include "Storages.h"
#include "Input.h"
#include "Table.h"
using namespace std;


MapStorage::MapStorage() : ContainerStorage<IdMap>("map") {}


bool MapStorage::add(const WorkRecord& rec) {
    return data.insert(make_pair(rec.getId(), rec)).second;
}

bool MapStorage::removeById(int id) {
    return data.erase(id) > 0;
}

bool MapStorage::findById(int id, WorkRecord& result) const {
    IdMap::const_iterator it = data.find(id);
    if (it == data.end()) return false;
    result = it->second;
    return true;
}

void MapStorage::search() const {
    int id = inputInt("введите номер записи для поиска-> ", 1, MAX_ID);
    IdMap::const_iterator it = data.find(id);
    if (it == data.end()) {
        cout << "\nзапись с номером " << id << " не найдена\n";
    }
    else {
        cout << "\nзапись найдена:\n";
        printTableSingle(cout, it->second);
    }
}


SetStorage::SetStorage() : ContainerStorage<RecordSet>("set") {}
bool SetStorage::add(const WorkRecord& rec) {
    return data.insert(rec).second;
}

void SetStorage::search() const {
    string fullName = inputFullName();
    int day, month, year;
    inputDate("введите дату смены (дд.мм.гггг)-> ", day, month, year);
    WorkRecord key(0, fullName, "", "", day, month, year, 0);
    RecordSet::const_iterator it = data.find(key);
    if (it == data.end()) {
        cout << "\nзапись не найдена\n";
    }
    else {
        cout << "\nзапись найдена:\n";
        printTableSingle(cout, *it);
    }
}


MultimapStorage::MultimapStorage() : ContainerStorage<DepartmentMultimap>("multimap") {}


bool MultimapStorage::add(const WorkRecord& rec) {
    data.insert(make_pair(rec.getDepartment(), rec));
    return true;
}

void MultimapStorage::search() const {
    string department = inputDepartment();
    pair<DepartmentMultimap::const_iterator, DepartmentMultimap::const_iterator> range
        = data.equal_range(department);
    cout << "\nколичество записей отделения " << department << ": " << data.count(department) << "\n";
    printRange(range.first, range.second);
}



MultisetStorage::MultisetStorage() : ContainerStorage<HoursMultiset>("multiset") {}

bool MultisetStorage::add(const WorkRecord& rec) {
    data.insert(rec);
    return true;
}

void MultisetStorage::search() const {
    cout << "\nпоиск по количеству часов:\n";
    cout << "1 - равно (equal_range)\n";
    cout << "2 - не меньше (lower_bound)\n";
    cout << "3 - строго больше (upper_bound)\n";
    cout << "0 - отмена\n";
    int mode = inputInt("выберите действие-> ", 0, 3);
    if (mode == 0) return;

    WorkRecord key;
    key.setHours(inputHours());
    if (mode == 1) {
        pair<HoursMultiset::const_iterator, HoursMultiset::const_iterator> range = data.equal_range(key);
        cout << "\nколичество записей: " << data.count(key) << "\n";
        printRange(range.first, range.second);
    }
    else if (mode == 2) {
        printRange(data.lower_bound(key), data.end());
    }
    else {
        printRange(data.upper_bound(key), data.end());
    }
}



UnorderedMapStorage::UnorderedMapStorage() : ContainerStorage<IdUnorderedMap>("unordered_map") {}



bool UnorderedMapStorage::add(const WorkRecord& rec) {
    return data.insert(make_pair(rec.getId(), rec)).second;
}

bool UnorderedMapStorage::removeById(int id) {
    return data.erase(id) > 0;
}

bool UnorderedMapStorage::findById(int id, WorkRecord& result) const {
    IdUnorderedMap::const_iterator it = data.find(id);
    if (it == data.end()) return false;
    result = it->second;
    return true;
}

void UnorderedMapStorage::search() const {
    int id = inputInt("введите номер записи для поиска-> ", 1, MAX_ID);
    IdUnorderedMap::const_iterator it = data.find(id);
    if (it == data.end()) {
        cout << "\nзапись с номером " << id << " не найдена\n";
    }
    else {
        cout << "\nзапись найдена:\n";
        printTableSingle(cout, it->second);
    }
}


UnorderedSetStorage::UnorderedSetStorage() : ContainerStorage<RecordUnorderedSet>("unordered_set") {}



bool UnorderedSetStorage::add(const WorkRecord& rec) {
    return data.insert(rec).second;
}

void UnorderedSetStorage::search() const {
    string fullName = inputFullName();
    int day, month, year;
    inputDate("введите дату смены (дд.мм.гггг)-> ", day, month, year);
    WorkRecord key(0, fullName, "", "", day, month, year, 0);
    RecordUnorderedSet::const_iterator it = data.find(key);
    if (it == data.end()) {
        cout << "\nзапись не найдена\n";
    }
    else {
        cout << "\nзапись найдена:\n";
        printTableSingle(cout, *it);
    }
}



UnorderedMultimapStorage::UnorderedMultimapStorage()
    : ContainerStorage<PositionUnorderedMultimap>("unordered_multimap") {}

bool UnorderedMultimapStorage::add(const WorkRecord& rec) {
    data.insert(make_pair(rec.getPosition(), rec));
    return true;
}

void UnorderedMultimapStorage::search() const {
    string position = inputPosition();
    pair<PositionUnorderedMultimap::const_iterator, PositionUnorderedMultimap::const_iterator> range
        = data.equal_range(position);
    cout << "\nколичество записей по должности " << position << ": " << data.count(position) << "\n";
    printRange(range.first, range.second);
}


UnorderedMultisetStorage::UnorderedMultisetStorage()
    : ContainerStorage<NameUnorderedMultiset>("unordered_multiset") {}


bool UnorderedMultisetStorage::add(const WorkRecord& rec) {
    data.insert(rec);
    return true;
}

void UnorderedMultisetStorage::search() const {
    string fullName = inputFullName();
    WorkRecord key;
    key.setFullName(fullName);
    pair<NameUnorderedMultiset::const_iterator, NameUnorderedMultiset::const_iterator> range
        = data.equal_range(key);
    cout << "\nколичество смен работника " << fullName << ": " << data.count(key) << "\n";
    printRange(range.first, range.second);
}