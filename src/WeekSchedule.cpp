//
// Created by 김영빈 on 11/16/25.
//


#include "WeekSchedule.h"
#include <iostream>
#include "DayConverter.h"



WeekSchedule::WeekSchedule(const std::string &id) : studentId(id),mondayDate{0,0,0} {
    for (int d = (int)DayOfWeek::Monday; d <= (int)DayOfWeek::Sunday; ++d) {
        weekDays[(DayOfWeek)d] = new DaySchedule(studentId);
    }
}

WeekSchedule::~WeekSchedule() {
    for (auto& pair : weekDays) {
        delete pair.second;
    }
    weekDays.clear();
}


DaySchedule* WeekSchedule::getDay(DayOfWeek day) {
    return weekDays[(DayOfWeek)day];
}

void WeekSchedule::setMondayDate(const SimpleDate& date) {
    mondayDate = date;
}

SimpleDate WeekSchedule::getMondayDate() const {
    return mondayDate;
}

std::string WeekSchedule::getStudentId() const {
    return studentId;
}

void WeekSchedule::displayWeekSchedule() const {
    std::cout << "\n===== Weekly Schedule for " << studentId << " =====" << std::endl;

    for (int d = (int)DayOfWeek::Monday; d <= (int)DayOfWeek::Sunday; ++d) {
        DayOfWeek day = (DayOfWeek)d;
        std::cout << "\n[" << dayToString(day) << "]" << std::endl;
        weekDays.at(day)->displayDaySchedule();

        std::vector<int> free = weekDays.at(day)->findFreeSlots();
        std::cout << "Free hours: ";
        if (free.empty()) {
            std::cout << "None";
        } else {
            for (int h : free) {
                std::cout << h << ":00 ";
            }
        }
        std::cout << std::endl;
    }
}



