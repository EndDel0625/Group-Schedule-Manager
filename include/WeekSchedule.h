//
// Created by 김영빈 on 10/25/25.
//

#ifndef FINAL_PROJECT_WEEKSCHEDULE_H
#define FINAL_PROJECT_WEEKSCHEDULE_H


#include "DaySchedule.h"
#include <map>
#include <string>

enum class DayOfWeek {
    Monday = 0,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

struct SimpleDate {
    int year;
    int month;
    int day;
};

class WeekSchedule {
    private:
        std::string studentId;
        std::map<DayOfWeek, DaySchedule*> weekDays;
        SimpleDate mondayDate;

    public:
        WeekSchedule(const std::string& id);
        ~WeekSchedule();

        void setMondayDate(const SimpleDate& date);

        DaySchedule* getDay(DayOfWeek day);
        SimpleDate getMondayDate() const;
        std::string getStudentId() const;

        void displayWeekSchedule() const;
};

#endif //FINAL_PROJECT_WEEKSCHEDULE_H