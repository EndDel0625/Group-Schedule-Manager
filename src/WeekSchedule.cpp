//
// Created by 김영빈 on 11/16/25.
//


#include "WeekSchedule.h"
#include <iostream>



WeekSchedule::WeekSchedule(const std::string& id) : studentId(id) {

    for (int d = 0; d < 7; ++d) {
        DayOfWeek day = static_cast<DayOfWeek>(d);
        days[day] = new DaySchedule(studentId);
    }
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
    std::cout << "\n==== Week Schedule for " << studentId << " ====" << std::endl;
    for (int d = 0; d < 7; ++d) {
        DayOfWeek day = static_cast<DayOfWeek>(d);
        auto it = days.find(day);
        if (it == days.end()) continue;

        std::cout << "[" << dayToString(day) << "]" <<std::endl;
        const DaySchedule* ds = it->second;
        ds->displayDaySchedule();
    }
}



