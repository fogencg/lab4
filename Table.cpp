#include "Table.h"

const int WIDTH_ID = 5;
const int WIDTH_NAME = MAX_NAME_LENGTH;
const int WIDTH_POSITION = MAX_POSITION_LENGTH;
const int WIDTH_DEPARTMENT = MAX_DEPARTMENT_LENGTH;
const int WIDTH_DATE = 10;
const int WIDTH_HOURS = 5;

static string pad(const string& text, int width) {
    if ((int)text.length() >= width) return text;
    return text + string(width - text.length(), ' ');
}


static void printFloat(ostream& out, float value, int width) {
    ios::fmtflags oldFlags = out.flags();
    streamsize oldPrecision = out.precision();
    out.setf(ios::fixed, ios::floatfield);
    out.setf(ios::right, ios::adjustfield);
    out.precision(1);
    out.width(width);
    out << value;
    out.flags(oldFlags);
    out.precision(oldPrecision);
}


static void printLine(ostream& out) {
    out << string(WIDTH_ID + 1, '-') << "+"
        << string(WIDTH_NAME + 2, '-') << "+"
        << string(WIDTH_POSITION + 2, '-') << "+"
        << string(WIDTH_DEPARTMENT + 2, '-') << "+"
        << string(WIDTH_DATE + 2, '-') << "+"
        << string(WIDTH_HOURS + 1, '-') << "\n";
}

void printTableHeader(ostream& out) {
    out << "\n";
    out << pad("номер", WIDTH_ID) << " | "
        << pad("фио", WIDTH_NAME) << " | "
        << pad("должность", WIDTH_POSITION) << " | "
        << pad("отделение", WIDTH_DEPARTMENT) << " | "
        << pad("дата", WIDTH_DATE) << " | "
        << pad("часы", WIDTH_HOURS) << "\n";
    printLine(out);
}

void printTableRow(ostream& out, const WorkRecord& rec) {
    ios::fmtflags oldFlags = out.flags();
    out.setf(ios::right, ios::adjustfield);
    out.width(WIDTH_ID);
    out << rec.getId();
    out.flags(oldFlags);
    out << " | " << pad(rec.getFullName(), WIDTH_NAME)
        << " | " << pad(rec.getPosition(), WIDTH_POSITION)
        << " | " << pad(rec.getDepartment(), WIDTH_DEPARTMENT)
        << " | " << pad(rec.getDateString(), WIDTH_DATE)
        << " | ";
    printFloat(out, rec.getHours(), WIDTH_HOURS);
    out << "\n";
}

void printTableFooter(ostream& out, int count, float totalHours, float totalOvertime) {
    printLine(out);
    out << "итого записей: " << count << ", всего часов: ";
    printFloat(out, totalHours, 0);
    out << ", из них сверхурочно: ";
    printFloat(out, totalOvertime, 0);
    out << "\n";
}

void printTableSingle(ostream& out, const WorkRecord& rec) {
    printTableHeader(out);
    printTableRow(out, rec);
    printLine(out);
}