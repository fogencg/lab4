#pragma once
#include <string>
using namespace std;

// ограничения на вводимые данные
const int MAX_ID = 999999;
const int MAX_NAME_LENGTH = 26;
const int MAX_POSITION_LENGTH = 18;
const int MAX_DEPARTMENT_LENGTH = 14;

// запись об одной отработанной смене медицинского работника
class WorkRecord {
private:
    int id;                
    string fullName;       
    string position;       
    string department;     
    int day;               
    int month;
    int year;
    float hours;         
public:
    static const float NORM_HOURS; 

    WorkRecord();
    WorkRecord(int id, const string& fullName, const string& position,
        const string& department, int day, int month, int year, float hours);

    int getId() const;
    const string& getFullName() const;
    const string& getPosition() const;
    const string& getDepartment() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    float getHours() const;

    void setId(int id);
    void setFullName(const string& fullName);
    void setPosition(const string& position);
    void setDepartment(const string& department);
    void setDate(int day, int month, int year);
    void setHours(float hours);

    string getDateString() const;   
    int getDateKey() const;        
    float getOvertime() const;      

    static bool isValidDate(int day, int month, int year);
};


bool operator<(const WorkRecord& first, const WorkRecord& second);
bool operator==(const WorkRecord& first, const WorkRecord& second);