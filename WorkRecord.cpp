#include "WorkRecord.h"

const float WorkRecord::NORM_HOURS = 8.0f;

WorkRecord::WorkRecord()
    : id(0), fullName(""), position(""), department(""),
    day(1), month(1), year(2000), hours(0) {}

WorkRecord::WorkRecord(int id, const string& fullName, const string& position,
    const string& department, int day, int month, int year, float hours)
    : id(id), fullName(fullName), position(position), department(department),
    day(day), month(month), year(year), hours(hours) {}

int WorkRecord::getId() const { return id; }
const string& WorkRecord::getFullName() const { return fullName; }
const string& WorkRecord::getPosition() const { return position; }
const string& WorkRecord::getDepartment() const { return department; }
int WorkRecord::getDay() const { return day; }
int WorkRecord::getMonth() const { return month; }
int WorkRecord::getYear() const { return year; }
float WorkRecord::getHours() const { return hours; }

void WorkRecord::setId(int id) { this->id = id; }
void WorkRecord::setFullName(const string& fullName) { this->fullName = fullName; }
void WorkRecord::setPosition(const string& position) { this->position = position; }
void WorkRecord::setDepartment(const string& department) { this->department = department; }
void WorkRecord::setDate(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}
void WorkRecord::setHours(float hours) { this->hours = hours; }

string WorkRecord::getDateString() const {
    string result;
    if (day < 10) result += "0";
    result += to_string(day);
    result += ".";
    if (month < 10) result += "0";
    result += to_string(month);
    result += ".";
    result += to_string(year);
    return result;
}

int WorkRecord::getDateKey() const {
    return year * 10000 + month * 100 + day;
}

float WorkRecord::getOvertime() const {
    return hours > NORM_HOURS ? hours - NORM_HOURS : 0.0f;
}

bool WorkRecord::isValidDate(int day, int month, int year) {
    if (year < 2000 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool leapYear = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    int maxDay = daysInMonth[month - 1];
    if (month == 2 && leapYear) maxDay = 29;
    return day >= 1 && day <= maxDay;
}

bool operator<(const WorkRecord& first, const WorkRecord& second) {
    if (first.getFullName() != second.getFullName())
        return first.getFullName() < second.getFullName();
    return first.getDateKey() < second.getDateKey();
}

bool operator==(const WorkRecord& first, const WorkRecord& second) {
    return first.getFullName() == second.getFullName()
        && first.getDateKey() == second.getDateKey();
}