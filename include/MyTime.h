//
// Created by 김영빈 on 11/10/25.
//

#ifndef FINAL_PROJECT_MYTIME_H
#define FINAL_PROJECT_MYTIME_H

class MyTime {
private:
    int hour;
    int minute;
public:
    MyTime(int h = 0, int m = 0);
    void setTime(int h, int m);

    int getHour() const;
    int getMinute() const;

    int toMinutes() const;
    int diffMinutes(const MyTime &other) const;

    bool isAfter(const MyTime &other) const;
    void display() const;
};

#endif //FINAL_PROJECT_MYTIME_H