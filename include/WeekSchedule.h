//
// Created by 김영빈 on 10/25/25.
//

#ifndef FINAL_PROJECT_WEEKSCHEDULE_H
#define FINAL_PROJECT_WEEKSCHEDULE_H

#include <map>
#include "DaySchedule.h"
#include <string>
#include "DayConverter.h"



class WeekSchedule {
    private:
        std::string studentId;
        std::map<DayOfWeek, DaySchedule*> days;

    public:
        WeekSchedule(const std::string& id);
        ~WeekSchedule();

        DaySchedule* getDay(DayOfWeek day);
        std::string getStudentId() const;

        void displayWeekSchedule() const;
};

#endif //FINAL_PROJECT_WEEKSCHEDULE_H