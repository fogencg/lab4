#pragma once
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "ContainerStorage.h"
using namespace std;


struct HoursLess {
    bool operator()(const WorkRecord& first, const WorkRecord& second) const {
        return first.getHours() < second.getHours();
    }
};


struct RecordHash {
    size_t operator()(const WorkRecord& rec) const {
        return hash<string>()(rec.getFullName() + rec.getDateString());
    }
};


struct NameHash {
    size_t operator()(const WorkRecord& rec) const {
        return hash<string>()(rec.getFullName());
    }
};

struct NameEqual {
    bool operator()(const WorkRecord& first, const WorkRecord& second) const {
        return first.getFullName() == second.getFullName();
    }
};

typedef map<int, WorkRecord> IdMap;
typedef set<WorkRecord> RecordSet;
typedef multimap<string, WorkRecord> DepartmentMultimap;
typedef multiset<WorkRecord, HoursLess> HoursMultiset;
typedef unordered_map<int, WorkRecord> IdUnorderedMap;
typedef unordered_set<WorkRecord, RecordHash> RecordUnorderedSet;
typedef unordered_multimap<string, WorkRecord> PositionUnorderedMultimap;
typedef unordered_multiset<WorkRecord, NameHash, NameEqual> NameUnorderedMultiset;


class MapStorage : public ContainerStorage<IdMap> {
public:
    MapStorage();
    bool add(const WorkRecord& rec) override;
    bool removeById(int id) override;
    bool findById(int id, WorkRecord& result) const override;
    void search() const override;
};


class SetStorage : public ContainerStorage<RecordSet> {
public:
    SetStorage();
    bool add(const WorkRecord& rec) override;
    void search() const override;
};


class MultimapStorage : public ContainerStorage<DepartmentMultimap> {
public:
    MultimapStorage();
    bool add(const WorkRecord& rec) override;
    void search() const override;
};


class MultisetStorage : public ContainerStorage<HoursMultiset> {
public:
    MultisetStorage();
    bool add(const WorkRecord& rec) override;
    void search() const override;
};


class UnorderedMapStorage : public ContainerStorage<IdUnorderedMap> {
public:
    UnorderedMapStorage();
    bool add(const WorkRecord& rec) override;
    bool removeById(int id) override;
    bool findById(int id, WorkRecord& result) const override;
    void search() const override;
};


class UnorderedSetStorage : public ContainerStorage<RecordUnorderedSet> {
public:
    UnorderedSetStorage();
    bool add(const WorkRecord& rec) override;
    void search() const override;
};


class UnorderedMultimapStorage : public ContainerStorage<PositionUnorderedMultimap> {
public:
    UnorderedMultimapStorage();
    bool add(const WorkRecord& rec) override;
    void search() const override;
};


class UnorderedMultisetStorage : public ContainerStorage<NameUnorderedMultiset> {
public:
    UnorderedMultisetStorage();
    bool add(const WorkRecord& rec) override;
    void search() const override;
};