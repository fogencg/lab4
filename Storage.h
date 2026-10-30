#pragma once
#include <iostream>
#include <string>
#include "WorkRecord.h"
using namespace std;


bool matchesFilter(const WorkRecord& rec, int mode, const string& text, float from, float to);


class Storage {
protected:
    string title;  
    int nextId;     
public:
    Storage(const string& title);
    virtual ~Storage();

    const string& getTitle() const;

    virtual bool add(const WorkRecord& rec) = 0;
    virtual bool removeById(int id) = 0;
    virtual bool findById(int id, WorkRecord& result) const = 0;
    virtual int size() const = 0;
    virtual void print(ostream& out) const = 0;
    virtual void printSorted(int field, bool ascending) const = 0;
    virtual void printFiltered(int mode, const string& text, float from, float to) const = 0;
    virtual void search() const = 0;


    //user
    void addInteractive();
    void removeInteractive();
    void editInteractive();
    void showOnScreen() const;
    void saveToFile() const;
    void sortInteractive() const;
    void filterInteractive() const;
    void fillTestData();
    void run();
};