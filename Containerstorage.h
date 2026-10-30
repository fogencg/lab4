#pragma once
#include <iostream>
#include <map>
#include "Storage.h"
#include "Table.h"
using namespace std;


inline const WorkRecord& getRecord(const WorkRecord& rec) {
    return rec;
}


template <class Key>
const WorkRecord& getRecord(const pair<const Key, WorkRecord>& element) {
    return element.second;
}


template <class Iterator>
int printRange(Iterator first, Iterator last) {
    int count = 0;
    float totalHours = 0;
    float totalOvertime = 0;
    for (Iterator it = first; it != last; ++it) {
        const WorkRecord& rec = getRecord(*it);
        if (count == 0) printTableHeader(cout);
        printTableRow(cout, rec);
        count++;
        totalHours += rec.getHours();
        totalOvertime += rec.getOvertime();
    }
    if (count == 0) cout << "\nзаписи не найдены\n";
    else printTableFooter(cout, count, totalHours, totalOvertime);
    return count;
}


inline string keyFullName(const WorkRecord& rec) { return rec.getFullName(); }
inline string keyDepartment(const WorkRecord& rec) { return rec.getDepartment(); }
inline int keyDate(const WorkRecord& rec) { return rec.getDateKey(); }
inline float keyHours(const WorkRecord& rec) { return rec.getHours(); }


template <class Container>
class ContainerStorage : public Storage {
protected:
    Container data;

    template <class Key>
    void printSortedBy(Key(*getKey)(const WorkRecord&), bool ascending) const {
        multimap<Key, const WorkRecord*> sorted;
        float totalHours = 0;
        float totalOvertime = 0;
        for (typename Container::const_iterator it = data.begin(); it != data.end(); ++it) {
            const WorkRecord& rec = getRecord(*it);
            sorted.insert(make_pair(getKey(rec), &rec));
            totalHours += rec.getHours();
            totalOvertime += rec.getOvertime();
        }
        printTableHeader(cout);
        if (ascending) {
            for (typename multimap<Key, const WorkRecord*>::const_iterator it = sorted.begin();
                it != sorted.end(); ++it)
                printTableRow(cout, *(it->second));
        }
        else {
            for (typename multimap<Key, const WorkRecord*>::const_reverse_iterator it = sorted.rbegin();
                it != sorted.rend(); ++it)
                printTableRow(cout, *(it->second));
        }
        printTableFooter(cout, (int)sorted.size(), totalHours, totalOvertime);
    }

public:
    ContainerStorage(const string& title) : Storage(title) {}

    int size() const override {
        return (int)data.size();
    }

    bool findById(int id, WorkRecord& result) const override {
        for (typename Container::const_iterator it = data.begin(); it != data.end(); ++it) {
            if (getRecord(*it).getId() == id) {
                result = getRecord(*it);
                return true;
            }
        }
        return false;
    }

    bool removeById(int id) override {
        for (typename Container::iterator it = data.begin(); it != data.end(); ++it) {
            if (getRecord(*it).getId() == id) {
                data.erase(it);
                return true;
            }
        }
        return false;
    }

    void print(ostream& out) const override {
        printTableHeader(out);
        float totalHours = 0;
        float totalOvertime = 0;
        for (typename Container::const_iterator it = data.begin(); it != data.end(); ++it) {
            const WorkRecord& rec = getRecord(*it);
            printTableRow(out, rec);
            totalHours += rec.getHours();
            totalOvertime += rec.getOvertime();
        }
        printTableFooter(out, (int)data.size(), totalHours, totalOvertime);
    }


    void printSorted(int field, bool ascending) const override {
        if (field == 1) printSortedBy(keyFullName, ascending);
        else if (field == 2) printSortedBy(keyDepartment, ascending);
        else if (field == 3) printSortedBy(keyDate, ascending);
        else if (field == 4) printSortedBy(keyHours, ascending);
    }

    void printFiltered(int mode, const string& text, float from, float to) const override {
        int count = 0;
        float totalHours = 0;
        float totalOvertime = 0;
        for (typename Container::const_iterator it = data.begin(); it != data.end(); ++it) {
            const WorkRecord& rec = getRecord(*it);
            if (!matchesFilter(rec, mode, text, from, to)) continue;
            if (count == 0) printTableHeader(cout);
            printTableRow(cout, rec);
            count++;
            totalHours += rec.getHours();
            totalOvertime += rec.getOvertime();
        }
        if (count == 0) cout << "\nзаписи, удовлетвор€ющие условию, не найдены\n";
        else printTableFooter(cout, count, totalHours, totalOvertime);
    }
};