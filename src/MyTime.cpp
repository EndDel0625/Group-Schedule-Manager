//
// Created by 김영빈 on 11/8/25.
//
#include "MyTime.h"
#include <iostream>
#include <iomanip>

MyTime::MyTime(int h, int m) : hour(h), minute(m) {}

void MyTime::setTime(int h, int m) {
    hour = h;
    minute = m;
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
int MyTime::diffMinutes(const MyTime &other) const {
    return other.toMinutes() - this->toMinutes();
}

bool MyTime::isAfter(const MyTime &other) const {
    return toMinutes() > other.toMinutes();
}

void MyTime::display() const {
    std::cout << std::setfill('0') << std::setw(2) << hour << ":"
              << std::setfill('0') << std::setw(2) << minute;
}