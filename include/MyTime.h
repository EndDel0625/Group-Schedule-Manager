//
// Created by 김영빈 on 11/10/25.
//

#ifndef FINAL_PROJECT_MYTIME_H
#define FINAL_PROJECT_MYTIME_H

#include <iostream>
#include "DayConverter.h"

class MyTime {
private:
    int year{};
    int month{};
    int day{};
    DayOfWeek dayOfWeek;
    int hour{};
    int minute{};
public:

    MyTime();
    MyTime(int y, int m, int d, DayOfWeek dow, int h, int min);

    int getYear() const;
    int getMonth() const;
    int getDay() const;
    DayOfWeek getDayOfWeek() const;
    int getHour() const;
    int getMinute() const;

    int toMinutes() const;
    int diffMinutes(const MyTime& other) const;

    void display() const;
};

#endif //FINAL_PROJECT_MYTIME_H