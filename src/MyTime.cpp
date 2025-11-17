//
// Created by 김영빈 on 11/8/25.
//
#include "MyTime.h"
#include <iostream>
#include <iomanip>

MyTime::MyTime() = default;

MyTime::MyTime(int y, int m, int d, DayOfWeek dow, int h, int min)
    : year(y), month(m), day(d), dayOfWeek(dow), hour(h), minute(min) {
}

int MyTime::getYear() const {
    return year;
}
int MyTime::getMonth() const {
    return month;
}
int MyTime::getDay() const {
    return day;
}
DayOfWeek MyTime::getDayOfWeek() const {
    return dayOfWeek;
}
int MyTime::getHour() const {
    return hour;
}
int MyTime::getMinute() const {
    return minute;
}

int MyTime::toMinutes() const {
    return hour * 60 + minute;
}

void MyTime::display() const {
    std::cout << dayToString(dayOfWeek) << " "
              << year << "/" << month << "/" << day << " "
              << hour << ":"
              << std::setw(2) << std::setfill('0') << minute;
}