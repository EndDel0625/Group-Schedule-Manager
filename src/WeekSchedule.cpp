//
// Created by 김영빈 on 11/16/25.
//


#include "WeekSchedule.h"
#include <iostream>



WeekSchedule::WeekSchedule(const std::string& id) : studentId(id) {

    days[DayOfWeek::Monday]    = new DaySchedule(studentId);
    days[DayOfWeek::Tuesday]   = new DaySchedule(studentId);
    days[DayOfWeek::Wednesday] = new DaySchedule(studentId);
    days[DayOfWeek::Thursday]  = new DaySchedule(studentId);
    days[DayOfWeek::Friday]    = new DaySchedule(studentId);
    days[DayOfWeek::Saturday]  = new DaySchedule(studentId);
    days[DayOfWeek::Sunday]    = new DaySchedule(studentId);
}

WeekSchedule::~WeekSchedule() {
    for (auto& pair : days) {
        delete pair.second;
    }
    days.clear();
}


DaySchedule* WeekSchedule::getDay(DayOfWeek day) {
    return days[day];
}


std::string WeekSchedule::getStudentId() const {
    return studentId;
}

void WeekSchedule::displayWeekSchedule() const {
    std::cout << "\n=== Weekly Schedule for " << studentId << " ===" << std::endl;

    for (auto& entry : days) {
        DayOfWeek day = entry.first;
        DaySchedule* schedule = entry.second;

        std::cout << "\n[" << dayToString(day) << "]" << std::endl;
        schedule->displayDaySchedule();
    }
}



