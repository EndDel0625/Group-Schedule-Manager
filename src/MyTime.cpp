//
// Created by 김영빈 on 11/8/25.
//
#include "MyTime.h"
#include <cmath>
#include <iomanip>

MyTime::MyTime() : year(0), month(0), day(0), dayOfWeek(DayOfWeek::Monday),hour(0), minute(0) {
}

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

int MyTime::diffMinutes(const MyTime& other) const {
    return std::abs(this->toMinutes() - other.toMinutes());
}

void MyTime::display() const {
    std::cout << dayToString(dayOfWeek) << " "
              << year << "/" << month << "/" << day << " "
              << hour << ":"
              << std::setw(2) << std::setfill('0') << minute;
}