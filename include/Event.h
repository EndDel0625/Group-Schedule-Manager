//
// Created by 김영빈 on 10/16/25.
//

#ifndef FINAL_PROJECT_EVENT_H
#define FINAL_PROJECT_EVENT_H

#include "MyTime.h"
#include <string>
#include <iostream>

class Event {
protected:
    std::string title;
    MyTime startTime;
    MyTime endTime;
    std::string note;

public:
    Event(const std::string& t, const MyTime& s, const MyTime& e, const std::string& n = "");
    virtual ~Event() = default;

    std::string getTitle() const;
    MyTime getStartTime() const;
    MyTime getEndTime() const;
    std::string getNote() const;

    void updateTitle(const std::string &newTitle);
    void updateTime(const MyTime &newStart, const MyTime &newEnd);
    void updateNote(const std::string &newNote);

    int getDurationMinutes() const;
    bool overlapsWith(const Event &other) const;

    virtual void display() const;
};

#endif //FINAL_PROJECT_EVENT_H